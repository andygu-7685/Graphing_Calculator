#ifndef INTEGER_H
#define INTEGER_H





#include "token.h"







class Integer : public Token{
    public:

    Integer();

    Integer(double numIn);

    Integer(string numStr);

    double get_int() const override{ return num; }

    private:
    double num;


};



#endif