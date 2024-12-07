#ifndef GRAPH_H
#define GRAPH_H


#include "graph_info.h"
#include "plot.h"
#include "translate.h"
#include "constants.h"




class graph{
    public:
    
    graph(){}


    graph(graph_info* _infoIn);

    void set_info(graph_info* _infoIn);
    void calc_plot(int index);
    void draw(sf::RenderWindow &window);
    int errorReport(){ return errorFlag; }


    private:
    graph_info* _info;
    sf::CircleShape pt;
    vector<sf::Vector2f> points;
    vector<vector<sf::Vector2f>> ptSets;
    plot plotter;
    int errorFlag;


};







#endif
