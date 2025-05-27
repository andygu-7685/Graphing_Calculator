#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "..\constants.h"

using namespace std;


class TextBox
{
public:
    TextBox();
    TextBox(float left, float top, float width, float height, int UIDIn, float vertSpace = 10.0, float margin = 10.0, bool hidden = false, bool coutMsg = true);
    virtual int overlapText(sf::Vector2f testPos);
    bool overlap(sf::Vector2f testPos);
    sf::Vector2f getPt(int corner);
    virtual void draw(sf::RenderWindow& window);
    string& operator [](int index);
    const string operator[](int index) const;
    float TextY(int lineNum);
    float TextH(int lineNum);
    void setColor(sf::Color inputColor);
    virtual void hide(bool h);
    bool is_hidden(){ return _hidden; }
    void setItems(vector<string> inputV) { items = inputV; }
    void setAll( float left, float top, float width, float height);
    void setLineColor(sf::Color inputColor, int lineNum){ lineColors[lineNum] = inputColor; }
    void setUID(int newUID){ UID = newUID; }
    int getUID(){ return UID; }

protected:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Text sb_text;                   //used to draw strings on the window object
    sf::Font font;                      //used to draw text
    vector<sf::Color> lineColors;

    double VERTICAL_LINE_SPACING;
    double LEFT_MARGIN;
    float _left;
    float _top;
    float _width;
    float _height;
    bool _hidden;
    int UID;

};

#endif // SIDEBAR_H
