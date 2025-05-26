#include "shunting_yard.h"

ShuntingYard::ShuntingYard( Queue<Token*> input_q ){
    sy_queue = input_q;
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> input_q){
    if(!input_q.empty())             //default arg
        sy_queue = input_q;
    return syAlgorithm(sy_queue);
}

void ShuntingYard::infix( Queue<Token*> input_q){
    sy_queue = input_q;
}

void ShuntingYard::infix( string inputStr , vector<string> fnLst){
    sy_queue = strToQueue(inputStr, fnLst, 0);
}