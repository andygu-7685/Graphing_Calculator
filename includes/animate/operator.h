#ifndef OPERATOR_H
#define OPERATOR_H







#include "token.h"







class Operator : public Token{
    public:

    Operator();

    Operator(string operand);

    double evaluate(double left, double right);

    virtual double evaluate() override;

    char get_op()const override{ return _op; }
    int get_prec()const override{ return _prec; }

    private:
    int _prec;
    char _op;               //hold the operator char


};





#endif