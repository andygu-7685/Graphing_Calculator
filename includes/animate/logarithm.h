#ifndef LOGARITHM_H
#define LOGARITHM_H







#include "token.h"
#include "operator.h"
#include "exception.h"



class Logarithm : public Operator{
    public:

    Logarithm();

    Logarithm(double base, bool LN);

    double evaluate(double uniInput) override;
    bool get_ln()const override { 
        return _logType; 
    }
    void set_base(double input) override{ 
        _base = input; 
    }
    int errorReport() override;

    private:
    double _base;               //base of log
    int errorFlag;
    bool _logType;              //true if ln(), false if log()


};





#endif