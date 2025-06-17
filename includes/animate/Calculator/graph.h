#ifndef GRAPH_H
#define GRAPH_H

#include<sstream>
#include<string>
#include "graph_info.h"
#include "plot.h"
#include "translate.h"
#include "..\constants.h"

class graph{
    public:
    graph(){}
    graph(graph_info* _infoIn);

    void set_info(graph_info* _infoIn);
    void calc_plot(string currentEqu, int mode = -1);
    void draw(sf::RenderWindow &window);

    private:
    sf::Font font;
    graph_info* _info;
    sf::CircleShape pt;
    vector<sf::Vector2f> points;
    plot plotter;

};




string floatToString(float value);




#endif
