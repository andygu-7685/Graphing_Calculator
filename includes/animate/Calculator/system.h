#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "..\Tools\particle.h"
#include "..\Tools\random.h"
#include "..\constants.h"
#include "graph_info.h"
#include "graph.h"

using namespace std;
class System
{
public:
    System();
    System(graph_info* _infoIn);
    void Step(int& command);
    void Draw(sf::RenderWindow& widnow);
    void set_info(graph_info* _infoIn);
    int errorReport(){ return errorFlag; }
    void setError(int inputCode){ errorFlag = inputCode; }

private:
    graph_info* _info;
    graph _g;
    int totalUID;
    int setNum;
    int errorFlag;
};

#endif // SYSTEM_H
