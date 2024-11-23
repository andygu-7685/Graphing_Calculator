#ifndef RPN_H
#define RPN_H













#include "function.h"
#include "operator.h"
#include "integer.h"
#include "leftparen.h"
#include "rightparen.h"
#include "variable.h"
#include "MyQueue.h"
#include "MyStack.h"




class RPN{
    public:

    RPN(){}

    RPN( Queue<Token*> input_q );

    double operator()(double fnInput = 0);

    double rpn( Queue<Token*> input_q = Queue<Token*>(), double fnInput = 0 );

    void set_input( Queue<Token*> input_q );

    private:
    Queue<Token*> rpn_queue;


};



#endif