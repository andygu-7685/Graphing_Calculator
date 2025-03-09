#ifndef TRIG_H
#define TRIG_H







#include "token.h"
#include "operator.h"
#include "..\exception.h"



class Trig : public Operator{
    public:

    Trig();

    Trig(string trigFn);

    double evaluate(double uniInput) override;
    int errorReport()override { return errorFlag; }
    string get_trig()const override{ return _trig; }

    private:
    string _trig;               //hold the trig string
    int errorFlag;


};





#endif