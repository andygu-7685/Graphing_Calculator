#ifndef CONSTANTS_H
#define CONSTANTS_H



using namespace std;

const double pi = 3.1415926;
const double FRICTION_COEF = 0.004;
const double GRAVITY = 0.02;
const double COLLISION_COEF = 0.02;
const double PANINC = 1;                    //how much to pan in plotting coordinate
const double ZOOMRATE = 1;                   //how much to zoom in plotting coordinate


const float SCREEN_WIDTH = 1400;
const float SCREEN_HEIGHT = 800;
const float WORK_PANEL = SCREEN_WIDTH*4/5;
const float SIDE_BAR = SCREEN_WIDTH*1/5;

const int PARTS = 5;
const int TYPES = 3;
const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;

const int IN_EQUATION = 1;

const int ST_SAVE = 0;
const int ST_CLEAR = 1;


#endif //CONSTANTS_H
