#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H





#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;



struct graph_info {
    string equation;
    vector<string> equLst = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    sf::Vector2f dimensions;
    sf::Vector2f origin;
    sf::Vector2f scale;
    sf::Vector2f domain;
    sf::Vector2f range;
    int Gmode = 0;                          //0 = cartesian, 1 = polar, 2 = derive
    int totalpt;

    graph_info(string equ, sf::Vector2f dim, sf::Vector2f org, sf::Vector2f rang, sf::Vector2f dom, int tot) 
    : equation(equ), dimensions(dim), origin(org), range(rang), domain(dom), totalpt(tot) {
        scale.x = dimensions.x / (domain.y - domain.x);
        scale.y = dimensions.y / (range.y - range.x);
    }

    void reset_scale(){
        scale.x = dimensions.x / (domain.y - domain.x);
        scale.y = dimensions.y / (range.y - range.x);
    }

    void square_scale(){
        scale.y = dimensions.y / (range.y - range.x);
        scale.x = scale.y;
        float absDomain = dimensions.x / scale.x;               //calc domian after scale is square
        domain = sf::Vector2f(-absDomain/2.0, absDomain/2.0);
        float absRange = dimensions.y / scale.y;                //calc range after scale is square
        range = sf::Vector2f(-absRange/2.0, absRange/2.0);
        origin = sf::Vector2f(dimensions.x / 2.0, dimensions.y/ 2.0);
    }

    void square_domain(){
        domain = range;
        origin = sf::Vector2f(dimensions.x / 2.0, dimensions.y/ 2.0);
        reset_scale();
    }

};





#endif