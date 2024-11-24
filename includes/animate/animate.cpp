#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"




animate::animate() : sidebar(WORK_PANEL, 0, SIDE_BAR, SCREEN_HEIGHT, 1), inputbar(0, 0, SIDE_BAR, 100, 2)
{
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    inputStr = "1";
    history = vector<string>();
    _info = new graph_info( inputStr, 
                            sf::Vector2f(SCREEN_HEIGHT, SCREEN_HEIGHT), 
                            sf::Vector2f(SCREEN_HEIGHT / 2.0 , SCREEN_HEIGHT / 2.0),
                            sf::Vector2f(-20, 20),
                            sf::Vector2f(-20, 20), 100);
    system = System(_info);
    window.setFramerateLimit(60);

    mouseIn = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Initial String for myTextLabel", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::Green);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));
    cout << "animate instantiated successfully." << endl;
}

void animate::Draw()
{
    // Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }

    sidebar.draw(window);
    inputbar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command);
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);

        int lineNum = 3;
        vector<string> historyDup = history;
        while(lineNum < 10 && !historyDup.empty()){
            sidebar[lineNum] = historyDup.back();
            historyDup.pop_back();
            lineNum++;
        }
    }
}

void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{

    sf::Event event;
    float mouseX, mouseY;

    while (window.pollEvent(event)) // or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                command = 3;

                _info->origin.x -= PANINC * _info->scale.x;
                _info->domain.x += PANINC;
                _info->domain.y += PANINC;
                system.set_info(_info);
                system.Step(command);

                break;
            case sf::Keyboard::Right:
                sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                command = 4;

                _info->origin.x += PANINC * _info->scale.x;
                _info->domain.x -= PANINC;
                _info->domain.y -= PANINC;
                system.set_info(_info);
                system.Step(command);

                break;
            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "UP ARROW";
                command = 5;

                _info->origin.y -= PANINC * _info->scale.y;
                _info->range.x += PANINC;
                _info->range.y += PANINC;
                system.set_info(_info);
                system.Step(command);

                break;
            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "DOWN ARROW";
                command = 6;

                _info->origin.y += PANINC * _info->scale.y;
                _info->range.x -= PANINC;
                _info->range.y -= PANINC;
                system.set_info(_info);
                system.Step(command);

                break;
            case sf::Keyboard::I:
                sidebar[SB_KEY_PRESSED] = "ZOOM IN";
                command = 7;
                ZoomScr(1, _info, window, 0);
                system.set_info(_info);
                system.Step(command);
                break;
            case sf::Keyboard::O:
                sidebar[SB_KEY_PRESSED] = "ZOOM OUT";
                command = 8;
                ZoomScr(2, _info, window, 0);
                system.set_info(_info);
                system.Step(command);
                break;
            case sf::Keyboard::Enter:
                if(inputUID == 2){
                    command = 2;
                    _info->equation = inputStr;
                    history.push_back(inputStr);
                    system.set_info(_info);
                    system.Step(command);
                }
                break;
            case sf::Keyboard::Escape:
                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                window.close();
                break;
            }

            break;
        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            // Do something with it if you need to...
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right){
                sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " + mouse_pos_string(window);
            }
            else{
                sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " + mouse_pos_string(window);
                if(isOverlap(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), 
                             inputbar.getPt(1), inputbar.getPt(3))){
                    inputUID = 2;
                }
                else if(isOverlap(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), 
                             sidebar.getPt(1), sidebar.getPt(3))){
                    inputUID = 1;
                    int rowNum = sidebar.overlapText(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
                    if(rowNum >= 3){
                        inputStr = sidebar[rowNum];
                        command = 2;
                        _info->equation = inputStr;
                        system.set_info(_info);
                        system.Step(command);
                    }
                }
            }

            break;
        case sf::Event::MouseWheelScrolled:
            if(event.mouseWheelScroll.delta != 0 && mouseIn){
                ZoomScr(3, _info, window, event.mouseWheelScroll.delta);
                sidebar[SB_KEY_PRESSED] = "SCROLLING";
                command = 9;
                system.set_info(_info);
                system.Step(command);
            }
            break;
        case sf::Event::TextEntered:
            if(event.text.unicode == 8 && inputUID == 2){
                assert(!inputStr.empty());
                inputStr.pop_back();
                inputbar[1] = inputStr;
            }
            else if (event.text.unicode < 128 && inputUID == 2){
                inputStr.push_back(static_cast<char>(event.text.unicode));
                inputbar[1] = inputStr;
            }
            break;
        default:
            break;
        }
    }
}

void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}



//1 = "i"
//2 = "o"
//3 = mouse scroll
void ZoomScr(int input_type, graph_info* _info, sf::RenderWindow &window, float mouse_delta){
    //screen origin in plotting coordinate
    double xratio1(1), xratio2(1);
    double yratio1(1), yratio2(1);
    double mousex = sf::Mouse::getPosition(window).x;
    double mousey = sf::Mouse::getPosition(window).y;
    
    int Zoom = 3;               // -1 = zoom out, 1 = zoom in, 3 = no zoom
    double ZoomX(_info->dimensions.x/2), ZoomY(_info->dimensions.y/2);
    if(input_type == 3 && mousex < _info->dimensions.x 
                       && mousey < _info->dimensions.y
                       && mousex > 0
                       && mousey > 0){
        ZoomX = mousex;
        ZoomY = mousey;
        xratio1 = mousex / _info->dimensions.x;
        xratio2 = (_info->dimensions.x - mousex) / _info->dimensions.x;
        yratio1 = mousey / _info->dimensions.y;
        yratio2 = (_info->dimensions.y - mousey) / _info->dimensions.y;
    }

    sf::Vector2f ScrO((ZoomX - _info->origin.x) / _info->scale.x , 
                        (ZoomY - _info->origin.y) / _info->scale.y);

    if(input_type == 1 && _info->domain.y - _info->domain.x >= 3 && _info->range.y - _info->range.x >= 3)
        Zoom = 1;
    if(input_type == 2)
        Zoom = -1;
    
    if( input_type == 3 && mouse_delta > 0 && _info->domain.y - _info->domain.x >= 3 && _info->range.y - _info->range.x >= 3)
        Zoom = 1;
    if(input_type == 3 && mouse_delta < 0)
        Zoom = -1;

    if(Zoom == 1 || Zoom == -1){
        _info->domain.x += xratio1 * ZOOMRATE * Zoom;
        _info->domain.y -= xratio2 * ZOOMRATE * Zoom;
        _info->range.x += yratio2 * ZOOMRATE * Zoom;
        _info->range.y -= yratio1 * ZOOMRATE * Zoom;
    }



    _info->reset_scale();
    _info->origin = sf::Vector2f (ZoomX - (ScrO.x * _info->scale.x), 
                                  ZoomY - (ScrO.y * _info->scale.y));
}




//testPos: position you want test
//boxPt1: the top left of bounding box
//boxPt2: the bottom right of bounding box
bool isOverlap(sf::Vector2f testPos, sf::Vector2f boxPt1, sf::Vector2f boxPt2){
    return (testPos.x > boxPt1.x && testPos.x < boxPt2.x && testPos.y > boxPt1.y && testPos.y < boxPt2.y);
}




