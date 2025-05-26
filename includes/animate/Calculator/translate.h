#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <vector>
#include "graph_info.h"
#include "..\Tools\MyQueue.h"
#include "..\Tools\MyStack.h"
#include "..\Tokens\operator.h"
#include "..\Tokens\integer.h"
#include "..\Tokens\leftparen.h"
#include "..\Tokens\rightparen.h"
#include "..\Tokens\variable.h"
#include "..\Tokens\trig.h"

class translate{
    public:
    translate(){}
    translate(graph_info* _infoIn);

    void set_info(graph_info* _infoIn);
    sf::Vector2f operator()(sf::Vector2f coord);
    sf::Vector2f toPolar(sf::Vector2f coord);

    private:
    graph_info* _info;
};
#endif
