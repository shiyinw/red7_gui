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

#ifndef COLORS_H
#define COLORS_H

pid_t pid;

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

#endif
