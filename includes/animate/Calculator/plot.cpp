#include "plot.h"

plot::plot(graph_info* _infoIn){
    _info = _infoIn;
    T = translate(_infoIn);
}

void plot::set_info(graph_info* _infoIn){
    _info = _infoIn;
    T.set_info(_info);
}

vector<sf::Vector2f> plot::operator()(int mode){
    points = vector<sf::Vector2f>();
    if(mode == -1)
        mode = _info->Gmode;

    double increment = (_info->domain.y - _info->domain.x) / _info->totalpt;

    Queue<Token*> infix1 = strToQueue(_info->equation, _info->equLst);
    if(infix1.empty()){
        //must push back something so the size != 0, prevent error for draw() in graph
         points.push_back(sf::Vector2f(0,0));
         return points;
    }

    ShuntingYard sy1(infix1);
    postfix = sy1.postfix();

    if(mode == 0){
        for(double i = _info->domain.x; i < _info->domain.y; i += increment){
            if(i != 0){
                sf::Vector2f coord1 = get_xy(i);
                coord1 = T(coord1);
                points.push_back(coord1);
            }
        }
    }
    else if(mode == 1){
        int ctr(0), currentPts(0);
        bool render = true;
        int renderState = 0;                //0 default, 1 outside screen, 2 enter screen, 3 inside screen, 4 exit screen
        double currentDist, totalDist(0), originDist;
        double screenDist = pow(_info->dimensions.x / 8.0, 2.0) + pow(_info->dimensions.y / 8.0, 2.0);
        
        for(double i = POLAR_RENDER_L; i < POLAR_RENDER_H; i += increment, ctr++){
            if(i != 0){
                render = true;
                int maxAttempt = 300;
                sf::Vector2f coord0 = get_polar(i);
                sf::Vector2f plotCoord0 = coord0;
                coord0 = T.toPolar(coord0);
                currentDist = pow(coord0.x - _info->dimensions.x / 2.0, 2.0) + pow(coord0.y - _info->dimensions.y / 2.0, 2.0);

                if(currentDist < screenDist && !dequ(currentDist, screenDist, 0.3) && ctr < maxAttempt){
                    switch(renderState){
                        case 0:
                            increment = POLAR_RESOLUTION;
                            renderState = 3;
                        break;
                        case 1:
                            i -= increment;
                            increment /= 2.0;
                            render = false;
                            renderState = 2;
                        break;
                        case 2:
                            i -= increment;
                            increment /= 2.0;
                            render = false;
                        break;
                        case 3:

                        break;
                        case 4:
                            render = false;
                        break;
                        default:
                        break;
                    }
                }
                else if(currentDist > screenDist && !dequ(currentDist, screenDist, 0.3) && ctr < maxAttempt){
                    switch(renderState){
                        case 0:
                            increment = POLAR_PRECISION_MIN;
                            renderState = 1;
                        break;
                        case 1:

                        break;
                        case 2:
                            render = false;
                        break;
                        case 3:
                            i -= increment;
                            increment /= 2.0;
                            render = false;
                            renderState = 4;
                        break;
                        case 4:
                            i -= increment;
                            increment /= 2.0;
                            render = false;
                        break;
                        default:
                        break;
                    }
                }
                else if(dequ(currentDist, screenDist, 0.3) || ctr >= maxAttempt){
                    switch(renderState){
                        case 0:

                        break;
                        case 1:
                            increment = POLAR_RESOLUTION;
                            renderState = 3;
                        break;
                        case 2:
                            increment = POLAR_RESOLUTION;
                            renderState = 3;
                        break;
                        case 3:
                            increment = POLAR_PRECISION_MIN;
                            renderState = 1;
                        break;
                        case 4:
                            increment = POLAR_PRECISION_MIN;
                            renderState = 1;
                        break;
                        default:
                        break;
                    }

                    if(ctr >= maxAttempt)
                        ctr = 0;
                }

                if(render){
                    points.push_back(coord0);
                    originDist = pow(abs(plotCoord0.x), 2.0) + pow(abs(plotCoord0.y), 2.0);
                    totalDist += originDist;
                    currentPts++;
                    double avgDist = totalDist / currentPts;
                    increment = max(POLAR_PRECISION_MAX * min(1.0, (avgDist / currentDist)), POLAR_PRECISION_MIN);
                }
            }
        }
    }
    else if(mode == 2){
        for(double i = _info->domain.x; i < _info->domain.y; i += increment){
            if(i != 0){
                sf::Vector2f coord1 = get_xy(i);
                sf::Vector2f coord2 = get_xy(i + 0.05);

                float slope = (coord2.y - coord1.y) / (coord2.x - coord1.x);
                //coord2 = midpoint b/t two point to calculate slope
                coord2 = sf::Vector2f((2*i+0.05) / 2.0, slope);

                coord2 = T(coord2);
                points.push_back(coord2);
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