#include "sidebar.h"





Sidebar::Sidebar(){}

Sidebar::Sidebar(float left, float top, float width, float height, int UIDIn, float vertSpace, float margin) 
    : _left(left), _top(top), _width(width), _height(height), UID(UIDIn)
{
    cout << "Sidebar CTOR: TOP" << endl;
    items.reserve(50);
    VERTICAL_LINE_SPACING = vertSpace;                  //defalut 10
    LEFT_MARGIN = margin;                               //default 10
    lineColors = vector<sf::Color>(25 , sf::Color::White);

    // set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105, 105, 105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, top));
    rect.setSize(sf::Vector2f(width, height));
    cout << "Sidebar CTOR: about to load font (marker)." << endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // the font file must be in the "working directory"
    //  check projects->run->working directory
    //       [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf"))
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    //. . . . . text / font problems: . . . . . . . .
    // initializing text object in this way caused problems
    // (hangs!)
    // only when sb_text was a private member and worked fine
    // when it was a public member. Probably not releavant,
    // but still strange!
    //
    // sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout << "Sidebar CTOR: Text object initialized." << endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::White);

    ////this is how you would position text on screen:
    // sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("ST");
    // Fill the items vector with empty strings so that we can use [] to read them:
    for (int i = 0; i < 30; i++)
    {
        items.push_back("");
    }
    cout << "Sidebar: CTOR: Exit." << endl;
}


//1 = top left
//2 = top right
//3 = bottom right
//4 = bottom left
//Position are in screen coordinate
sf::Vector2f Sidebar::getPt(int corner){
    if(corner == 1)
        return sf::Vector2f(_left, _top);
    if(corner == 2)
        return sf::Vector2f(_left + _width, _top);
    if(corner == 3)
        return sf::Vector2f(_left + _width, _top + _height);
    if(corner == 4)
        return sf::Vector2f(_left, _top + _height);
    return sf::Vector2f();
}




void Sidebar::draw(sf::RenderWindow &window)
{
    window.draw(rect);
    float height = _top + VERTICAL_LINE_SPACING;

    for (vector<string>::iterator it = items.begin();
         it != items.end(); it++)
    {
        //sb_text.setColor(lineColors[it - items.begin()]);
        bool blank = false;
        if (it->length() == 0)
        {
            // empty rows must be taken into account (getLocalBounds())
            //     but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else
        {
            sb_text.setString(it->c_str());
        }
        sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        height += sb_text.getLocalBounds().height + VERTICAL_LINE_SPACING;
        if (!blank)
            window.draw(sb_text);
    }
}


int Sidebar::overlapText(sf::Vector2f testPos){
    float height = _top + VERTICAL_LINE_SPACING;

    for (vector<string>::iterator it = items.begin(); it != items.end(); it++)
    {
        if (it->length() == 0){
            sb_text.setString("A");
        }
        else{
            sb_text.setString(it->c_str());
        }

        float buttom = height + sb_text.getLocalBounds().height;
        if(testPos.y > height && testPos.y < buttom && 
           testPos.x > _left && testPos.x < _left + _width){
                return it - items.begin();
           }
        height = buttom + VERTICAL_LINE_SPACING;
    }
    return -1;
}







float Sidebar::TextX(int lineNum){
    float height = _top + VERTICAL_LINE_SPACING;    

    for (vector<string>::iterator it = items.begin(); it != items.end(); it++)
    {
        if (it->length() == 0){
            sb_text.setString("A");
        }
        else{
            sb_text.setString(it->c_str());
        }

        if(lineNum == it - items.begin())
            return height;
        height += sb_text.getLocalBounds().height + VERTICAL_LINE_SPACING;
    }
    return -1;
}



bool Sidebar::overlap(sf::Vector2f testPos){
    sf::Vector2f boxPt1 = getPt(1);
    sf::Vector2f boxPt2 = getPt(3);
    return (testPos.x > boxPt1.x && testPos.x < boxPt2.x && testPos.y > boxPt1.y && testPos.y < boxPt2.y);
}



void Sidebar::setColor(sf::Color inputColor){
    rect.setFillColor(inputColor);
}

float Sidebar::TextH(int lineNum){
    vector<string>::iterator it = items.begin() + lineNum;
    sb_text.setString(it->c_str());
    float retVal = sb_text.getLocalBounds().height;
    return retVal;
}



void Sidebar::setAll( float left, float top, float width, float height){
    _top = top;
    _left = left;
    _height = height;
    _width = width;
    rect.setPosition(sf::Vector2f(_left, _top));
    rect.setSize(sf::Vector2f(_width, _height));
}



string& Sidebar::operator[](int index)
{
    return items[index];
}

const string Sidebar::operator[](int index) const
{
    return items[index];
}
