#include "plot.h"







plot::plot(graph_info* _infoIn){
    _info = _infoIn;
    T = translate(_infoIn);
}


void plot::set_info(graph_info* _infoIn){
    _info = _infoIn;
    T.set_info(_info);
}



vector<sf::Vector2f> plot::operator()(){
    points = vector<sf::Vector2f>();
    Queue<Token*> infix1 = strToQueue(_info->equation, _info->equLst, -1);
    ShuntingYard sy1(infix1);
    postfix = sy1.postfix();

    for(double i = _info->domain.x; i < _info->domain.y; i += 0.05){
        sf::Vector2f coord = get_xy(i);
        coord = T(coord);
        points.push_back(coord);
    }
    return points;
}



sf::Vector2f plot::get_xy(double input_x){
    RPN rpn1(postfix);
    double y = rpn1(input_x);
    return sf::Vector2f(input_x, y);
}