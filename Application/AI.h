//
//  AI.hpp
//  Red7
//
//  Created by Shiyin Wang on 05/07/2017.
//  Copyright © 2017 Shiyin Wang. All rights reserved.
//

#ifndef AI_H
#define AI_H

#include <list>
#include <iostream>
#include "Common.h"
using namespace std;

class AI
{
public:
    list<int> my_hand, my_palette, op_palette;
    list<int> _strategy;
    int _rule;
    bool alive;
public:
    AI()
    {
        alive=1;
    }
    void see(list<int> a, list<int>b, list<int>c, int r)
    {
        my_hand = a;
        my_palette = b;
        op_palette = c;
        _rule=r;
    }
    void get_strategy()//通用函数，返回所有可能的打法
    {
        _strategy.clear();
        
        for(list<int>::iterator i = my_hand.begin(); i!=my_hand.end(); i++)//只放牌
        {
            list<int> add = my_palette;
            add.push_back(*i);
            if(rule_compare(add, op_palette, _rule))
            {
                _strategy.push_back(*i);
            }
        }
        for(list<int>::iterator i = my_hand.begin(); i!=my_hand.end(); i++)
        {
            int new_rule = (*i)%10;
            if(rule_compare(my_palette, op_palette, new_rule))//只更改规则
            {
                _strategy.push_back((*i)*100);
            }
            for(list<int>::iterator j = my_hand.begin(); j!=my_hand.end(); j++)//规则+牌
            {
                if(i!=j)
                {
                    list<int> add = my_palette;
                    add.push_back(*j);
                    if(rule_compare(add, op_palette, new_rule))
                    {
                        _strategy.push_back((*i)*100+(*j));
                    }
                }
            }
        }
        //print(_strategy);
        // 出牌表示为四位整数， 如 7275表示将72放到规则牌， 将75加入Palette
        
    }
    virtual int play()=0;
};

class Trivial:public AI
{
public:
    int play();
    Trivial()
    {
        alive=1;
    }
};





#endif /* AI_h */
