#include "system.h"
#include "random.h"
#include "constants.h"
#include "graph_info.h"
#include "graph.h"
#include <iostream>
#include <cmath>


//./build/bin/main





System::System()
{

}




System::System(graph_info* _infoIn)
{
    _info = _infoIn;
    _g = graph(_infoIn);
    _g.calc_plot();
}
//------------------------------------------------------------------
//------------------------------------------------------------------


void System::set_info(graph_info* _infoIn){
    _info = _infoIn; 
    _g.set_info(_info);
}




//if 1 = function changed or zoomed 
void System::Step(int& command)
{
    switch(command){
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
                _g.calc_plot();
            break;
        default:
            break;
    }
    command = 0;
}




void System::Draw(sf::RenderWindow &window)
{
    window.clear();
    _g.draw(window);
}
