#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H





#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;



struct graph_info {
    string equation;
    vector<string> plotLst = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    vector<string> equLst = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    vector<sf::Vector2f> ArduinoIn;
    sf::Vector2<double> dimensions;
    sf::Vector2<double> origin;
    sf::Vector2<double> scale;
    sf::Vector2<double> domain;
    sf::Vector2<double> range;
    int Gmode = 0;                          //0 = cartesian, 1 = polar, 2 = derive
    int totalpt;
    int totalgraph = 1;

    graph_info(string equ, sf::Vector2<double> dim, sf::Vector2<double> org, sf::Vector2<double> rang, sf::Vector2<double> dom, int tot) 
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
        double absDomain = dimensions.x / scale.x;               //calc domian after scale is square
        domain = sf::Vector2<double>(-absDomain/2.0, absDomain/2.0);
        double absRange = dimensions.y / scale.y;                //calc range after scale is square
        range = sf::Vector2<double>(-absRange/2.0, absRange/2.0);
        origin = sf::Vector2<double>(dimensions.x / 2.0, dimensions.y/ 2.0);
    }

    void square_domain(){
        domain = range;
        origin = sf::Vector2<double>(dimensions.x / 2.0, dimensions.y/ 2.0);
        reset_scale();
    }

    sf::Vector2<double> plotDimension(){
        return sf::Vector2<double>(domain.y - domain.x, range.y - range.x);
    }

};





#endif