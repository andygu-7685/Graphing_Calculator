#ifndef RPN_H
#define RPN_H

#include "..\Tokens\function.h"
#include "..\Tokens\operator.h"
#include "..\Tokens\integer.h"
#include "..\Tokens\leftparen.h"
#include "..\Tokens\rightparen.h"
#include "..\Tokens\variable.h"
#include "..\Tools\MyQueue.h"
#include "..\Tools\MyStack.h"

class RPN{
    public:
    RPN( Queue<Token*> input_q );

    double operator()(double fnInput = 0);
    double rpn(Queue<Token*> input_q = Queue<Token*>(), double fnInput = 0 );
    void set_input( Queue<Token*> input_q );

    private:
    Queue<Token*> rpn_queue;
};
#endif