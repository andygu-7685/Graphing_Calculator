
#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept> // For standard exceptions
#include <string>
#include "constants.h"
#include "MyStack.h"
#include "Token.h"


using namespace std;





int FunctionException(vector<string> fnLst, int fnIndex, int outerfn);

int syException(Stack<Token*>& op_stack, bool unkInput);

int rpnException(Stack<Token *> int_stack, int condition);

int InputException();

int divideException(double inputVal, char _op);


class Exception
{
public:
    Exception();
    Exception(string msg, int num);

    Exception& operator =(const Exception& right);
    string Report(int eCode);
    int ReportCode();
private:
    string msg;
    int errorCode;
};






#endif