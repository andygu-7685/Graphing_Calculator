#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "..\Tokens\operator.h"
#include "..\Tokens\integer.h"
#include "..\Tokens\leftparen.h"
#include "..\Tokens\rightparen.h"
#include "..\Tokens\variable.h"
#include "..\Tokens\function.h"
#include "..\Tools\MyQueue.h"
#include "..\Tools\MyStack.h"

class ShuntingYard{
    public:
    ShuntingYard( Queue<Token*> input_q );

    Queue<Token*> postfix(Queue<Token*> input_q = Queue<Token*>());
    void infix( Queue<Token*> input_q );
    void infix( string inputStr , vector<string> fnLst);

    private:
    Queue<Token*> sy_queue;
};
#endif