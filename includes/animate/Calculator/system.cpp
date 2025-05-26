#include "system.h"
#include <iostream>
#include <cmath>

//./build/bin/main
//./build/bin/testB
System::System(){}

System::System(graph_info* _infoIn)
{
    _info = _infoIn;
    _g = graph(_infoIn);
    _g.calc_plot(1);
    sysException = MyException();
}

void System::set_info(graph_info* _infoIn){
    _info = _infoIn; 
    _g.set_info(_info);
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
                _g.calc_plot();
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
        _g.draw(window);
    }
    catch(MyException e){
        sysException = e;
    }
}

MyException System::error(){
    return sysException;
}

void System::clear(){
    sysException = MyException();
}