#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

//0 = empty
//1 = number
//2 = operator
//3 = variable
//4 = rightparen
//5 = leftparen
//6 = comma
//7 = leftbracket
//8 = rightbracket
class Token{
    public:
    Token(int typeIn = 0);

    friend ostream& operator<<(ostream& outs, const Token& rhs){
        switch(rhs.type){
            case 1:
                cout << rhs.get_int();
            break;
            case 2:
                cout << rhs.get_op();
            break;
            case 3:
                cout << "x";
            break;
            case 4:
                cout << "(";
            break;
            case 5:
                cout << ")";
            break;
            case 6:
                cout << ",";
            break;
            case 7:
                cout << "{";
            break;
            case 8:
                cout << "}";
            break;
            default:
                cout << "Warning: Invalid token in cout\n";
            break;
        }
        return outs;
    }

    virtual double evaluate(double left, double right);
    virtual double evaluate(double uniInput);
    virtual double evaluate();

    virtual void set_base(double input);

    virtual double get_int()const;
    virtual char get_op()const;
    virtual char get_name()const;
    virtual int get_prec()const;
    virtual string get_trig()const;
    virtual bool get_ln()const;
    int get_type() const{ return type; }

    private:
    int type;
};
#endif