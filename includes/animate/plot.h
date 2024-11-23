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




class plot{
    public:
    
    plot(){

    }


    plot(graph_info* _infoIn){
        _info = _infoIn;
    }


    sf::Vector2f get_xy(int input_x){
        Queue<Token*> infix1 = strToQueue(_info->equation, _info->equLst, -1);
        ShuntingYard sy1(infix1);
        Queue<Token*> postfix1 = sy1.postfix();
        RPN rpn1(postfix1);
        double y = rpn1(input_x);
        return sf::Vector2f(input_x, y);
    }



    private:
    graph_info* _info;
    Queue<Token*> postfix;

};







#endif
