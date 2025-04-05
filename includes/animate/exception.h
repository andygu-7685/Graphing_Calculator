#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "constants.h"
#include ".\Tools\MyStack.h"
#include ".\Tokens\Token.h"

using namespace std;

enum ecodes {functionE, defineE, syE, rpnE, inputE, divideE, trigE1, trigE2, logE, parenE, DomainE1, DomainE2};

bool dequ(double left, double right, double epsilon = _EPSILON){
    return fabs(left - right) < epsilon ? true : false;
}

class MyException : public exception{
    public:
    MyException(int ecode, string msg) : _code(ecode), _msg(msg){}
    int code() const{ return _code; }
    const char* what() const noexcept override { return _msg.c_str(); }

    private:
    int _code;
    string _msg;
};





int FunctionException(vector<string> fnLst, int fnIndex, int outerfn);

int DefinitionException(bool isDef);

int syException(Stack<Token*>& op_stack);

int rpnException(Stack<Token *> int_stack, bool invert = false);

int InputException();

void divideException(double inputVal, char _op);

void trigException1(double inputVal);

void trigException2(double inputVal);

void logException(double inputVal);

int parenException(int ctr);

void DomainException(int domainFlag);

void DomainException(double low, double high);











#endif