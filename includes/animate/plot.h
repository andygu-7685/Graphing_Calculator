#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <vector>
#include "graph_info.h"
#include "rpn.h"
#include "shunting_yard.h"
#include "MyQueue.h"
#include "MyStack.h"
#include "operator.h"
#include "integer.h"
#include "leftparen.h"
#include "rightparen.h"
#include "variable.h"
#include "trig.h"
#include "translate.h"
#include "exception.h"




class plot{
    public:
    
    plot(){}


    plot(graph_info* _infoIn);
    void set_info(graph_info* _infoIn);


    vector<sf::Vector2f> operator()();


    sf::Vector2f get_xy(double input_x);

    sf::Vector2f get_polar(double input_x);

    int errorReport(){ return errorFlag; }


    private:
    graph_info* _info;
    vector<sf::Vector2f> points;
    Queue<Token*> postfix;
    translate T;
    int errorFlag;

};







#endif
