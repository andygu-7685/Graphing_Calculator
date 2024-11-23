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
    int totalpt;

    graph_info(
        std::string equ,
        sf::Vector2f dim,
        sf::Vector2f org,
        sf::Vector2f scl,
        sf::Vector2f dom,
        int tot
    ) : equation(equ), dimensions(dim), origin(org), scale(scl), domain(dom), totalpt(tot) {}

};





#endif