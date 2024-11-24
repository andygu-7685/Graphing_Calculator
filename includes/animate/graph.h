#ifndef GRAPH_H
#define GRAPH_H


#include "graph_info.h"
#include "plot.h"
#include "translate.h"



class graph{
    public:
    
    graph(){}


    graph(graph_info* _infoIn);

    void set_info(graph_info* _infoIn);
    void calc_plot();
    void draw(sf::RenderWindow &window);


    private:
    graph_info* _info;
    sf::CircleShape pt;
    vector<sf::Vector2f> points;
    plot plotter;


};







#endif
