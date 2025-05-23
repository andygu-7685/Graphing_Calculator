#ifndef GAME_H
#define GAME_H





#include <SFML/Graphics.hpp>
#include <fstream> 
#include <cstdlib>
#include <cstdio>
#include ".\Calculator\system.h"
#include ".\Calculator\sidebar.h"

#include ".\Calculator\graph_info.h"
#include ".\Parser\rpn.h"
#include ".\Parser\shunting_yard.h"

#include "constants.h"


class animate{
public:
    animate();
    void run();
    void processEvents();
    
    void update();
    void render();
    void Draw();
    int scanOverlap(sf::Vector2f testPos);
    vector<string> LoadHistory(int& errorFlag);
    vector<sf::Vector2f> LoadData(int& errorFlag, streampos& lastImport, double& lastTime);

private:
    sf::RenderWindow window;
    sf::CircleShape mousePoint;         //The little red dot
    sf::Vector2f mousePos;
    System system;                      //container for all the animated objects
    graph_info* _info;                   //contain info about current graph
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    bool mouseIn;                       //mouse is in the screen
    Sidebar sidebar;                    //rectangular message sidebar
    bool sidebarMode;                   //true if display history, false if display function
    Sidebar inputbar;
    Sidebar settingbar;
    string inputStr;
    vector<string> history;
    vector<Sidebar*> fnLine;
    int inputUID;
    int errorFlag;
    bool isDragging;
    int ctrlShift;
    int cursorPos;
    int cursorToggle;                   //keep track of cursor blank
    bool INB_Hidden;                    //true if hidden, false if show
    double ArdTime;                     //time for arduino data
    streampos ArdDataPos;                  //file reading location
    bool FN_Hidden;
    sf::Vector2f dragStart;
};

string mouse_pos_string(sf::RenderWindow& window);
void ZoomScr(int input_type, graph_info* _info, sf::Vector2f mousePos, float mouse_delta = 0, int axis = 0);
bool isOverlap(sf::Vector2f testPos, sf::Vector2f boxPt1, sf::Vector2f boxPt2);
void clearfile(const string& fileName, const string& baseStr);
void PanScreen(graph_info* _info, int dir);
void PanScreen(graph_info* _info, sf::Vector2f diff);
#endif // GAME_H
