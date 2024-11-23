#include "rpn.h"











    RPN::RPN( Queue<Token*> input_q ){
        rpn_queue = input_q;
    }

    double RPN::operator()(double fnInput) {
        return rpn(rpn_queue, fnInput);
    }

    double RPN::rpn( Queue<Token*> input_q, double fnInput ){
        if(input_q.empty())             //default arg
            input_q = rpn_queue;
        return rpnAlgorithm(input_q, fnInput);
        //the Algorithm is in function.h
    }



    void RPN::set_input( Queue<Token*> input_q ){
        rpn_queue = input_q;
    }