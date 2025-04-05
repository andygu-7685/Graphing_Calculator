#ifndef INTEGER_H
#define INTEGER_H

#include "token.h"
#include <cassert>

class Integer : public Token{
    public:
    Integer(double num = 0.0);
    Integer(string numStr);
    Integer(char numChar);

    double get_int() const override{ return _num; }

    private:
    double _num;
};
#endif