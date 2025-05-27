#include "translate.h"

translate::translate(graph_info* _infoIn){
    _info = _infoIn;
}

sf::Vector2f translate::operator()(sf::Vector2f coord){
    double newX = (coord.x * _info->scale.x) + _info->origin.x;
    double newY = -(coord.y * _info->scale.y) + _info->origin.y;
    return sf::Vector2f(newX, newY);
}

sf::Vector2f translate::toPolar(sf::Vector2f coord){
    double cartx = coord.y * cos(coord.x);
    double carty = coord.y * sin(coord.x);
    double newX = (cartx * _info->scale.x) + _info->origin.x;
    double newY = -(carty * _info->scale.y) + _info->origin.y;
    return sf::Vector2f(newX, newY);
}

void translate::set_info(graph_info* _infoIn){ 
    _info = _infoIn;
}