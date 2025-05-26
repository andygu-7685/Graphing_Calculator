#include "rpn.h"

RPN::RPN( Queue<Token*> input_q ){
    rpn_queue = input_q;
}

double RPN::operator()(double fnInput) {
    return rpn(rpn_queue, fnInput);
}

double RPN::rpn(Queue<Token*> input_q, double fnInput ){
    if(!input_q.empty())             //default arg
        rpn_queue = input_q;
    return rpnAlgorithm(rpn_queue, fnInput);
}

void RPN::set_input( Queue<Token*> input_q ){
    rpn_queue = input_q;
}