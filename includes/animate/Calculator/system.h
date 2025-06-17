#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "..\Tools\particle.h"
#include "..\Tools\random.h"
#include "..\constants.h"
#include "graph_info.h"
#include "graph.h"
#include "../exception.h"

using namespace std;
class System
{
public:
    System();
    System(graph_info* _infoIn);
    void Step(int& command);
    void Draw(sf::RenderWindow& widnow);
    void set_info(graph_info* _infoIn);
    MyException error();
    void setError(int eCode, string eMsg);
    void setError(MyException excep);
    void clear();

private:
    graph_info* _info;
    vector<graph> _g;
    int totalUID;
    MyException sysException;

};

#endif // SYSTEM_H
