#include "compare.h"





compare::compare(): Operator("C"){}

compare::compare(bool type): Operator("C"){
    cmpType = type;
}


double compare::evaluate(double op1, double op2){
    if(cmpType){
        if(op1 > op2)
            return op1;
        return op2;
    }
    else{
        if(op1 > op2)
            return op2;
        return op1;
    }
}