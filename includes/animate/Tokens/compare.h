#ifndef COMPARE_H
#define COMPARE_H

#include "operator.h"

class compare : public Operator{
    public:
    compare(bool type = true);
    
    double evaluate(double op1, double op2) override;

    private:
    bool _type;                  //true if max, false if min
};
#endif