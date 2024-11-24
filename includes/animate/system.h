#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "particle.h"
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

private:
    graph_info* _info;
    graph _g;
    int totalUID;
};

#endif // SYSTEM_H
