#include "operator.h"
#include <cassert>





    Operator::Operator() : Token(2){
        _op = ' ';
        _prec = 0;
    }

    Operator::Operator(string operand) : Token(2){
        _op = operand[0];
        switch(operand[0]){
            case '+':
                _prec = 1;
            break;
            case '-':
                _prec = 1;
            break;
            case '*':
                _prec = 2;
            break;
            case '/':
                _prec = 2;
            break;
            case '^':
                _prec = 3;
            break;
            case 'F':
                _prec = 4;
            break;
            case 'T':
                _prec = 4;
            break;
            default:
                cout << "Invalid Operand in constructor\n";
            break;
        }
    }


    double Operator::evaluate(double left, double right){
        switch(_op){
            case '+':
                return (left + right);
            break;
            case '-':
                return (left - right);
            break;
            case '*':
                return (left * right);
            break;
            case '/':
                return (left / right);
            break;
            case '^':
                return (pow(left, right));
            break;
            default:
                cout << "Invalid Operand in Evaluate\n";
                return 0;
            break;
        }
    }

    double Operator::evaluate(){
        cout << "child virtual evaluate excuted";
        return 0;
    }

    int Operator::errorReport(){
        cout << "child virtual errorReport excuted";
        return 0;
    }
