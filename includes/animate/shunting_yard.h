#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H




#include "operator.h"
#include "integer.h"
#include "leftparen.h"
#include "rightparen.h"
#include "variable.h"
#include "function.h"
#include "MyQueue.h"
#include "MyStack.h"














class ShuntingYard{
    public:

    ShuntingYard(){

    }

    ShuntingYard( Queue<Token*> input_q );

    Queue<Token*> postfix( Queue<Token*> input_q = Queue<Token*>() );

    void infix( Queue<Token*> input_q );

    void infix( string inputStr , vector<string> fnLst);


    private:
    Queue<Token*> sy_queue;


};






#endif

