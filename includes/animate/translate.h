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
    
    translate(){}


    translate(graph_info* _infoIn);
    void set_info(graph_info* _infoIn);

    sf::Vector2f operator()(sf::Vector2f coord);




    private:
    graph_info* _info;



};







#endif
