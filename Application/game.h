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

#include "colors.h"


#define LOG_FILE "log.txt"
#define PLAYER_OUTPUT "output.txt"
#define MAX_PLAYERS 4
#define MAX_ROUNDS 12
#define TIME_LIMIT 2

using namespace std;


#ifndef GAME_H
#define GAME_H
class game
{
  ostringstream record; //all information of the current game

  ostringstream duration; //the public information so far

  int num_players;
  int num_rounds=7;
  int scores[MAX_PLAYERS];
  string player_file[MAX_PLAYERS];


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
#endif
