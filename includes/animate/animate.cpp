#include "animate.h"
#include "constants.h"
#include <iostream>

using namespace std;
#include "system.h"



const vector<string> errorMsg = {   "No Error",
                                    "Error: Invalid function name1.",
                                    "Error: the function should not self reference.",
                                    "Error: the function you referenced do not exist.",
                                    "Error: missing leftparen.",
                                    "Error: unknown Input.",
                                    "Error: missing operand.",
                                    "Error: invalid input.",
                                    "Error: unknown Input.",
                                    "Error: divide by zero.",
                                    "Error: Missing rightparen",
                                    "Error: Invalid function name2",
                                    "Error: Invalid trig Input",
                                    "Error: Invalid log Input" ,
                                    "Error: invalid Input in domain",
                                    "Error: Upper bound should not be lower than lower bound"};





animate::animate() : sidebar(SIDEB_X, SIDEB_Y, SIDEB_W, SIDEB_H, 1),
                     inputbar(INB_X, INB_Y, INB_W, INB_H, 2), 
                     settingbar(SETB_X, SETB_Y, SETB_W, SETB_H, 3)
{
    for(int i = SB_HISTORY; i < 14; i++){
        Sidebar* linePtr = new Sidebar(SIDEB_X, 0,  10.0, 10.0 , i, -1.0);
        linePtr->setColor(sf::Color(60, 64, 59));
        fnLine.push_back(linePtr);
    }
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
    settingbar[ST_MODE] = "POLAR";




    //initialize private variable
    inputStr = "";
    cursorPos = 0;
    cursorToggle = 0;
    inputUID = 0;
    isDragging = false;
    sidebarMode = true;
    INB_Hidden = true;
    FN_Hidden = true;
    errorFlag = 0;



    _info = new graph_info( inputStr, 
                            sf::Vector2f(SCREEN_WIDTH - SIDEB_W, SCREEN_HEIGHT), 
                            sf::Vector2f((SCREEN_WIDTH - SIDEB_W) / 2.0 , SCREEN_HEIGHT / 2.0),
                            sf::Vector2f(-20, 20),
                            sf::Vector2f(-20, 20), 100);
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
    history = LoadHistory(errorFlag);
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
    if(!INB_Hidden)
        inputbar.draw(window);
    settingbar.draw(window);

    if(!FN_Hidden){
        for(int i = 0; i < fnLine.size(); i++){
            fnLine[i]->draw(window);
        }
    }


    if (mouseIn)
        window.draw(mousePoint);



    if(!sidebarMode){
        int lineNum = SB_HISTORY;
        sf::Text deleteButton("X", font);
        deleteButton.setFillColor(sf::Color::Red);
        deleteButton.setCharacterSize(20);
        vector<string> fnLstDup = _info->equLst;
        while(lineNum < SB_HISTORY_END && !fnLstDup.empty()){
            if(fnLstDup[0] != " "){
                deleteButton.setPosition(sf::Vector2f(SCREEN_WIDTH - 20, sidebar.TextX(lineNum)));
                window.draw(deleteButton);
            }
            fnLstDup.erase(fnLstDup.begin());
            lineNum++;
        }
    }
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

    
    system.Step(command);
    command = 0;
    
    sidebar[SB_KEY_PRESSED] = "( " + to_string(_info->range.x) + ", " + to_string(_info->range.y) + " )";
    if(INB_Hidden && inputUID == 2)
        inputUID = 0;

    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5, sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);

        // update the sidebar with history
        if(sidebarMode){
            int lineNum = SB_HISTORY;
            vector<string> historyDup = history;
            while(lineNum < SB_HISTORY_END){
                if(!historyDup.empty()){
                    sidebar[lineNum] = historyDup.back();
                    historyDup.pop_back();
                }
                else{
                    sidebar[lineNum] = "";
                }
                lineNum++;
            }
        }
        else{
            int lineNum = SB_HISTORY;
            vector<string> fnLstDup = _info->equLst;
            while(lineNum < SB_HISTORY_END){
                if(!fnLstDup.empty()){
                    string temp = to_string(lineNum - SB_HISTORY) + ": ";
                    (*fnLine[lineNum - SB_HISTORY])[0] = "> F" + temp + fnLstDup[0];
                    sidebar[lineNum] = "> F" + temp + fnLstDup[0];
                    fnLstDup.erase(fnLstDup.begin());
                }
                else{
                    sidebar[lineNum] = "";
                }
                lineNum++;
            }

            for(int i = 0; i < 10; i++){
                float TextBoxY = sidebar.TextX(i + SB_HISTORY);
                float TextBoxH = sidebar.TextH(i + SB_HISTORY);
                fnLine[i]->setAll(SIDEB_X + 5.0, TextBoxY, SIDEB_W - 5.0, TextBoxH + 5.0);
            }
        }

        



        string displayStr = inputStr;
        if(cursorToggle > 100){
            cursorToggle = 0;
        }
        else if(cursorToggle > 50){
            displayStr.insert(cursorPos , 1, '|');              //add cursor display
        }
        else{
            displayStr.insert(cursorPos , 1, ' ');
        }
        cursorToggle++;
        inputbar[1] = displayStr;






        //update error label
        if(system.errorReport() == 11){
            string defStr = inputStr;
            int defError = 0;               //error flag for function definition
            int fnIndex = defStr[1] - '0';

            assert(defStr.size() > 3);         //already debuged
            Queue<Token*> testPostfix;
            Queue<Token*> testQueue = strToQueue(defStr.substr(3, defStr.size() - 3), _info->equLst, fnIndex, defError);
            if(defError == 0){
                ShuntingYard sytest(testQueue);
                testPostfix = sytest.postfix(defError);
            }
            if(defError == 0){
                RPN rpntest(testPostfix);
                rpntest(defError, 1);
            }



            if(defError != 0){
                inputbar[0] = errorMsg[defError];
                system.setError(-98);
            }
            else{
                if(fnIndex < 10 && fnIndex >= 0){
                    (_info->equLst)[fnIndex] = defStr.substr(3, defStr.size() - 3);
                    history.push_back(defStr.substr(3, defStr.size() - 3));
                    system.setError(0);
                    INB_Hidden = !INB_Hidden;
                }
                else{
                    inputbar[0] = errorMsg[system.errorReport()];           //if the name of function defining is invalid
                    system.setError(-98);
                }
            }
        }
        else if(system.errorReport() == -98){
            //nothing happen
        }
        else if(system.errorReport() != 0){
            inputbar[0] = errorMsg[system.errorReport()];
        }
        else{
            inputbar[0] = "Input equation: "; 
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
                    PanScreen(_info, 1);
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
                    PanScreen(_info, 3);
                    system.set_info(_info);
                    command = 4;
                }
                break;


            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "UP ARROW";
                PanScreen(_info, 5);
                system.set_info(_info);
                command = 5;
                break;


            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "DOWN ARROW";
                PanScreen(_info, 7);
                system.set_info(_info);
                command = 6;
                break;


            case sf::Keyboard::PageUp:
                sidebar[SB_KEY_PRESSED] = "ZOOM IN";
                ZoomScr(1, _info, mousePos);
                system.set_info(_info);
                command = 7;
                break;


            case sf::Keyboard::PageDown:
                sidebar[SB_KEY_PRESSED] = "ZOOM OUT";
                ZoomScr(2, _info, mousePos);
                system.set_info(_info);
                command = 8;
                break;


            case sf::Keyboard::Enter:
                if(inputUID == 2 && !INB_Hidden){
                    _info->equation = inputStr;
                    cout << "input: " << inputStr << endl;
                    system.set_info(_info);
                    command = 2;
                    system.Step(command);
                    if(system.errorReport() == 0){
                        history.push_back(inputStr);
                        INB_Hidden = !INB_Hidden;
                    }
                    
                    if(system.errorReport() == 11)
                        _info->equation = " ";
                }
                else if(INB_Hidden){
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
            /*
                if(_info->polar){
                    _info->derive = false;
                }
                else{
                    _info->derive = !_info->derive;
                    system.set_info(_info);
                    command = 8;
                }
                */
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
            mousePos.x = event.mouseMove.x;
            mousePos.y = event.mouseMove.y;
            if(isDragging){
                sf::Vector2f diff(mousePos.x - dragStart.x, mousePos.y - dragStart.y);
                PanScreen(_info, diff);
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
                    case 1:                 //sidebar
                        cout << "clicked sidebar:";
                        rowNum = sidebar.overlapText(mousePos);
                        if(rowNum >= SB_HISTORY && sidebar[rowNum] != ""){
                            cursorPos = 0;                  //reset cursor
                            //delete the item
                            if(!sidebarMode && mousePos.x > SCREEN_WIDTH - 40){
                                sidebar[rowNum] = " ";
                                _info->equLst[rowNum - SB_HISTORY] = " ";
                                inputStr = "";
                                _info->equation = inputStr;
                                system.set_info(_info);
                                command = 2;
                            }
                            else{
                                inputStr = sidebar[rowNum];
                                _info->equation = inputStr;
                                system.set_info(_info);
                                command = 2;
                            }
                        }
                        else if(rowNum == SB_MODE){
                            sidebarMode = !sidebarMode;
                            if(sidebarMode){
                                sidebar[SB_MODE] = "HISTORY";
                                FN_Hidden = !FN_Hidden;
                            }
                            else{
                                sidebar[SB_MODE] = "FUNCTIONS";
                                FN_Hidden = !FN_Hidden;
                            }
                        }
                        break;

                    case 2:                 //inputbar
                        cout << "clicked inputbar:";
                        break;

                    case 3:                 //settingbar
                        cout << "clicked setting bar:";
                        rowNum = settingbar.overlapText(mousePos);
                        if(rowNum == ST_SAVE){
                            vector<string> historyDup = history;
                            clearfile("historyData.txt", "Base:FileState:Data:");
                            ofstream historyIn("historyData.txt", ios::app);
                            while(!historyDup.empty()){
                                historyIn << historyDup.begin()->c_str() << "\n";
                                historyDup.erase(historyDup.begin());
                            }


                            historyIn << "Base:FileState:Functions:" << "\n";
                            vector<string> fnLstDup = _info->equLst;
                            while(!fnLstDup.empty()){
                                historyIn << fnLstDup.begin()->c_str() << "\n";
                                fnLstDup.erase(fnLstDup.begin());
                            }
                            historyIn.close();
                        }
                        else if(rowNum == ST_CLEAR){
                            clearfile("historyData.txt", "Base:FileState:Data:");
                            ofstream historyIn("historyData.txt", ios::app);
                            historyIn << "Base:FileState:Functions:" << "\n";
                            vector<string> fnLstDup = _info->equLst;
                            while(!fnLstDup.empty()){
                                historyIn << fnLstDup.begin()->c_str() << "\n";
                                fnLstDup.erase(fnLstDup.begin());
                            }
                            historyIn.close();
                        }
                        else if(rowNum == ST_MODE){
                            _info->Gmode++;
                            if(_info->Gmode >= 4)
                                _info->Gmode = 0;
                        
                            if(_info->Gmode == 0){
                                settingbar[ST_MODE] = "CARTESIAN";
                            }
                            else if(_info->Gmode == 1){
                                settingbar[ST_MODE] = "POLAR";
                            }
                            else if(_info->Gmode == 2){
                                settingbar[ST_MODE] = "DERIVATIVE";
                            }
                            else{
                                settingbar[ST_MODE] = "ARDUINO";
                            }
                            system.set_info(_info);
                            command = 2;
                        }
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
                ZoomScr(3, _info, mousePos, event.mouseWheelScroll.delta, zoomMode);
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
            else if (event.text.unicode == 13 && inputUID == 2){
                //dont push anything when Enter is pressed
            }
            else if (event.text.unicode < 128 && inputUID == 2){
                inputStr.insert(cursorPos, 1, static_cast<char>(event.text.unicode));
                cursorPos++;
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
        
        sidebar.setLineColor(sf::Color::White, SB_MODE);
        settingbar.setLineColor(sf::Color::White, ST_CLEAR);
        settingbar.setLineColor(sf::Color::White, ST_SAVE);
        settingbar.setLineColor(sf::Color::White, ST_MODE);
        int lineID;
        int hoverUID = scanOverlap(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        if(hoverUID == 1){
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
void ZoomScr(int input_type, graph_info* _info, sf::Vector2f mousePos, float mouse_delta, int axis){
    //the zoom rate depend on the ratio of the screen
    double zoomFractY;                  //how many coordinate to change for Y 
    double zoomFractX;
    if((_info->range.y - _info->range.x) > (_info->domain.y - _info->domain.x)){
        zoomFractY = (_info->domain.y - _info->domain.x) / 50.0;
        zoomFractX = (_info->domain.y - _info->domain.x) / 50.0;
    }
    else{
        zoomFractY = (_info->range.y - _info->range.x) / 50.0;
        zoomFractX = (_info->range.y - _info->range.x) / 50.0;
    }

    double xratio1(_info->dimensions.x / _info->dimensions.y), xratio2(_info->dimensions.x / _info->dimensions.y);
    double yratio1(1), yratio2(1);
    if(axis == 1){                      //only zoom x
        zoomFractX = (_info->domain.y - _info->domain.x) / 50.0;
        yratio1 = 0;
        yratio2 = 0;
    }
    else if(axis == 2){                 //only zoom y
        zoomFractY = (_info->range.y - _info->range.x) / 50.0;
        xratio1 = 0;
        xratio2 = 0;
    }

    
    // -1 = zoom out, 1 = zoom in, 3 = no zoom
    int Zoom = 3;
    //Center of the zoom
    double ZoomX(_info->dimensions.x/2), ZoomY(_info->dimensions.y/2);
    if(input_type == 3 && mousePos.x < _info->dimensions.x 
                       && mousePos.y < _info->dimensions.y
                       && mousePos.x > 0
                       && mousePos.y > 0){
        ZoomX = mousePos.x;
        ZoomY = mousePos.y;
        xratio1 *= mousePos.x / _info->dimensions.x;
        xratio2 *= (_info->dimensions.x - mousePos.x) / _info->dimensions.x;
        yratio1 *= mousePos.y / _info->dimensions.y;
        yratio2 *= (_info->dimensions.y - mousePos.y) / _info->dimensions.y;
    }


    //coordinate of center of zoom relative to the origin in plotting coordinate
    sf::Vector2f ScrO((ZoomX - _info->origin.x) / _info->scale.x,
                      (ZoomY - _info->origin.y) / _info->scale.y);

    //if "i" or "o" zoom
    if(input_type == 1 && (_info->domain.y - _info->domain.x) >= MIN_RANGE && 
                          (_info->range.y - _info->range.x) >= MIN_RANGE)
        Zoom = 1;
    if(input_type == 2)
        Zoom = -1;
    
    //if mouse zoom
    if(input_type == 3 && mouse_delta > 0){
       if((axis == 1 && (_info->domain.y - _info->domain.x) >= MIN_RANGE) ||
          (axis == 2 && (_info->range.y - _info->range.x) >= MIN_RANGE))
            Zoom = 1;

       if(axis == 0 && ((_info->domain.y - _info->domain.x) >= MIN_RANGE) &&
         ((_info->range.y - _info->range.x) >= MIN_RANGE))
            Zoom = 1;
    }
    if(input_type == 3 && mouse_delta < 0)
        Zoom = -1;


    //if there's a zoom
    if(Zoom == 1 || Zoom == -1){
        _info->domain.x += xratio1 * zoomFractX * Zoom;
        _info->domain.y -= xratio2 * zoomFractX * Zoom;
        _info->range.x += yratio2 * zoomFractY * Zoom;
        _info->range.y -= yratio1 * zoomFractY * Zoom;
    }



    _info->reset_scale();
    //calculate position of the origin after zoom
    _info->origin = sf::Vector2f (ZoomX - (ScrO.x * _info->scale.x), 
                                  ZoomY - (ScrO.y * _info->scale.y));
}




//testPos: position you want test
//boxPt1: the top left of bounding box
//boxPt2: the bottom right of bounding box
bool isOverlap(sf::Vector2f testPos, sf::Vector2f boxPt1, sf::Vector2f boxPt2){
    return (testPos.x > boxPt1.x && testPos.x < boxPt2.x && testPos.y > boxPt1.y && testPos.y < boxPt2.y);
}








void clearfile(const string& fileName, const string& baseStr){
    if (remove(fileName.c_str()) == 0) {
        cout << "File " << fileName << " successfully deleted.\n";
    } else {
        cout << "Error deleting file";
    }

    //PATH: "C:/Users/agu4/99_00_final_project-andygu-7685/temp.txt"
    ofstream fout("temp.txt", ios::app);
    fout << baseStr << "\n";
    fout.close();

    if (rename("temp.txt", fileName.c_str()) != 0) 
        cout << "Error: Could not rename the temporary file.\n";
}







vector<string> animate::LoadHistory(int& errorFlag){
    vector<string> history;
    string metaData, equationData;
    ifstream fin("historyData.txt");

    if(fin.fail()){
        cout << "could not open file";
        exit(-1);
    }

    getline(fin, metaData);
    int section = 1;        //1 = history , 2 = function
    int fnCtr = 0;
    if(metaData == "Base:FileState:Data:"){
        while(getline(fin, equationData)){
            if(equationData == "Base:FileState:Functions:"){
                section = 2;
            }
            else{
                if(section == 1){
                    history.push_back(equationData);
                }
                else if(section == 2){
                    _info->equLst[fnCtr] = equationData;
                    fnCtr++;
                }
            }
        }
    }

    fin.close();
    return history;
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
void PanScreen(graph_info* _info, int dir){
    if(dir > 4){
        _info->origin.y -= (dir-6) * PANINC * _info->scale.y;
        _info->range.x -= (dir-6) * PANINC;
        _info->range.y -= (dir-6) * PANINC;
    }
    else{
        _info->origin.x -= (dir-2) * PANINC * _info->scale.x;
        _info->domain.x += (dir-2) * PANINC;
        _info->domain.y += (dir-2) * PANINC;
    }
}


void PanScreen(graph_info* _info, sf::Vector2f diff){
    _info->origin.x += diff.x;
    _info->origin.y += diff.y;
    _info->domain.x -= diff.x / _info->scale.x;
    _info->domain.y -= diff.x / _info->scale.x;
    _info->range.x += diff.y / _info->scale.y;
    _info->range.y += diff.y / _info->scale.y;
}


