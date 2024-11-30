#ifndef FUNCTION_H
#define FUNCTION_H





#include <string>
#include <vector>
#include "operator.h"
#include "integer.h"
#include "leftparen.h"
#include "rightparen.h"
#include "variable.h"
#include "trig.h"
#include "MyQueue.h"
#include "MyStack.h"
#include "exception.h"



void ConvertDigit(Stack<char>& digitStack, Queue<Token*>& finalStack);

int ConvertChar(Queue<char>& charQueue, Queue<Token*>& finalQueue, vector<string> fnLst, int outerfn);

void clearQueue(Queue<char>& charQueue);

Queue<Token*> strToQueue(string inputStr, vector<string> fnLst, int outerfn, int& errorFlag);

double rpnAlgorithm(Queue<Token*> input_q, int& errorFlag, double fnInput = 0);

Queue<Token*> syAlgorithm( Queue<Token*> input_q, int& errorFlag);



class Function : public Operator{
    public:

    Function() : Operator("F"){}

    Function(string fnStr, double varInput, vector<string> fnLst, int outerfn = -1);

    int errorReport()override { return errorFlag; }

    double evaluate(double uniInput) override;

    void set_Input(double varInput){ Input = varInput; }

    private:
    Queue<Token*> fnQueue;
    double Input;
    int errorFlag;

};



#endif