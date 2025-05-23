#include "exception.h"















int FunctionException(vector<string> fnLst, int fnIndex, int outerfn){
    try{
        if(fnIndex >= 10 || fnIndex < 0)
            throw 1;             //"Error: Invalid function name."
        if(fnIndex == outerfn)
            throw 2;             //"Error: the function should not self reference."
        if(fnLst[fnIndex] == " ")
            throw 3;             //"Error: the function you referenced do not exist."
        if(outerfn <= 0 && outerfn > -10)
            throw 11;              //for function definition
        return 0;
    }
    catch(int error){ 
        cout << "error code: " << error << endl;
        return error;
    }
}


int DefinitionException(bool isDef){
    if(isDef)
        return 11;
    return 0;
}



int syException(Stack<Token*>& op_stack){
    try{
        if(op_stack.empty())
            throw 4;            //"Error: missing leftparen.";
        return 0;
    }
    catch(int error){
        return error;
    }
}




int InputException(){
    //always return an error code 8, when input is unk
    return 8;
}



void divideException(double inputVal, char _op){
    if(inputVal == 0.0 && _op == '/')
        throw MyException(divideE, "Error: divde operator cannot divide by 0");
}


void trigException1(double inputVal){
    if(fmod(inputVal, pi) == 0.0)
        throw MyException(trigE1, "Error: cot evaluate to undefined");
}

void trigException2(double inputVal){
    if(dequ(fmod(inputVal, pi), pi/2.0))
        throw MyException(trigE2, "Error: tan evaluate to undefined");
}


void logException(double inputVal){
    if(inputVal == 0 || inputVal == 1)
        throw MyException(logE, "Error: log base cannot be 0 or 1");
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
    catch(int error){
        return error;
    }
}




int DomainException(int domainFlag){
    if(domainFlag == 1){
        return 14;
    }
    return 0;
}




int DomainException(double low, double high){
    if(high <= low)
        return 15;
    return 0;
}







