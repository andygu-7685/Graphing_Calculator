#ifndef FUNCTIONBAR_H
#define FUNCTIONBAR_H

#include "textbox.h"
#include "functioncell.h"

using namespace std;

class FunctionBar : public TextBox {
    public:
        FunctionBar();
        FunctionBar(float cellH, float left, float top, float width, float height, int UIDIn,
                    float vertSpace = 10.0, float margin = 10.0, bool hidden = false);
        
        int overlapText(sf::Vector2f testPos) override;         
        void hide(bool h) override;
        void setFunctions(vector<string> fnLst);
        void draw(sf::RenderWindow& window) override;
        
    private:
        vector<FunctionCell> fnCell;
        float cellHeight;

    };

#endif 