#include "logarithm.h"







Logarithm::Logarithm() : Operator("L"){
    _logType = false;
    _base = 1;
    errorFlag = 0;
}

Logarithm::Logarithm(double base, bool LN) : Operator("L"){
    _logType = LN;
    _base = base;
    errorFlag = 0;
}

double Logarithm::evaluate(double uniInput){
    errorFlag = logException(uniInput);
    if(errorFlag != 0){ return 0.0; }
    return (log(uniInput) / log(_base));
}


int Logarithm::errorReport(){
    return errorFlag;
}