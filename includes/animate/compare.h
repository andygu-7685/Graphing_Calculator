#ifndef TRIG_H
#define TRIG_H







#include "token.h"
#include "operator.h"



class compare : public Operator{
    public:

    compare();



    double evaluate(double op1, double op2) override;

    char get_trig()const override{ return _trig[2]; }

    private:
    string _trig;               //hold the trig string


};





#endif