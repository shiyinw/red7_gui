#include <string>  
#include <fstream>  
#include <sstream>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <string>
using namespace std;

int main()
{
	std::ifstream t("log_p.txt");  
	std::stringstream buffer;  
	//buffer << t.rdbuf();  
	//std::string contents(buffer.str());
	//cout<<contents;
	//istringstream ssin(contents);
	string line;
	string rule, p1hand, p1p, p2hand, p2p, announce;
	string win, buf;
	if(t)
	{
		while(!t.eof())
		{
			getline(t, rule);
			
			if(!getline(t, p1hand)) break;
			else {
				std::stringstream buffer;
				buffer<<p1hand;
			    std::string contents(buffer.str());
				istringstream ssin(contents);
				string a;
				while(ssin>>a)
				{
					cout<<atoi(a)<<",";
				}
			}
			
			
			if(!getline(t, p1p)) break;
			
			getline(t, p2hand);
			
			getline(t, p2p);
			
			getline(t, announce);
			

			if(announce=="1 eliminated"||announce=="0 eliminated")
			{
				cout<<announce<<endl;
				getline(t, buf);
				getline(t, buf);
				getline(t, buf);
				getline(t, buf);
				getline(t, win);
				cout<<"win card: "<<win<<endl;
			}
			else if(announce=="0 winning"||announce=="1 winning")
			{
				//cout<<"winning..."<<endl;
			}
			else cout<<"announcement error"<<endl;
		}
	}
	else
		cout<<"no such file"<<endl;
	return 0;
}