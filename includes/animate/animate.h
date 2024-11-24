#ifndef GAME_H
#define GAME_H





#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"

#include "graph_info.h"
#include "rpn.h"
#include "shunting_yard.h"



class animate{
public:
    animate();
    void run();
    void processEvents();
    
    void update();
    void render();
    void Draw();
private:
    sf::RenderWindow window;
    sf::CircleShape mousePoint;         //The little red dot
    System system;                      //container for all the animated objects
    graph_info* _info;                   //contain info about current graph
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    bool mouseIn;                       //mouse is in the screen
    Sidebar sidebar;                    //rectangular message sidebar
    Sidebar inputbar;
    string inputStr;
    vector<string> history;
    int inputUID;
};

string mouse_pos_string(sf::RenderWindow& window);
void ZoomScr(int input_type, graph_info* _info, sf::RenderWindow& window, float mouse_delta = 0);
bool isOverlap(sf::Vector2f testPos, sf::Vector2f boxPt1, sf::Vector2f boxPt2);

#endif // GAME_H
