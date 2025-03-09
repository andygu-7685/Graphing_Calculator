#include "shunting_yard.h"








    ShuntingYard::ShuntingYard( Queue<Token*> input_q ){
        sy_queue = input_q;
    }

    Queue<Token*> ShuntingYard::postfix(int& errorFlag, Queue<Token*> input_q){
        if(input_q.empty())             //default arg
            input_q = sy_queue;
        return syAlgorithm(input_q, errorFlag);
        //the Algorithm is in function.h
    }



    void ShuntingYard::infix( Queue<Token*> input_q){
        sy_queue = input_q;
    }

    void ShuntingYard::infix( string inputStr , vector<string> fnLst, int& errorFlag){
        sy_queue = strToQueue(inputStr, fnLst, -1, errorFlag);
    }







