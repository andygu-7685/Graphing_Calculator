#include "system.h"
#include <iostream>
#include <cmath>

//./build/bin/main
//./build/bin/testB
System::System(){}

System::System(graph_info* _infoIn)
{
    _info = _infoIn;
    _g = vector<graph>(1, graph(_infoIn));
    sysException = MyException();
}

void System::set_info(graph_info* _infoIn){
    _info = _infoIn;
    for(int i = 0; i < _g.size(); i++)
        _g[i].set_info(_info);
    sysException = MyException();
}

//if 1 = function changed or zoomed 
void System::Step(int& command)
{
    switch(command){
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            try{
                vector<string> displayDup = _info->displayLst();
                _g = vector<graph>(displayDup.size(), graph(_info));
                for(int i = 0; i < displayDup.size(); i++)
                    _g[i].calc_plot(displayDup[i]);
            }
            catch(MyException e){
                sysException = e;
            }
            break;
        default:
            break;
    }
    command = 0;
}

void System::Draw(sf::RenderWindow &window)
{
    window.clear();
    try{
        for(int i = 0; i < _g.size(); i++)
            _g[i].draw(window);
    }
    catch(MyException e){
        sysException = e;
    }
}

MyException System::error(){
    return sysException;
}

void System::setError(int eCode, string eMsg){
    sysException = MyException(eCode, eMsg);
}

void System::setError(MyException excep){
    sysException = excep;
}

void System::clear(){
    sysException = MyException();
}