#include "graph.h"






graph::graph(graph_info* _infoIn){
    _info = _infoIn;
    plotter = plot(_infoIn);
    pt = sf::CircleShape(2);
    points = vector<sf::Vector2f>();
}


void graph::set_info(graph_info* _infoIn){
    _info = _infoIn; 
    plotter.set_info(_info);
}




void graph::calc_plot(){
    points = plotter();
    //cout << "\npt vector: " << points[i].x << ", " << points[i].y << endl;
}


void graph::draw(sf::RenderWindow &window){
    pt.setFillColor(sf::Color(254, 254, 0));
    for(int i = 0; i < points.size(); i++){
        pt.setPosition(points[i]);
        window.draw(pt);
    }
    pt.setPosition(_info->origin);
    pt.setFillColor(sf::Color(254, 0, 0));
    window.draw(pt);
}