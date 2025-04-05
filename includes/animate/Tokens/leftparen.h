#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include "token.h"

class LeftParen : public Token{
    public:
    LeftParen() : Token(4){}
    
    int get_prec()const override{ return 0; }
};
#endif