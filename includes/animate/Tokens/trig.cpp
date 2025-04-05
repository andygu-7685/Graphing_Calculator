#include "trig.h"

Trig::Trig(string trigFn) : Operator("T"), _trig(trigFn){}





double Trig::evaluate(double uniInput){
    int charSum = 0;
    for(int i = 0; i < _trig.size(); i++)
        charSum += tolower(_trig[i]);
    
    switch(charSum){
        case 't' + 'a' + 'n':
        case 's' + 'e' + 'c':
            try{
                trigException2(uniInput);
            }
            catch(const MyException& e){
                throw;
            }
        break;
        case 'c' + 's' + 'c':
        case 'c' + 'o' + 't':
            try{
                trigException1(uniInput);
            }
            catch(const MyException& e){
                throw;
            }
        break;
        default:
        break;
    }

    switch(charSum){
        case 's' + 'i' + 'n':
            return sin(uniInput);
        break;
        case 'c' + 'o' + 's':
            return cos(uniInput);
        break;
        case 't' + 'a' + 'n':
            return tan(uniInput);
        break;
        case 's' + 'e' + 'c':
            return (1/cos(uniInput));
        break;
        case 'c' + 's' + 'c':
            return (1/sin(uniInput));
        break;
        case 'c' + 'o' + 't':
            return (1/tan(uniInput));
        break;
        default:
            cout << "Warning: Invalid trig fn in evaluate\n";
            return 0;
        break;
    }
}