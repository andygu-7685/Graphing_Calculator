#include "graph.h"






graph::graph(graph_info* _infoIn){
    _info = _infoIn;
    plotter = plot(_infoIn);
    pt = sf::CircleShape(2);
    points = vector<sf::Vector2f>();
    errorFlag = 0;
}


void graph::set_info(graph_info* _infoIn){
    _info = _infoIn; 
    plotter.set_info(_info);
    errorFlag = 0;
}




void graph::calc_plot(){
    points = plotter();
    errorFlag = plotter.errorReport();
    //cout << "\npt vector: " << points[i].x << ", " << points[i].y << endl;
}


void graph::draw(sf::RenderWindow &window){
    sf::Vertex xaxis[] = {
    sf::Vertex(sf::Vector2f(0, _info->origin.y), sf::Color::White),
    sf::Vertex(sf::Vector2f(SCREEN_WIDTH - SIDEB_W, _info->origin.y), sf::Color::White)
    };

    sf::Vertex yaxis[] = {
    sf::Vertex(sf::Vector2f(_info->origin.x, 0), sf::Color::White),
    sf::Vertex(sf::Vector2f(_info->origin.x, SCREEN_HEIGHT), sf::Color::White)
    };
    window.draw(xaxis, 2, sf::Lines);
    window.draw(yaxis, 2, sf::Lines);



    pt.setFillColor(sf::Color(254, 254, 0));
    for(int i = 0; i < points.size() - 1; i++){
        sf::Vertex line[] = {
        sf::Vertex(points[i], sf::Color::Yellow),
        sf::Vertex(points[i + 1], sf::Color::Yellow)
        };

        double xdiff = points[i + 1].x - points[i].x;
        double ydiff = points[i + 1].y - points[i].y;
        if(pow(pow(xdiff, 2) + pow(ydiff, 2), 1/2.0) < 2000)
            window.draw(line, 2, sf::Lines);

    }
    pt.setPosition(_info->origin);
    pt.setFillColor(sf::Color(254, 0, 0));
    window.draw(pt);
}