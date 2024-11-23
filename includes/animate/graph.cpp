#include "graph.h"


void graph::draw(sf::RenderWindow &window){
    for(int i = 0; i < points.size(); i++){
        pt.setPosition(points[i]);
        window.draw(pt);
    }
}