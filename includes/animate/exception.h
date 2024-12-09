
#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include "constants.h"
#include "MyStack.h"
#include "Token.h"


using namespace std;





int FunctionException(vector<string> fnLst, int fnIndex, int outerfn);

int DefinitionException(bool isDef);

int syException(Stack<Token*>& op_stack);

int rpnException(Stack<Token *> int_stack, bool invert = false);

int InputException();

int divideException(double inputVal, char _op);

int trigException(double inputVal);

int logException(double inputVal);

int parenException(int ctr);


int DomainException(int domainFlag);

int DomainException(double low, double high);





#endif