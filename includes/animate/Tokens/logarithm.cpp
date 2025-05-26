#include "logarithm.h"

Logarithm::Logarithm(double base, bool logType) : Operator("L"), _logType(logType), _base(base){}

double Logarithm::evaluate(double uniInput){
    logException(_base);
    return (log(uniInput) / log(_base));
}