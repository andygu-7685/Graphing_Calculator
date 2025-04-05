#include "token.h"






    Token::Token(){
        type = 0;
    }

    Token::Token(int typeIn){
        type = typeIn;
    }

    double Token::evaluate(double left, double right){
        cout << "Token evaluate function excuted";
        return 0;
    }

    double Token::evaluate(double uniInput){
        cout << "Token evaluate function excuted";
        return 0;
    }

    double Token::evaluate(){
        cout << "Token evaluate function excuted";
        return 0;
    }

    double Token::get_int() const {
        cout << "Token get_int function excuted";
        return 0;
    }
    
    char Token::get_op()const {
        cout << "Token get_op function excuted";
        return 'a';
    }
    char Token::get_name()const {
        cout << "Token get_name function excuted";
        return 'a';
    }
    int Token::get_prec()const {
        cout << "Token get_prec function excuted";
        return -1;
    }

    string Token::get_trig()const {
        cout << "Token get_trig function excuted";
        return "a";
    }

    bool Token::get_ln()const {
        cout << "Token get_ln function excuted";
        return false;
    }

    void Token::set_base(double input){
        cout << "Token set_base function excuted";
    }




