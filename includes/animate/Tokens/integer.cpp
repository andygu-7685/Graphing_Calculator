#include "integer.h"

Integer::Integer(double num) : Token(1), _num(num){}

Integer::Integer(string numStr) : Token(1){
    try{
        _num = stod(numStr);
    }
    catch(const invalid_argument& e){
        assert(false && "Integer.cpp::Integer(string numStr); Error: invalid argument");
    }
    catch(const out_of_range& e){
        assert(false && "Integer.cpp::Integer(string numStr); Error: out of range");
    }
}

Integer::Integer(char numChar) : Token(1), _num(numChar - '0'){
    assert(numChar - '0' < 10);
}