#ifndef LOGARITHM_H
#define LOGARITHM_H

#include "operator.h"
#include "..\exception.h"

class Logarithm : public Operator{
    public:
    //must be this default arg b/c of the parsing algorithm
    Logarithm(double base = 1, bool logType = false);

    double evaluate(double uniInput) override;

    void set_base(double input) override{ _base = input; }

    bool get_ln()const override { return _logType; }

    private:
    double _base;               //base of log
    bool _logType;              //true if ln(), false if log()
};
#endif