#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H





#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "equation.h"

using namespace std;



struct graph_info {
    vector<equation> equLst;
    vector<sf::Vector2f> ArduinoIn;
    sf::Vector2f dimensions;
    sf::Vector2f origin;
    sf::Vector2f scale;
    sf::Vector2f domain;
    sf::Vector2f range;
    int Gmode = 0;                          //0 = cartesian, 1 = polar, 2 = derive
    int totalpt;
    int totalgraph = 1;

    graph_info(vector<equation> equ, sf::Vector2f dim, sf::Vector2f org, sf::Vector2f rang, sf::Vector2f dom, int tot) 
    : equLst(equ), dimensions(dim), origin(org), range(rang), domain(dom), totalpt(tot) {
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

    sf::Vector2f plotDimension(){
        return sf::Vector2f(domain.y - domain.x, range.y - range.x);
    }

    vector<string> strLst(){
        vector<string> allequ;
        for(int i = 0 ; i < equLst.size(); i++){
            allequ.push_back(equLst[i].expression);
        }
        return allequ;
    }

    vector<string> fnLst(){
        vector<string> allfn;
        for(int i = 0 ; i < equLst.size(); i++){
            if(equLst[i].isFn)
                allfn.push_back(equLst[i].expression);
        }
        return allfn;
    }

    vector<string> displayLst(){
        vector<string> alldisplay;
        for(int i = 0 ; i < equLst.size(); i++){
            if(equLst[i].isDisplay)
                alldisplay.push_back(equLst[i].expression);
        }
        return alldisplay;
    }

};





#endif