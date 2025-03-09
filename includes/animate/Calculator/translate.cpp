#include "translate.h"




translate::translate(graph_info* _infoIn){
    _info = _infoIn;
}


sf::Vector2f translate::operator()(sf::Vector2f coord){
    double domain = _info->domain.y - _info->domain.x;
    double newX = (coord.x * _info->scale.x) + _info->origin.x;
    double newY = -(coord.y * _info->scale.y) + _info->origin.y;
    return sf::Vector2f(newX, newY);
}



void translate::set_info(graph_info* _infoIn){ 
    _info = _infoIn;
}