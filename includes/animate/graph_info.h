#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H





#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;



struct graph_info {
    string equation;
    vector<string> equLst;
    sf::Vector2f dimensions;
    sf::Vector2f origin;
    sf::Vector2f scale;
    sf::Vector2f domain;
    sf::Vector2f range;
    int totalpt;

    graph_info(std::string equ, sf::Vector2f dim, sf::Vector2f org, sf::Vector2f rang, sf::Vector2f dom, int tot) 
    : equation(equ), dimensions(dim), origin(org), range(rang), domain(dom), totalpt(tot) {
        scale.x = dimensions.x / (domain.y - domain.x);
        scale.y = dimensions.y / (range.y - range.x);
    }

    void reset_scale(){
        scale.x = dimensions.x / (domain.y - domain.x);
        scale.y = dimensions.y / (range.y - range.x);
    }

};





#endif