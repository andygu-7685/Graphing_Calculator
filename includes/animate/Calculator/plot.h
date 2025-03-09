#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <vector>
#include "graph_info.h"
#include "..\Parser\rpn.h"
#include "..\Parser\shunting_yard.h"
#include "..\Tools\MyQueue.h"
#include "..\Tools\MyStack.h"
#include "..\Tokens\operator.h"
#include "..\Tokens\integer.h"
#include "..\Tokens\leftparen.h"
#include "..\Tokens\rightparen.h"
#include "..\Tokens\variable.h"
#include "..\Tokens\trig.h"
#include "translate.h"
#include "..\exception.h"




class plot{
    public:
    
    plot(){}


    plot(graph_info* _infoIn);
    void set_info(graph_info* _infoIn);


    vector<sf::Vector2f> operator()();


    sf::Vector2f get_xy(double input_x);

    sf::Vector2f get_polar(double input_x);

    vector<sf::Vector2f> get_derivative();

    int errorReport(){ return errorFlag; }

    void points_allo();


    private:
    graph_info* _info;
    vector<sf::Vector2f> points;
    vector<sf::Vector2f> derivativePts;
    Queue<Token*> postfix;
    translate T;
    int errorFlag;

};







#endif
