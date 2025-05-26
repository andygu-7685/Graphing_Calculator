#ifndef LEFTBRACKET_H
#define LEFTBRACKET_H

#include "token.h"

class LeftBracket : public Token{
    public:
    LeftBracket() : Token(7){}

    int get_prec()const override{ return 0; }
};
#endif