#ifndef TOKEN_H
#define TOKEN_H




#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;



// Design a class Token with an integer _type to indicate what type of token it is: 1 for numbers, 2 for operators.
// Design two derived classes: Number and Operator. 
// Number will have a double member variable named. _val, Operator will have a character _op to hold the operator.
// The operator will have a function evaluate() that takes two doubles and returns the resulting double value


//0 = empty
//1 = number
//2 = operator
//3 = variable
//4 = rightparen
//5 = leftparen

class Token{
    public:

    Token();

    Token(int typeIn);


    friend ostream& operator<<(ostream& outs, const Token& rhs){
        switch(rhs.type){
            case 1:
                cout << rhs.get_int();
            break;
            case 2:
                cout << rhs.get_op();
            break;
            case 4:
                cout << "(";
            break;
            case 5:
                cout << ")";
            break;
            default:
                cout << "Invalid Token in cout\n";
            break;
        }
        return outs;
    }

    virtual double evaluate(double left, double right);

    virtual double evaluate(double uniInput);

    virtual double evaluate();

    virtual double get_int() const ;
    virtual char get_op()const ;
    virtual char get_name()const ;
    virtual int get_prec()const ;

    virtual string get_trig()const ;
    virtual bool get_ln()const;
    virtual void set_base(double input);

    virtual int errorReport();

    int get_type() const{ return type; }



    private:
    int type;

};






#endif