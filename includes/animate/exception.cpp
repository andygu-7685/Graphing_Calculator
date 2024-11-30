#include "exception.h"






Exception::Exception() : msg(""), errorCode(0)
{}
Exception::Exception(string str, int num) : msg(str), errorCode(num)
{}




string Exception::Report(int eCode)
{
    return msg;
}

int Exception::ReportCode(){
    return errorCode;
}



Exception& Exception::operator =(const Exception& right){
    msg = right.msg;
    errorCode = right.errorCode;
    return *this;
}



int FunctionException(vector<string> fnLst, int fnIndex, int outerfn){
    try{
        if(fnIndex >= 10 || fnIndex < 0){
            throw Exception("Error: Invalid function name.", 1);
        }

        if(fnIndex == outerfn){
            throw Exception("Error: the function should not self reference.", 2);
        }

        if(fnLst[fnIndex] == "NaN"){
            throw Exception("Error: the function you referenced do not exist.", 3);
        }

        return Exception().ReportCode();
    }
    catch(Exception e){
        return e.ReportCode();
    }
}














int syException(Stack<Token*>& op_stack, bool unkInput){
    try{
        if(op_stack.empty() && unkInput == false){
            throw Exception("Error: missing leftparen.", 4);
        }
        if(unkInput){
            //never gets excuted
            throw Exception("Error: unknown Input.", 5);
        }
        return Exception().ReportCode();
    }
    catch(Exception e){
        return e.ReportCode();
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




















int rpnException(Stack<Token *> int_stack, int condition){
    try{
        if(!int_stack.empty() && condition == 3)
            throw Exception("Error: int_stack should be empty.", 7);

        if(int_stack.empty() && (condition == 0 || condition == 1 || condition == 2))
            throw Exception("Error: missing operand.", 6);
        
        return Exception().ReportCode();
    }
    catch(Exception e){
        return e.ReportCode();
    }
}






