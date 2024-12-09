#include "system.h"
#include "random.h"
#include "constants.h"
#include "graph_info.h"
#include "graph.h"
#include <iostream>
#include <cmath>


//./build/bin/main


//./build/bin/testB



//axial zoom and dynamic coordinate
//



System::System()
{

}




System::System(graph_info* _infoIn)
{
    _info = _infoIn;
    setNum = 1;
    _g = graph(_infoIn);
    _g.calc_plot(1);
    errorFlag = 0;
}
//------------------------------------------------------------------
//------------------------------------------------------------------


void System::set_info(graph_info* _infoIn){
    _info = _infoIn; 
    _g.set_info(_info);
    errorFlag = 0;
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
                //if(_info->Gmode == 0 || _info->Gmode == 1){
                    _g.calc_plot(1);
                    errorFlag = _g.errorReport();
                //}
                //else{
                //    _g.calc_derivative(1);
                //    errorFlag = _g.errorReport();
                //}
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
