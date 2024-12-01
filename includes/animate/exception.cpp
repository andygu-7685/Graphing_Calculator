#include "exception.h"





int FunctionException(vector<string> fnLst, int fnIndex, int outerfn){
    try{
        if(fnIndex >= 10 || fnIndex < 0)
            throw 1;             //"Error: Invalid function name."
        if(fnIndex == outerfn)
            throw 2;             //"Error: the function should not self reference."
        if(fnLst[fnIndex] == "NaN")
            throw 3;             //"Error: the function you referenced do not exist."
        return 0;
    }
    catch(int e){
        return e;
    }
}














int syException(Stack<Token*>& op_stack){
    try{
        if(op_stack.empty())
            throw 4;            //"Error: missing leftparen.";
        return 0;
    }
    catch(int e){
        return e;
    }
}




int InputException(){
    //always return an error code 8, when input is unk
    return 8;
}



int divideException(double inputVal, char _op){
    if(inputVal == 0.0 && _op == '/')
        return 9;
    return 0;
}


int parenException(int ctr){
    if(ctr != 0)
        return 10;
    return 0;
}








int rpnException(Stack<Token*> int_stack, bool invert){
    try{
        if(!int_stack.empty() && invert == true)
            throw 7;                //"Error: int_stack should be empty."
        if(int_stack.empty() && invert == false)
            throw 6;                 //"Error: missing operand."
        return 0;
    }
    catch(int e){
        return e;
    }
}






