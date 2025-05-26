#ifndef FUNCTION_H
#define FUNCTION_H

#include "operator.h"
#include "integer.h"
#include "comma.h"
#include "leftparen.h"
#include "rightparen.h"
#include "variable.h"
#include "trig.h"
#include "logarithm.h"
#include "compare.h"
#include "leftbracket.h"
#include "rightbracket.h"
#include "..\Tools\MyQueue.h"
#include "..\Tools\MyStack.h"
#include "..\constants.h"
#include "..\exception.h"
#include <algorithm> 

double ConvertDigit(string& digits, Queue<Token*>& finalQueue);
Queue<Token*> strToQueue(string inputStr, vector<string> fnLst, int cmd = 0);
double rpnAlgorithm(Queue<Token*> input_q, double fnInput = 0);
Queue<Token*> syAlgorithm( Queue<Token*> input_q);
void popUntil(Queue<Token*>& total_queue, Stack<Token*>& op_stack, int type = 4);

class Function : public Operator{
    public:
    Function() : Operator("F"){}
    Function(const vector<string>& fnLst, int outerfn = -1, double varInput = 0);

    double evaluate(double uniInput) override;
    double evaluate() override;
    void set_Input(double varInput){ Input = varInput; }

    private:
    Queue<Token*> fnQueue;
    int fnIndex;
    double Input;
};
#endif