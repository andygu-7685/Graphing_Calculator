#include "plot.h"







plot::plot(graph_info* _infoIn){
    _info = _infoIn;
    T = translate(_infoIn);
    errorFlag = 0;
}


void plot::set_info(graph_info* _infoIn){
    _info = _infoIn;
    T.set_info(_info);
    errorFlag = 0;
}



vector<sf::Vector2f> plot::operator()(){
    points = vector<sf::Vector2f>();
    derivativePts = vector<sf::Vector2f>();
    Queue<Token*> infix1 = strToQueue(_info->equation, _info->equLst, -99, errorFlag);
    if(infix1.empty() || errorFlag != 0){
        //must push back something so the size != 0, prevent error for draw() in graph
         points.push_back(sf::Vector2f(0,0));
         return points;
    }

    ShuntingYard sy1(infix1);
    postfix = sy1.postfix(errorFlag);
    if(errorFlag != 0){
         points.push_back(sf::Vector2f(0,0));
         return points;
    }

    if(_info->Gmode == 1){
        for(double i = POLAR_RENDER_L; i < POLAR_RENDER_H; i += 0.05){
            if(i != 0){
                sf::Vector2f coord = get_polar(i);
                if(errorFlag != 0){
                    points = vector<sf::Vector2f>();
                    points.push_back(sf::Vector2f(0,0));
                    return points;
                }
                coord = sf::Vector2f(coord.y * cos(coord.x), coord.y * sin(coord.x));
                coord = T(coord);
                points.push_back(coord);
            }
        }
    }
    else{
        for(double i = _info->domain.x; i < _info->domain.y; i += 0.05){
            if(i != 0){
                sf::Vector2f coord1 = get_xy(i);
                sf::Vector2f coord2 = get_xy(i + 0.05);
                
                if(errorFlag != 0){
                    points = vector<sf::Vector2f>();
                    points.push_back(sf::Vector2f(0,0));
                    return points;
                }


                float slope = (coord2.y - coord1.y) / (coord2.x - coord1.x);
                coord2 = sf::Vector2f((i+0.05+i) / 2.0, slope);
                coord2 = T(coord2);
                coord1 = T(coord1);
                points.push_back(coord1);
                derivativePts.push_back(coord2);
            }
        }
    }
    if(_info->Gmode == 2)
        return derivativePts;
    return points;
}



sf::Vector2f plot::get_xy(double input_x){
    RPN rpn1(postfix);
    double y = rpn1(errorFlag, input_x);
    return sf::Vector2f(input_x, y);
}

sf::Vector2f plot::get_polar(double input_x){
    RPN rpn1(postfix);
    double r = rpn1(errorFlag, input_x);
    return sf::Vector2f(input_x, r);
}



vector<sf::Vector2f> plot::get_derivative(){
    return derivativePts;
}

void plot::points_allo(){
    points = derivativePts;
}