#ifndef EXCEPTION_H
#define EXCEPTION_H

//#include "constants.h"
#include ".\Tools\MyStack.h"
#include ".\Tokens\Token.h"

using namespace std;

enum ecodes {fnE1, fnE2, fnE3, defE, defineE, syE, rpnE1, rpnE2, inputE, divideE, trigE1, trigE2, logE, parenE, DomainE1, DomainE2, CommaE, invalidE, DefFlag = 100};

bool dequ(double left, double right, double epsilon = 0.00000000001);

class MyException : public exception{
    public:
    MyException() : _code(-1), _msg("default"){}
    MyException(int ecode, string msg) : _code(ecode), _msg(msg){}
    int code() const{ return _code; }
    const char* what() const noexcept override { return _msg.c_str(); }

    private:
    int _code;
    string _msg;
};



void FunctionException(const vector<string>& fnLst, char fnKey, vector<bool> visited);

void DefinitionException(const vector<string>& fnLst, string currentDef, int defIndex);

void syException(const Stack<Token*>& op_stack);

void rpnException1(const Stack<Token *>& int_stack);

void rpnException2(const Stack<Token *>& int_stack);

void InputException();

void divideException(double inputVal, char _op);

void trigException1(double inputVal);

void trigException2(double inputVal);

void logException(double inputVal);

void parenException(const Stack<char>& match);

void commaException(const Stack<char>& match);

void DomainException1(int domainFlag);

void DomainException2(int domainFlag);

void DomainException3(double low, double high);

#endif