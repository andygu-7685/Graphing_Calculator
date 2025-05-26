#ifndef RIGHTBRACKET_H
#define RIGHTBRACKET_H

#include "token.h"

class RightBracket : public Token{
    public:
    RightBracket() : Token(8){}

    int get_prec()const override{ return 0; }
};
#endif