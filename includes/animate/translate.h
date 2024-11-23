#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <vector>
#include "graph_info.h"
#include "MyQueue.h"
#include "MyStack.h"
#include "operator.h"
#include "integer.h"
#include "leftparen.h"
#include "rightparen.h"
#include "variable.h"
#include "trig.h"




class translate{
    public:
    
    translate(){
        
    }


    translate(graph_info* _infoIn){
        _info = _infoIn;
    }


    sf::Vector2f operator()(sf::Vector2f coord){
        double domain = _info->domain.y - _info->domain.x;
        double factor = (_info->dimensions.x) / domain;
        double newX = (coord.x * factor) + _info->origin.x;
        double newY = -(coord.y * factor) + _info->origin.y;
        return sf::Vector2f(newX, newY);
    }




    private:
    graph_info* _info;



};







#endif
