//
//  Common.h
//  Red7
//
//  Created by Shiyin Wang on 05/07/2017.
//  Copyright © 2017 Shiyin Wang. All rights reserved.
//

#ifndef COMMON_H
#define COMMON_H

#include <list>
#include <iostream>
using namespace std;

bool compare(list<int> a, list<int> b);   //if a is higher than b, return true

list<int> red(list<int> a);
list<int> orange(list<int> a);
list<int> yellow(list<int> a);
list<int> green(list<int> a);
list<int> blue(list<int> a);
list<int> indigo(list<int> a);
list<int> violet(list<int> a);

bool rule_compare(list<int>a, list<int>b, int r);

void print(list<int> h1, list<int> p1, list<int> h2, list<int> p2, int r);

void print(list<int> a);

#endif
