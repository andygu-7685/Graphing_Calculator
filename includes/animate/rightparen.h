#ifndef RightParen_H
#define RightParen_H








#include "token.h"








class RightParen : public Token{
    public:

    RightParen() : Token(5){}

    int get_prec()const override{ return 0; }

    private:



};






#endif