//current
#ifndef TRIG_H
#define TRIG_H

#include "operator.h"
#include "..\exception.h"

class Trig : public Operator{
    public:
    Trig(string trigFn = "sin");

    double evaluate(double uniInput) override;
    
    string get_trig()const override{ return _trig; }

    private:
    string _trig;               //hold the trig string
};
#endif