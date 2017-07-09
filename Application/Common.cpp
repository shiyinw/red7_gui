//
//  Common.cpp
//  Red7
//
//  Created by Shiyin Wang on 05/07/2017.
//  Copyright © 2017 Shiyin Wang. All rights reserved.
//

#include "Common.h"

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

bool rule_compare(list<int>a, list<int>b, int r)
{
    if(r==7) return compare(red(a), red(b));
    else if(r==6) return compare(orange(a), orange(b));
    else if(r==5) return compare(yellow(a), yellow(b));
    else if(r==4) return compare(green(a), green(b));
    else if(r==3) return compare(blue(a), blue(b));
    else if(r==2) return compare(indigo(a), indigo(b));
    else if(r==1) return compare(violet(a), violet(b));
    else
    {
        cout<<"rule_compare() Error for rule input"<<endl;
        return 0;
    }
}

void print(list<int> h1, list<int> p1, list<int> h2, list<int> p2, int r)
{
    cout<<"(Player1)hand:";
    for(list<int>::iterator i=h1.begin(); i!=h1.end(); i++)
        cout<<*i<<" ";
    cout<<"palette:";
    for(list<int>::iterator i=p1.begin(); i!=p1.end(); i++)
        cout<<*i<<" ";
    cout<<endl<<"(Player2)hand:";
    for(list<int>::iterator i=h2.begin(); i!=h2.end(); i++)
        cout<<*i<<" ";
    cout<<"palette:";
    for(list<int>::iterator i=p2.begin(); i!=p2.end(); i++)
        cout<<*i<<" ";
    cout<<endl<<"Rule: "<<r<<endl;
}

void print(list<int> a)
{
    for(list<int>::iterator i= a.begin();i!=a.end();i++)
        cout<<"rule "<<(*i)/100<<"  palette"<<(*i)%100<<"   ";
    cout<<endl;
}
