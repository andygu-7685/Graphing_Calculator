#include "compare.h"

compare::compare(bool type): Operator("C"), _type(type){}

double compare::evaluate(double op1, double op2){
    if(_type)
        return (op1 > op2) ? op1 : op2;
    else
        return (op1 > op2) ? op2 : op1;
}