#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float top, float width, float height, int UIDIn);
    sf::Vector2f getPt(int corner);
    void draw(sf::RenderWindow& window);
    string& operator [](int index);
private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object

    float _left;
    float _top;
    float _width;
    float _height;
    int UID;
};

#endif // SIDEBAR_H
