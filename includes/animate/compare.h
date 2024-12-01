#ifndef COMPARE_H
#define COMPARE_H







#include "token.h"
#include "operator.h"



class compare : public Operator{
    public:

    compare();

    compare(bool type);

    double evaluate(double op1, double op2) override;


    private:
    bool cmpType;                  //true if max, false if min


};





#endif