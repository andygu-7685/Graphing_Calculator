#ifndef GAME_H
#define GAME_H





#include <SFML/Graphics.hpp>
#include <fstream> 
#include <cstdlib>
#include <cstdio>
#include ".\Calculator\system.h"
#include ".\Calculator\textbox.h"
#include ".\Calculator\functionbar.h"
#include ".\Calculator\functioncell.h"

#include ".\Calculator\graph_info.h"
#include ".\Parser\rpn.h"
#include ".\Parser\shunting_yard.h"
#include "exception.h"

#include "constants.h"

enum dirCode {leftDir = 1, rightDir = 3, upDir = 5, downDir = 7};

class animate{
public:
    animate();
    void run();
    void processEvents();
    
    void update();
    void render();
    void Draw();
    int scanOverlap(sf::Vector2f testPos);
    void LoadHistory(int& errorFlag);
    vector<sf::Vector2f> LoadData(int& errorFlag, streampos& lastImport, double& lastTime);
    void ZoomScr(int input_type, sf::Vector2<double> mousePos, float mouse_delta = 0, int axis = 0);
    void PanScreen(int dir);
    void PanScreen(sf::Vector2<double> diff);

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
    TextBox sidebar;                    //rectangular message sidebar
    bool sidebarMode;                   //true if display history, false if display function
    TextBox inputbar;
    TextBox settingbar;
    TextBox historybar;
    FunctionBar funcbar;
    string inputStr;
    string displayStr;
    vector<string> history;
    int inputUID;
    int errorFlag;
    bool isDragging;
    int ctrlShift;
    int cursorPos;
    int cursorToggle;                   //keep track of cursor blank
    bool INB_Hidden;                    //true if hidden, false if show
    double ArdTime;                     //time for arduino data
    streampos ArdDataPos;                  //file reading location
    sf::Vector2<double> dragStart;
};

string mouse_pos_string(sf::RenderWindow& window);
void clearfile(const string& fileName);
#endif // GAME_H
