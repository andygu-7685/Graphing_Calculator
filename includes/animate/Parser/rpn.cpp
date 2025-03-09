#include "rpn.h"











    RPN::RPN( Queue<Token*> input_q ){
        rpn_queue = input_q;
    }

    double RPN::operator()(int& errorFlag, double fnInput) {
        return rpn(errorFlag, rpn_queue, fnInput);
    }

    double RPN::rpn(int& errorFlag, Queue<Token*> input_q, double fnInput ){
        if(input_q.empty())             //default arg
            input_q = rpn_queue;
        return rpnAlgorithm(input_q, errorFlag, fnInput);
        //the Algorithm is in function.h
    }



    void RPN::set_input( Queue<Token*> input_q ){
        rpn_queue = input_q;
    }