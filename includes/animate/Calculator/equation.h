#ifndef EQUATION_H
#define EQUATION_H

#include<string>

using namespace std;

struct equation
{
    string expression;
    bool isFn;
    bool isDisplay;

    equation(string expr, bool fn, bool display) : expression(expr), isFn(fn), isDisplay(display){}

};


#endif 