#ifndef GRAPH_H
#define GRAPH_H


#include "graph_info.h"
#include "plot.h"
#include "translate.h"



class graph{
    public:
    
    graph(){

    }


    graph(graph_info* _infoIn){
        _info = _infoIn;
        plotter = plot(_infoIn);
        pt = sf::CircleShape(5);
        points = vector<sf::Vector2f>();
    }


    void calc_plot(){
        translate T(_info);
        for(int i = _info->domain.x; i < _info->domain.y; i++){
            sf::Vector2f coord = plotter.get_xy(i);
            coord = T(coord);
            points.push_back(coord);
        }
    }

    void draw(sf::RenderWindow &window);


    private:
    graph_info* _info;
    sf::CircleShape pt;
    vector<sf::Vector2f> points;
    plot plotter;


};







#endif
