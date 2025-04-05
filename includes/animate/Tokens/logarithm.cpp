#include "logarithm.h"

Logarithm::Logarithm(double base, bool logType) : Operator("L"), _logType(logType), _base(base){}

double Logarithm::evaluate(double uniInput){
    try{
        logException(_base);
    }
    catch(const MyException e){
        throw;
    }
    return (log(uniInput) / log(_base));
}