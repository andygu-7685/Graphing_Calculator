#include "trig.h"







    Trig::Trig() : Operator("T"){
        _trig = "sin";
        errorFlag = 0;
    }

    Trig::Trig(string trigFn) : Operator("T"){
        _trig = trigFn;
        errorFlag = 0;
    }

    double Trig::evaluate(double uniInput){
        if(_trig == "cot"){
            errorFlag = trigException(uniInput);
            if(errorFlag != 0){ return 0.0; }
            return (1/tan(uniInput));
        }
        char uniqueChar = _trig[1];
        switch(uniqueChar){
            case 'i':
            case 'I':
                return sin(uniInput);
            break;
            case 'o':
            case 'O':
                return cos(uniInput);
            break;
            case 'a':
            case 'A':
                return tan(uniInput);
            break;
            case 'e':
            case 'E':
                errorFlag = trigException(uniInput);
                if(errorFlag != 0){ return 0.0; }
                return (1/sin(uniInput));
            break;
            case 's':
            case 'S':
                return (1/cos(uniInput));
            break;
            default:
                cout << "Invalid trig fn in Evaluate\n";
                return 0;
            break;
        }
    }