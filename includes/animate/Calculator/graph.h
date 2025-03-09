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
    void calc_plot(int index);
    void calc_derivative(int index);
    void draw(sf::RenderWindow &window);
    int errorReport(){ return errorFlag; }


    private:
    sf::Font font;
    graph_info* _info;
    sf::CircleShape pt;
    vector<sf::Vector2f> points;
    vector<vector<sf::Vector2f>> ptSets;
    plot plotter;
    int errorFlag;


};




string floatToString(float value);




#endif
