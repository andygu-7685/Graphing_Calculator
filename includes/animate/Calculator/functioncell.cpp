#include "functioncell.h"


FunctionCell::FunctionCell()
    : TextBox() {}

FunctionCell::FunctionCell(float left, float top, float width, float height, int UIDIn,
                         float vertSpace, float margin, bool hidden)
    : TextBox(left, top, width, height, UIDIn, vertSpace, margin, hidden, false) {
        items.clear();
        items.push_back("");
        setColor(sf::Color(97, 97, 97));

        delButton.setFillColor(sf::Color(254, 0, 0)); 
        delButton.setSize(sf::Vector2f(20.0, height));
        sf::Vector2f delPos = sf::Vector2f(getPt(2).x - delButton.getLocalBounds().width, getPt(2).y);
        delButton.setPosition(delPos);
}

void FunctionCell::draw(sf::RenderWindow& window){
    if(!_hidden){
        TextBox::draw(window);
        window.draw(delButton);
    }
}