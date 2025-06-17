#include "exception.h"








bool dequ(double left, double right, double epsilon){
    return fabs(left - right) < epsilon ? true : false;
}









void FunctionException(const vector<string>& fnLst, char fnKey, vector<bool> visited) {
    if(fnKey > 126 || fnKey < 33){
        throw MyException(fnE1, "Error: Invalid function name");
    }
    else if (visited[fnIndex]) {
        // Already visited in the current path => circular reference
        throw MyException(fnE2, "Error: detected circular definition");
    }
    else if(fnLst[fnIndex] == " "){
        throw MyException(fnE3, "Error: function referenced do not exist");
    }

    
    visited[fnIndex] = true;
    string target = fnLst[fnIndex];
    int pos = target.find("F");

    while (pos != string::npos) {
        if ((pos + 2) < target.size() && target[pos + 2] == '(') 
            FunctionException(fnLst, target[pos + 1] - '0', visited);
        pos++;
        pos = target.find("F", pos);
    }
}

void DefinitionException(const vector<string>& fnLst, string currentDef, int defIndex) {
    if(defIndex > 9 || defIndex < 0){
        throw MyException(defE, "Error: Invalid definition name");
    }
    vector<bool> visited = vector<bool>(10, false);
    visited[defIndex] = true;
    int pos = currentDef.find("F");

    while (pos != string::npos) {
        if ((pos + 2) < currentDef.size() && currentDef[pos + 2] == '(')
            FunctionException(fnLst, currentDef[pos + 1] - '0', visited);
        pos++;
        pos = currentDef.find("F", pos);
    }
}



void syException(const Stack<Token*>& op_stack){
    if(op_stack.empty())
        throw MyException(syE, "Error: Missing left paren");
}




void InputException(){
    //always throw, when input is does not match any keyword
    throw MyException(inputE, "Error: Unknown Input");
}



void divideException(double inputVal, char _op){
    if(inputVal == 0.0 && _op == '/')
        throw MyException(divideE, "Error: divde operator cannot divide by 0");
}


void trigException1(double inputVal){
    if(fmod(inputVal, 3.1415926) == 0.0)
        throw MyException(trigE1, "Error: cot evaluate to undefined");
}

void trigException2(double inputVal){
    if(dequ(fmod(inputVal, 3.1415926), 3.1415926/2.0))
        throw MyException(trigE2, "Error: tan evaluate to undefined");
}


void logException(double inputVal){
    if(inputVal == 0 || inputVal == 1)
        throw MyException(logE, "Error: log base cannot be 0 or 1");
}





//The must be empty after sy algorithm
void parenException(const Stack<char>& match){
    if(!match.empty())
        throw MyException(parenE, "Error: paren did not match");
}


void commaException(const Stack<char>& match){
    if(match.empty())
        throw MyException(parenE, "Error: comma did not match");
}




// void rpnException(Stack<Token*> int_stack, bool invert){
//         if(!int_stack.empty() && invert == true)
//             throw 7;                //"Error: int_stack should be empty."
//         if(int_stack.empty() && invert == false)
//             throw 6;                 //"Error: missing operand."
// }

void rpnException1(const Stack<Token*>& int_stack){
    if(!int_stack.empty())
        throw MyException(rpnE1, "Error: int_stack should be empty");                //"Error: int_stack should be empty."
}

void rpnException2(const Stack<Token*>& int_stack){
    if(int_stack.empty())
        throw MyException(rpnE2, "Error: missing operand");                 //"Error: missing operand."
}




void DomainException1(int domainFlag){
    if(domainFlag != 0)
        throw MyException(DomainE1, "Error: Domain redefinition detected");
}

void DomainException2(int domainFlag){
    if(domainFlag != 1)
        throw MyException(DomainE1, "Error: Missing left bracket");
}




void DomainException3(double low, double high){
    if(high <= low)
        throw MyException(DomainE2, "Error: Upper bound should not be lower than lower bound");
}



void commaException(int closest){
    if(closest == 0)
        throw MyException(CommaE, "Error: Incomplete argument or domain");
}




