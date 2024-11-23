#include "integer.h"




    Integer::Integer() : Token(1){
        num = 0;
    }

    Integer::Integer(double numIn) : Token(1){
        num = numIn;
    }

    Integer::Integer(string numStr) : Token(1){
        num = numStr[0] - '0';
    }