#ifndef OPERATOR_H
#define OPERATOR_H

#include <cassert>
#include "token.h"
#include "..\exception.h"

class Operator : public Token{
    public:
    Operator(string operand);

    virtual double evaluate(double left, double right) override;

    char get_op()const override{ return _op; }
    int get_prec()const override{ return _prec; }

    private:
    int _prec;
    char _op;               //hold the operator char
};
#endif