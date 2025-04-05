#include "operator.h"

Operator::Operator(string operand = " ") : Token(2){
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
        //Function
        case 'F':
            _prec = 4;
        break;
        //Trig
        case 'T':
            _prec = 4;
        break;
        //Compare
        case 'C':
            _prec = 4;
        break;
        //Logarithm
        case 'L':
            _prec = 4;
            break;
        default:
            cout << "Warning: Invalid operator in constructor\n";
            _prec = 0;
        break;
    }
}

double Operator::evaluate(double left, double right){
    try{
        divideException(right, _op);
    }
    catch(const MyException e){
        throw;
    }

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
            cout << "Warning: Invalid operator in evaluate\n";
            return 0;
        break;
    }
}