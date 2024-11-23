#include "shunting_yard.h"








    ShuntingYard::ShuntingYard( Queue<Token*> input_q ){
        sy_queue = input_q;
    }

    Queue<Token*> ShuntingYard::postfix( Queue<Token*> input_q){
        if(input_q.empty())             //default arg
            input_q = sy_queue;
        return syAlgorithm(input_q);
        //the Algorithm is in function.h
    }



    void ShuntingYard::infix( Queue<Token*> input_q ){
        sy_queue = input_q;
    }

    void ShuntingYard::infix( string inputStr , vector<string> fnLst){
        sy_queue = strToQueue(inputStr, fnLst, -1);
    }







