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




System::System(graph_info* _info)
{
    _g = graph(_info);
    _g.calc_plot();
}
//------------------------------------------------------------------
//------------------------------------------------------------------





void System::Step(int command)
{
    
}




void System::Draw(sf::RenderWindow &window)
{
    window.clear();
    _g.draw(window);
}
