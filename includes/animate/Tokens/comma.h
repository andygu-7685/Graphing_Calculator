#ifndef COMMA_H
#define COMMA_H

#include "token.h"

class Comma : public Token{
    public:
    Comma() : Token(6){}

    int get_prec()const override{ return 0; }
};
#endif