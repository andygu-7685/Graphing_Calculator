#ifndef TRIG_H
#define TRIG_H







#include "token.h"
#include "operator.h"



class Trig : public Operator{
    public:

    Trig();

    Trig(string trigFn);

    double evaluate(double uniInput) override;

    char get_trig()const override{ return _trig[2]; }

    private:
    string _trig;               //hold the trig string


};





#endif