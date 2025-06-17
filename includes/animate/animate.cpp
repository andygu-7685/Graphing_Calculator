#include "animate.h"
#include <iostream>

using namespace std;


animate::animate() : sidebar(SIDEB_X, SIDEB_Y, SIDEB_W, SIDEB_H, SIDEB_UID),
                     inputbar(INB_X, INB_Y, INB_W, INB_H, INB_UID), 
                     settingbar(SETB_X, SETB_Y, SETB_W, SETB_H, SETB_UID),
                     historybar(HISTB_X, HISTB_Y, HISTB_W, HISTB_H, HISTB_UID),
                     funcbar(25.0, FNB_X, FNB_Y, FNB_W, FNB_H, FNB_UID, 5.0, 5.0, true)
{
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    window.setFramerateLimit(60);
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will





    //default text
    inputbar[0] = "Input equation: ";
    sidebar[SB_MODE] = "HISTORY";
    settingbar[ST_SAVE] = "SAVE ALL";
    settingbar[ST_CLEAR] = "CLEAR HISTORY";
    settingbar[ST_MODE] = "CARTESIAN";




    //initialize private variable
    inputStr = "";
    cursorPos = 0;
    cursorToggle = 0;
    inputUID = 0;
    isDragging = false;
    sidebarMode = true;
    INB_Hidden = true;
    errorFlag = 0;



    _info = new graph_info( vector<equation>(1, equation(inputStr, false, false)), 
                            sf::Vector2f(SCREEN_WIDTH - SIDEB_W, SCREEN_HEIGHT), 
                            sf::Vector2f((SCREEN_WIDTH - SIDEB_W) / 2.0 , SCREEN_HEIGHT / 2.0),
                            sf::Vector2f(-20, 20),
                            sf::Vector2f(-20, 20), 400);
    _info->square_scale();
    system = System(_info);
    mouseIn = true;
    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);





    //initalize arduino file reading pos and time
    ArdTime = 0;
    ifstream fin("ArduinoData.txt");
    if(fin.fail()){
        cout << "could not open file";
        exit(-1);
    }
    ArdDataPos = ios::beg + 2;
    fin.close();





    //Load History
    LoadHistory(errorFlag);
    LoadData(errorFlag, ArdDataPos, ArdTime);
    
    


    cout << "Game CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    // Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Duckies", font);
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
    sidebar.draw(window);
    inputbar.draw(window);
    settingbar.draw(window);
    historybar.draw(window);
    funcbar.draw(window);

    if (mouseIn)
        window.draw(mousePoint);

    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    //window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}





void animate::update()
{
    // cause changes to the data for the next frame
    int ArdStore = ArdTime;
    LoadData(errorFlag, ArdDataPos, ArdTime);
    if(ArdStore != ArdTime)             //update graph every time new data introduced
        command = 10;

    sidebar.hide(false);
    inputbar.hide(INB_Hidden);
    settingbar.hide(false);
    funcbar.hide(sidebarMode);
    historybar.hide(!sidebarMode);

    // update the sidebar with history & function, and calculate graph
    historybar.setItems(history);
    funcbar.setFunctions(_info->strLst());
    system.Step(command);
    
    sidebar[SB_KEY_PRESSED] = "( " + to_string(_info->range.x) + ", " + to_string(_info->range.y) + " )";
    if(INB_Hidden && inputUID == INB_UID) inputUID = 0;

    // mousePoint red dot:
    if (mouseIn){
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5, sf::Mouse::getPosition(window).y - 5);
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }



    //text cursor animation
    displayStr = inputStr;
    if(cursorToggle < 50)
        displayStr.insert(cursorPos , 1, '|');
    else if(cursorToggle < 100)
        displayStr.insert(cursorPos , 1, ' ');
    else
        cursorToggle = 0;
    cursorToggle++;
    inputbar[1] = displayStr;




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
    int zoomMode;

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
                if(inputUID == 2){
                    if(cursorPos > 0)
                        cursorPos--;
                }
                else{
                    sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                    PanScreen(leftDir);
                    system.set_info(_info);
                    command = 3;
                }
                break;


            case sf::Keyboard::Right:
                if(inputUID == 2){
                    if(cursorPos < inputStr.size())
                        cursorPos++;
                }
                else{
                    sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                    PanScreen(rightDir);
                    system.set_info(_info);
                    command = 4;
                }
                break;


            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "UP ARROW";
                PanScreen(upDir);
                system.set_info(_info);
                command = 5;
                break;


            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "DOWN ARROW";
                PanScreen(downDir);
                system.set_info(_info);
                command = 6;
                break;


            case sf::Keyboard::PageUp:
                sidebar[SB_KEY_PRESSED] = "ZOOM IN";
                ZoomScr(1, mousePos);
                system.set_info(_info);
                command = 7;
                break;


            case sf::Keyboard::PageDown:
                sidebar[SB_KEY_PRESSED] = "ZOOM OUT";
                ZoomScr(2, mousePos);
                system.set_info(_info);
                command = 8;
                break;


            case sf::Keyboard::Enter:
                if(inputUID == INB_UID && !INB_Hidden){
                    _info->equLst.push_back(equation(inputStr, false, true));
                    cout << "input: " << inputStr << endl;
                    system.set_info(_info);
                    command = 2;
                    system.Step(command);
                    command = 2;

                    //if the expression has no errors
                    if(system.error().code() == -1){
                        INB_Hidden = !INB_Hidden;
                        inputbar[0] = "Input equation: "; 
                    }
                    else if(system.error().code() == DefFlag){
                        _info->equLst.pop_back();
                        _info->equLst.push_back(equation(inputStr, true, true));
                    }
                    else{
                        _info->equLst.pop_back();
                        inputbar[0] = system.error().what();
                    }


                    //update error label
                    if(system.error().code() == DefFlag){
                        string defStr = inputStr;
                        defStr.erase(remove(defStr.begin(), defStr.end(), '\r'), defStr.end());             //remove all retrun character
                        int fnIndex = defStr[1] - '0';
                        assert(defStr.size() > 3);         //already debuged

                        try{
                            Queue<Token*> testQueue; 
                            testQueue = strToQueue(defStr.substr(3, defStr.size() - 3), _info->equLst);
                            ShuntingYard sytest(testQueue);
                            testQueue = sytest.postfix();
                            RPN rpntest(testQueue);
                            rpntest(1);

                            
                            if(fnIndex < 10 && fnIndex >= 0){
                                (_info->equLst)[fnIndex] = defStr.substr(3, defStr.size() - 3);
                                history.push_back(defStr.substr(3, defStr.size() - 3));
                                INB_Hidden = !INB_Hidden;
                                system.clear();
                            }
                            else{
                                system.setError(MyException(invalidE, "Error: Invalid function name"));           //if the name of function defining is invalid
                            }
                        }
                        catch(MyException e){
                            system.setError(e);
                        }
                    }
                }
                else if(INB_Hidden){
                    //display the input bar of input
                    INB_Hidden = !INB_Hidden;
                }

                break;

            case sf::Keyboard::Tab:
                _info->square_scale();
                system.set_info(_info);
                command = 8;
                break;

            case sf::Keyboard::BackSlash:
                _info->square_domain();
                system.set_info(_info);
                command = 8;
                break;

            case sf::Keyboard::RShift:

                break;


            case sf::Keyboard::Escape:
                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                window.close();
                break;

            default:
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
            mousePos.x = event.mouseMove.x;
            mousePos.y = event.mouseMove.y;
            if(isDragging){
                sf::Vector2f diff(mousePos.x - dragStart.x, mousePos.y - dragStart.y);
                PanScreen(diff);
                dragStart = mousePos;
                system.set_info(_info);
                command = 8;
            }
            break;

        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right){
                sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " + mouse_pos_string(window);
            }
            else{
                isDragging = false;
                int rowNum;
                sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " + mouse_pos_string(window);
                inputUID = scanOverlap(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
                //cout << mousePos.x << ", " << mousePos.y << endl;
                switch(inputUID){
                    case SIDEB_UID:                 //sidebar
                        cout << "clicked sidebar:";
                        rowNum = sidebar.overlapText(mousePos);
                        if(rowNum == SB_MODE){
                            sidebarMode = !sidebarMode;
                            if(sidebarMode)
                                sidebar[SB_MODE] = "HISTORY";
                            else
                                sidebar[SB_MODE] = "FUNCTIONS";
                        }
                        break;

                    case INB_UID:                 //inputbar
                        cout << "clicked inputbar:";
                        break;

                    case SETB_UID:                 //settingbar
                        cout << "clicked setting bar:";
                        rowNum = settingbar.overlapText(mousePos);
                        if(rowNum == ST_SAVE){
                            clearfile("historyData.txt");
                            ofstream historyIn("historyData.txt", ios::app);

                            historyIn << "Base:FileState:Data:" << "\n";
                            for(int i = 0; i < _info->equLst.size(); i++){
                                equation temp = _info->equLst[i];
                                historyIn << temp.isFn << temp.isDisplay;
                                historyIn << temp.expression.c_str() << "\n";
                            }

                            historyIn.close();
                        }
                        else if(rowNum == ST_CLEAR){
                            clearfile("historyData.txt");
                            ofstream historyIn("historyData.txt", ios::app);
                            historyIn << "Base:FileState:Data:" << "\n";
                            _info->equLst.clear();
                            historyIn.close();
                        }
                        else if(rowNum == ST_MODE){
                            _info->Gmode++;
                            switch(_info->Gmode){
                                case CART_MODE:
                                    settingbar[ST_MODE] = "CARTESIAN";
                                break;
                                case POLAR_MODE:
                                    settingbar[ST_MODE] = "POLAR";
                                break;
                                case DERIVE_MODE:
                                    settingbar[ST_MODE] = "DERIVATIVE";
                                break;
                                case ARD_MODE:
                                    settingbar[ST_MODE] = "ARDUINO";
                                break;
                                default:
                                    _info->Gmode = 0;
                                    settingbar[ST_MODE] = "CARTESIAN";
                                break;
                            }
                            system.set_info(_info);
                            command = 2;
                        }
                        break;
                    
                    case FNB_UID:
                        cout << "clicked function bar:";
                        rowNum = funcbar.overlapText(mousePos);
                        if(rowNum != -1){
                            cursorPos = 0;                  //reset cursor
                            //delete the item
                            if(!sidebarMode && mousePos.x > SCREEN_WIDTH - 40){
                                _info->equLst.erase(_info->equLst.begin() + rowNum);
                                funcbar.setFunctions(_info->strLst());
                                system.set_info(_info);
                                command = 2;
                            }
                            else{
                                _info->equLst[rowNum].isDisplay = true;
                                system.set_info(_info);
                                command = 2;
                            }
                        }
                        break;
                    case HISTB_UID:
                        cout << "clicked history bar:";
                        // rowNum = historybar.overlapText(mousePos);
                        // if(rowNum != -1){
                        //     cursorPos = 0;
                        //     inputStr = historybar[rowNum];
                        //     _info->equation = inputStr;
                        //     system.set_info(_info);
                        //     command = 2;
                        // }
                        break;
                    default:

                        break;
                }
            }
            break;


        case sf::Event::MouseWheelScrolled:
            zoomMode = 0;                       //0 = default, 1 = xzoom, 2 = yzoom
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                zoomMode = 1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                zoomMode = 2;
            }

            if(event.mouseWheelScroll.delta != 0 && mouseIn){
                ZoomScr(3, mousePos, event.mouseWheelScroll.delta, zoomMode);
                system.set_info(_info);
                command = 9;
            }
            
            break;


        case sf::Event::TextEntered:
            if(event.text.unicode == 8 && inputUID == 2){
                //if backspace is pressed
                if(!inputStr.empty() && cursorPos > 0){
                    inputStr.erase(cursorPos - 1 , 1);
                    cursorPos--;
                }
            }                       
            else if (event.text.unicode < 128 && inputUID == 2){
                inputStr.insert(cursorPos, 1, static_cast<char>(event.text.unicode));
                cursorPos++;
            }
            else if (event.text.unicode == 13 && inputUID == 2){
                //dont push anything when Enter is pressed
            }
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                isDragging = true;
                dragStart = mousePos;
            }
        default:
            break;
        }
        
        //UI Asethetic
        sidebar.setLineColor(sf::Color::White, SB_MODE);
        settingbar.setLineColor(sf::Color::White, ST_CLEAR);
        settingbar.setLineColor(sf::Color::White, ST_SAVE);
        settingbar.setLineColor(sf::Color::White, ST_MODE);
        int lineID;
        int hoverUID = scanOverlap(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        if(hoverUID == SIDEB_UID){
            lineID = sidebar.overlapText(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
            if(lineID == SB_MODE)
                sidebar.setLineColor(sf::Color::Yellow, SB_MODE);
        }
        else if(hoverUID == 3){
            lineID = settingbar.overlapText(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
            if(lineID == ST_SAVE || lineID == ST_CLEAR || lineID == ST_MODE)
                settingbar.setLineColor(sf::Color::Yellow, lineID);
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




int animate::scanOverlap(sf::Vector2f testPos){
    if(funcbar.overlap(testPos) && !funcbar.is_hidden())
        return funcbar.getUID();
    if(historybar.overlap(testPos) && !historybar.is_hidden())
        return historybar.getUID();
    if(sidebar.overlap(testPos))
        return sidebar.getUID();
    if(inputbar.overlap(testPos))
        return inputbar.getUID();
    if(settingbar.overlap(testPos))
        return settingbar.getUID();
    return -1;
}





string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}


//input_type:          
//1 = "i"               
//2 = "o"               
//3 = mouse scroll
//   
//axis:
//0 = default zoom
//1 = only zoom x
//2 = only zoom y
void animate::ZoomScr(int input_type, sf::Vector2f mousePos, float mouse_delta, int axis){
    //the zoom rate depend on the ratio of the screen
    sf::Vector2f plotDim = _info->plotDimension();                                              //plot dimension inplot coordinate
    sf::Vector2f ZoomCenter = sf::Vector2f((_info->dimensions.x/2), (_info->dimensions.y/2));   //zoom center in screen coordinate
    sf::Vector2f zoomFract = sf::Vector2f(plotDim.x / 30.0, plotDim.y / 30.0);                  //total delta domain & range of a zoom action
    sf::Vector2f xratio = sf::Vector2f(1, 1);                                                   //a fraction that determin how much of the delta 
                                                                                                //domain goes on each side of the mouse pos
                                                                                                //when adding x and y, it equal to 1 
    sf::Vector2f yratio = sf::Vector2f(1, 1);                                                   //a fraction that determin how much of the delta 
                                                                                                //range goes on each side of the mouse pos 
                                                                                                //when adding x and y, it equal to 1 
    // -1 = zoom out, 1 = zoom in, 3 = no zoom
    int Zoom = 3;
    
    if(axis == 1)                      //only zoom x
        yratio = sf::Vector2f(0,0);
    else if(axis == 2)                 //only zoom y
        xratio = sf::Vector2f(0,0);

    //Keep seperate from Zoom assignment  b/c ZoomCenter need be 
    //at mousePos when at minimum range and mouse zoom
    if(input_type == 3 && mousePos.x < _info->dimensions.x 
                       && mousePos.y < _info->dimensions.y
                       && mousePos.x > 0
                       && mousePos.y > 0){
        ZoomCenter = mousePos;
        xratio.x *= mousePos.x / _info->dimensions.x;
        xratio.y *= (_info->dimensions.x - mousePos.x) / _info->dimensions.x;
        yratio.x *= mousePos.y / _info->dimensions.y;
        yratio.y *= (_info->dimensions.y - mousePos.y) / _info->dimensions.y;
    }

    
    //if mouse zoom
    if( input_type == 3 && mouse_delta > 0 && ( 
        axis == 1 && (plotDim.x >= MIN_RANGE) ||
        axis == 2 && (plotDim.y >= MIN_RANGE) ||
        axis == 0 && (plotDim.x >= MIN_RANGE && plotDim.y >= MIN_RANGE)))
        Zoom = 1;
    else if(input_type == 3 && mouse_delta < 0)
        Zoom = -1;
    //if "i" or "o" zoom
    else if(input_type == 1 && plotDim.x >= MIN_RANGE && plotDim.y >= MIN_RANGE)
        Zoom = 1;
    else if(input_type == 2)
        Zoom = -1;


    //if there's a zoom
    if(Zoom == 1 || Zoom == -1){
        _info->domain.x += xratio.x * zoomFract.x * Zoom;
        _info->domain.y -= xratio.y * zoomFract.x * Zoom;
        _info->range.x += yratio.y * zoomFract.y * Zoom;
        _info->range.y -= yratio.x * zoomFract.y * Zoom;
    }


    //coordinate of center of zoom relative to the origin in plotting coordinate
    sf::Vector2f ScrO((ZoomCenter.x - _info->origin.x) / _info->scale.x,
                      (ZoomCenter.y - _info->origin.y) / _info->scale.y);
    _info->reset_scale();
    //calculate position of the origin after zoom
    _info->origin = sf::Vector2f (ZoomCenter.x - (ScrO.x * _info->scale.x), 
                                  ZoomCenter.y - (ScrO.y * _info->scale.y));
}








//clear the file with name fileName in the current directory,
//insert the baseStr to the beginning of the file
void clearfile(const string& fileName){
    if (remove(fileName.c_str()) == 0)
        cout << "File " << fileName << " successfully deleted.\n";
    else
        cout << "Error deleting file";

    ofstream fout("temp.txt", ios::app);
    fout.close();

    if (rename("temp.txt", fileName.c_str()) != 0) 
        cout << "Error: Could not rename the temporary file.\n";
}







void animate::LoadHistory(int& errorFlag){
    string metaData, equationData;
    ifstream fin("historyData.txt");

    if(fin.fail()){
        cout << "could not open file";
        exit(-1);
    }

    getline(fin, metaData);
    if(metaData == "Base:FileState:Data:"){
        while(getline(fin, equationData))
            _info->equLst.push_back(equation(equationData.substr(2), equationData[0] - '0', equationData[1] - '0'));
    }

    fin.close();
}




vector<sf::Vector2f> animate::LoadData(int& errorFlag, streampos& lastImport, double& lastTime){
    string metaData, holder, singleImport;
    ifstream fin("ArduinoData.txt");

    if(fin.fail()){
        cout << "could not open file";
        exit(-1);
    }

    getline(fin, metaData);
    fin.seekg(lastImport - 2);
    getline(fin, holder);
    


    if(metaData == "Base:FileState:Arduino:"){
        while(getline(fin, singleImport)){
            _info->ArduinoIn.push_back(sf::Vector2f(lastTime , stof(singleImport)));
            lastTime += 1;
        }
        fin.clear();
    }

    lastImport = fin.tellg();
    fin.close();

    // if(_info->ArduinoIn.size() == 0){
    //     _info->ArduinoIn.push_back(sf::Vector2f(0, 0));
    // }

    return _info->ArduinoIn;
}








//1357
//1 = left
//3 = right
//5 = up
//7 = down
void animate::PanScreen(int dir){
    double panInc;
    if(dir > 4){
        panInc = (_info->range.y - _info->range.x) * PANFRAC;
        _info->origin.y -= (dir-6) * panInc * _info->scale.y;
        _info->range.x -= (dir-6) * panInc;
        _info->range.y -= (dir-6) * panInc;
    }
    else{
        panInc = (_info->domain.y - _info->domain.x) * PANFRAC;
        _info->origin.x -= (dir-2) * panInc * _info->scale.x;
        _info->domain.x += (dir-2) * panInc;
        _info->domain.y += (dir-2) * panInc;
    }
}


void animate::PanScreen( sf::Vector2f diff){
    _info->origin.x += diff.x;
    _info->origin.y += diff.y;
    _info->domain.x -= diff.x / _info->scale.x;
    _info->domain.y -= diff.x / _info->scale.x;
    _info->range.x += diff.y / _info->scale.y;
    _info->range.y += diff.y / _info->scale.y;
}


