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

    Queue<Token*> infix1 = strToQueue(_info->equation, _info->equLst);
    if(infix1.empty()){
        //must push back something so the size != 0, prevent error for draw() in graph
         points.push_back(sf::Vector2f(0,0));
         return points;
    }

    ShuntingYard sy1(infix1);
    postfix = sy1.postfix();

    if(_info->Gmode == 1){
        for(double i = POLAR_RENDER_L; i < POLAR_RENDER_H; i += 0.05){
            if(i != 0){
                sf::Vector2f coord0 = get_polar(i);
                coord0 = T.toPolar(coord0);
                points.push_back(coord0);
            }
        }
    }
    else if(_info->Gmode == 0){
        for(double i = _info->domain.x; i < _info->domain.y; i += 0.05){
            if(i != 0){
                sf::Vector2f coord1 = get_xy(i);
                coord1 = T(coord1);
                points.push_back(coord1);
            }
        }
    }
    else if(_info->Gmode == 2){
        for(double i = _info->domain.x; i < _info->domain.y; i += 0.05){
            if(i != 0){
                sf::Vector2f coord1 = get_xy(i);
                sf::Vector2f coord2 = get_xy(i + 0.05);

                float slope = (coord2.y - coord1.y) / (coord2.x - coord1.x);
                //coord2 = midpoint b/t two point to calculate slope
                coord2 = sf::Vector2f((2*i+0.05) / 2.0, slope);

                coord2 = T(coord2);
                points.push_back(coord1);
            }
        }
    }
    else{
        for(double i = 0; i < _info->ArduinoIn.size(); i++){
            sf::Vector2f coord3 = _info->ArduinoIn[i];
            if(coord3.x > _info->domain.x && coord3.x < _info->domain.y){
                coord3 = T(coord3);
                points.push_back(coord3);
            }
        }
    }

    if(points.empty())
        points.push_back(sf::Vector2f(0,0));
    return points;
}

sf::Vector2f plot::get_xy(double input_x){
    RPN rpn1(postfix);
    double y = rpn1(input_x);
    return sf::Vector2f(input_x, y);
}

sf::Vector2f plot::get_polar(double input_x){
    RPN rpn1(postfix);
    double r = rpn1(input_x);
    return sf::Vector2f(input_x, r);
}