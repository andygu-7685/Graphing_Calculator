#ifndef FUNCTIONCELL_H
#define FUNCTIONCELL_H

#include "textbox.h"

using namespace std;

class FunctionCell : public TextBox {
    public:
        FunctionCell();
        FunctionCell(float left, float top, float width, float height, int UIDIn,
                    float vertSpace = 10.0, float margin = 10.0, bool hidden = false);
        
        void draw(sf::RenderWindow& window) override;
        
    private:
        sf::RectangleShape delButton;

    };

#endif 