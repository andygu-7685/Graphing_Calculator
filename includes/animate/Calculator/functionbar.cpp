#include "functionbar.h"


FunctionBar::FunctionBar()
    : TextBox() {}

FunctionBar::FunctionBar(float cellH, float left, float top, float width, float height, int UIDIn,
                         float vertSpace, float margin, bool hidden)
    : TextBox(left, top, width, height, UIDIn, vertSpace, margin, hidden) {
    fnCell.reserve(20);
    cellHeight = cellH;
}

void FunctionBar::setFunctions(vector<string> fnLst){
    fnCell.clear();
    items = fnLst;
    float height = _top + VERTICAL_LINE_SPACING;
    for (vector<string>::iterator it = items.begin();
        it != items.end(); it++)
    {
        sf::Vector2f cellPos = sf::Vector2f(_left + LEFT_MARGIN, height);
        sf::Vector2f cellSize = sf::Vector2f(_width - LEFT_MARGIN, cellHeight);
        //The UID is same for all cells, might need implementation
        FunctionCell cell(cellPos.x, cellPos.y, cellSize.x, cellSize.y, UID, 1.0, 5.0, _hidden);
        cell[0] = *it;
        fnCell.push_back(cell);
        height += cellHeight + VERTICAL_LINE_SPACING;
    }
}

void FunctionBar::draw(sf::RenderWindow& window){
    if(!_hidden){
        window.draw(rect);
        if(fnCell.empty()){
            cout << "empty vector error:";
        }
        for (int i = 0; i < fnCell.size(); i++){
            FunctionCell cell = fnCell[i];
            cell.draw(window);
        }
    }
}

void FunctionBar::hide(bool h){
    _hidden = h;
    for (int i = 0; i < fnCell.size(); i++)
        fnCell[i].hide(h);
}

int FunctionBar::overlapText(sf::Vector2f testPos){
    for(int i = 0; i < fnCell.size(); i++){
        if(fnCell[i].overlap(testPos)) 
            return i;
    }
    return -1;
}