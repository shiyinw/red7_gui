#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <fcntl.h>
#include <cstring>
#include <signal.h>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;

int num_players;
int game_mode=0;
int num_games=1;
int num_rounds=7;



#define LOG_FILE "log.txt"
#define PLAYER_OUTPUT "output.txt"
#define MAX_PLAYERS 4
#define MAX_ROUNDS 12


#define TIME_LIMIT 2

int scores[MAX_PLAYERS];///

pid_t pid;///


string player_file[MAX_PLAYERS];///

void print_list_on_screen(list<int> a) {
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    cout << *it << " ";
  cout << endl;
}

void print_list(list<int> a, ostringstream& r) {
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    r << *it << " ";

}

bool compare(list<int> a, list<int> b) {    //if a is higher than b, return true
  if (a.size()==0) return false;
  else if (a.size()>b.size()) return true;
  else if (a.size()<b.size()) return false;
  else return (*max_element(a.begin(),a.end()) > *max_element(b.begin(),b.end()));

}

list<int> red(list<int> a) {
  list<int> r;
  r.push_back(*max_element(a.begin(),a.end()));
  return r;

}

list<int> orange(list<int> a) {
  list<int> n[8],best;
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    n[(int)(*it/10)].push_back(*it);

  best=n[1];
  for (int i=2;i<8;i++)
    if (compare(n[i],best)) best=n[i];

  return best;   

}

list<int> yellow(list<int> a) {
  list<int> n[8],best;
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    n[*it%10].push_back(*it);

  best=n[1];
  for (int i=2;i<8;i++)
    if (compare(n[i],best)) best=n[i];

  return best;   

}

list<int> green(list<int> a) {
  list<int> r;
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    if (((int)(*it/10))%2==0) r.push_back(*it);
  return r;
}

list<int> blue(list<int> a) {
  int m_color[8]={0,0,0,0,0,0,0,0};
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    if (*it>m_color[*it%10]) m_color[*it%10]=*it;
  list<int> r;
  for (int i=1;i<8;i++)
    if (m_color[i]>0) r.push_back(m_color[i]);
  return r;

}

list<int> indigo(list<int> a) {
  int m_number[8]={0,0,0,0,0,0,0,0};
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    if (*it>m_number[(int)(*it/10)]) m_number[(int)(*it/10)]=*it;

  list<int> best, current;
  for (int i=1;i<8;i++)
    if (m_number[i]==0) current.clear();
    else {
      current.push_back(m_number[i]);
      if (compare(current,best)) best=current;
    }
  return best;
}

list<int> violet(list<int> a) {
  list<int> r;
  for (list<int>::iterator it=a.begin();it!=a.end();it++)
    if (((int)(*it/10))<4) r.push_back(*it);
  return r;
}


void overtime(int param) {
	kill(pid,SIGKILL);
	cerr << "Killing process " << pid << endl;
}


  
class game
{
  ostringstream record; //all information of the current game

  ostringstream duration; //the public information so far

public:
  list<int> hand[MAX_PLAYERS], palette[MAX_PLAYERS];
  int current_rule;

  int num_active;
  bool active[MAX_PLAYERS];

  list<int> highest;
  
  void deal(list<int> whole) {
    vector<int> v;
    for (list<int>::iterator it=whole.begin();it!=whole.end();it++)    
      v.push_back(*it);
    int i,j,c;
    int k=rand();
    for (i=0;i<num_rounds;i++)
      for (j=0;j<num_players;j++)
	{
	  c=rand()%v.size();
	  hand[(j+k)%num_players].push_back(v[c]);
	  v.erase(v.begin()+c);
	}
    for (j=0;j<num_players;j++)
      {
	c=rand()%v.size();
	palette[(j+k)%num_players].push_back(v[c]);
	v.erase(v.begin()+c);
      }
  }

  int winning(int rule) {
    if (rule==0) rule=current_rule;
    int i,win;
    win=-1;
    list<int> best, top;
    for (i=0;i<num_players;i++)
      if (active[i]) {
	top.clear();
	switch (rule) {
	case 7: top=red(palette[i]); break;
	case 6: top=orange(palette[i]); break;
	case 5: top=yellow(palette[i]); break;
	case 4: top=green(palette[i]); break;
	case 3: top=blue(palette[i]); break;
	case 2: top=indigo(palette[i]); break;
	case 1: top=violet(palette[i]); break;
	}
      
	if (compare(top,best)) {
	  best=top;
	  win=i;
	}
      }
    highest=best;
    return win;
  }


  void record_log() {
    int i;
    record << "Current rule: " << current_rule << endl;
    for (i=0;i<num_players;i++) {
      record << "player " << i << "'s hand: ";
      if (active[i]) {
	print_list(hand[i],record);
	record << " palette: ";
	print_list(palette[i],record);
      }
      else record << "0";
      record << endl;
    }

  }

  void print_log() {
    ofstream logfile;   //write the log file
    logfile.open(LOG_FILE,ofstream::app);
    logfile << record.str();
    logfile.close();
  }
	  
  game(list<int> whole) {
    current_rule=7;
    deal(whole);
    num_active=num_players;
    int i;
    for (i=0;i<num_players;i++)
      active[i]=true;

    for (i=0;i<num_players;i++)
      duration << scores[i] << " ";
    duration << endl;
    duration << whole.size() << " ";
    print_list(whole,duration);
    duration << endl;
    

    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    record << "Game between ";
    for (i=0;i<num_players;i++)
      record << "player " << i << " (" << player_file[i] << "), ";
    record << endl;
    record << "At time " << asctime(timeinfo) << endl;
    record_log();

  }

  void run_program(int p, int& rule_card, int& card) {
    		//p stands for index of the current player

		
		string cmd = player_file[p]; // secondary program you want to run
		rule_card=0;card=0;
		int input[2], output[2];

		unlink(PLAYER_OUTPUT);
		
		signal(SIGPIPE, SIG_IGN);
		if (pipe(input)!=0 || pipe(output)!=0) {
			cerr << "Pipe Error!" << endl;
			return;
		}

		pid = fork(); // create child process //在子进程调用

		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0) // child process
		{
			dup2(input[0],0);//程序间输入管道
			dup2(output[1],1);//输出

			close(input[1]);
			close(output[0]);
        
			execl(cmd.c_str(),cmd.c_str(), NULL); // run the command

			perror("execl"); // execl doesn't return unless there is a problem
			cerr << "child process ends." << endl;
			exit(1);
		}
		else // parent process, pid now contains the child pid
		{
			close(input[0]);  
			close(output[1]);

			FILE *child_out = fdopen(output[0], "r");
			FILE *child_in = fdopen(input[1], "w");

			ostringstream info;
			info << num_players << " " << p <<endl;
			info << current_rule << endl;
			info << hand[p].size() << " ";
			print_list(hand[p],info);
			info << endl;
			//info << palette[p].size() << " ";
			//print_list(palette[p],info);
			//info << endl;
			int i;
			for (i=0;i<num_players;i++)
			  {
			    if (active[i]) {
			      info << hand[i].size() << endl;
			      info << palette[i].size() << " ";
			      print_list(palette[i],info);
			      info << endl;
			    }
			    else info << 0 << endl << 0 << endl;
			  }
			
			fprintf(child_in, "%s\n", info.str().c_str());
        
		  
			fprintf(child_in, "%s\n", duration.str().c_str());

			

			fflush(child_in);
            
            fclose(child_in);

			signal(SIGALRM, overtime);
			alarm(TIME_LIMIT);

			int status;
			while (-1 == waitpid(pid, &status, 0)); // wait for child to complete

			alarm(0);

			if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			{
				// handle error
				cerr << "process " << cmd << " (pid=" << pid << ") failed" << endl;
			}

			int rc=0,c=0;
			if (fscanf(child_out, "%d%d", &rc, &c) < 2)//得到出牌
			{
			  // cerr << "Try to read output.txt" << endl;
			        ifstream file;
				file.open(PLAYER_OUTPUT);

				if (!file.is_open()) {
					cerr << "No output.txt" << endl;
					// return 0;
				}
				else if (!(file >> rc) || !(file >> c)) {
					cerr << "NO OUTPUT" << endl;
					// return 0;
				}
				file.close();
				unlink(PLAYER_OUTPUT);
			}

			fclose(child_in);
			fclose(child_out);

			// cout << "The pid is: " << pid << endl;

			rule_card=rc;
			card=c;
		}


  }



    
  int game_play() {
    int p;
    int i,j;

    bool current_winning;
    p=(winning(current_rule)+1)%num_players;    
    do {
      if (active[p]) {
	int rule,rule_card=0,card=0;
	if (hand[p].size()>0)
	  run_program(p, rule_card, card);

	record << "player "<< p << "'s play: " << rule_card << " " << card << endl;
	
	if (card>0) {
	  list<int>::iterator it=find(hand[p].begin(),hand[p].end(),card);
	  if (it==hand[p].end()) {
	    cout << "Card not in player " << p << "'s hand" << endl;
	    record << "Card not in player " << p << "'s hand" << endl;
	    card=0;
	  }
	  else {
	    palette[p].push_back(card);
	    hand[p].remove(card);
	  }
	}

	if (rule_card>0) {
	  list<int>::iterator it=find(hand[p].begin(),hand[p].end(),rule_card);
	  if (it==hand[p].end()) {
	    cout << "Rule card not in player " << p << "'s hand" << endl;
	    record << "Rule card not in player " << p << "'s hand" << endl;
	    rule_card=0;
	  }
	  else hand[p].remove(rule_card);
	}
	current_winning=false;
	if (card>0 || rule_card>0) {
	  rule=rule_card%10;
	  if (winning(rule)==p) {
	    if (rule_card>0)
	      current_rule=rule;
	    current_winning=true;
	  }
	}
    
	
	if (!current_winning) {
	  active[p]=false;
	  num_active--;
	}

	duration << p << " " << rule_card << " " << card << endl;
	

	record << "player " << p;
	if (current_winning) record <<  " winning" << endl; else record << " eliminated" << endl;
	record_log();
	
      }
      p=(p+1)%num_players;
    } while (num_active>1);


    int winner=winning(0);
    record << "Winner: " << winner << endl;
    record << "Winning cards: ";
    print_list(highest, record);
    record << endl;
    print_log();

    //   cout << duration.str();
    return winner;
    
         
  }


};


int main(int argc, char *argv[])
{
  srand(time(0));// set random seed
  rand();
  
  if (argc<3) return 0;
	
  int i,j,g;

  num_players=0;
  for (i=1;i<argc;i++)
    if (argv[i][0]=='-') {
      
      if (i>=argc-1) {
	cerr << "Parameter Error!" << endl;
	return 0;
      }
      
      int j=atoi(argv[i+1]);
      switch (argv[i][1]) {
         case 'm': game_mode=j;break;
         case 'g': num_games=j;break;
      }
      i++;
    }
    else {
      if (num_players>=MAX_PLAYERS) {
	cerr << "TOO MANY PLAYERS!" << endl;
	return 0;
      }
      player_file[num_players]=(string)(argv[i]);
      num_players++;
    }

  if (game_mode>MAX_ROUNDS || (game_mode+1)*num_players>49) {
    cerr << "TOO MANY ROUNDS." << endl;
    return 0;
  }

  if (game_mode>0) num_rounds=game_mode;
  cout << "Number of Players: " << num_players << endl;
  cout << "Number of games: " << num_games << endl;
  cout << "Number of rounds per game: " << num_rounds << endl;
  cout << "Game mode: ";
  if (game_mode==0) cout << "long game" << endl;
  else cout << "short game" << endl;
  
  for (i=0; i<num_players; i++) cout << "Player " << i << ": " << player_file[i] << endl;
  
  int points[MAX_PLAYERS];
  int winner, max_score;
  for (i=0;i<num_players;i++) {
    points[i]=0;
    scores[i]=0;
  }



  for (g=0;g<num_games; g++) {
    cout << "Game " << g << ":" << endl;
    list<int> whole;
    for (i=1;i<=7;i++)
      for (j=1;j<=7;j++)
	whole.push_back(i*10+j);

    if (game_mode>0) {

      game *game1=new game(whole);
      winner=game1->game_play();
      points[winner]++;
      cout << "WINNER: " << winner << endl;
    } else {
        for (i=0;i<num_players;i++)
	  scores[i]=0;
	while(whole.size()>=num_players*8 && *max_element(scores,scores+num_players)<50-5*num_players) {
	  game *game1=new game(whole);
	  winner=game1->game_play();
	  for (list<int>::iterator it=game1->highest.begin();it!=game1->highest.end();it++) {
	    scores[winner]+=(int)(*it/10);
	    whole.remove(*it);
	  }

	  cout << "SCORES: ";
	  for (i=0;i<num_players;i++)
	    cout << scores[i] << " ";
	  cout << endl;
	}

	max_score=-1;
	for (i=0;i<num_players;i++)
	  if (scores[i]>max_score) {
	    max_score=scores[i];
	    winner=i;
	  }

	points[winner]++;
	cout << "WINNER: " << winner << endl;
    }
    cout << "Current scores: ";
    for (i=0; i<num_players; i++)
      cout << " " << points[i];
    cout << endl;
    
  }

  cout << "TOTAL POINTS: " << endl;
  for (i=0; i<num_players; i++)
    cout << "PLAYER " << i << ": " << points[i] << endl;


  return 0;
}

