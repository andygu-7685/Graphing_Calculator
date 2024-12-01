#ifndef CONSTANTS_H
#define CONSTANTS_H



using namespace std;

const double pi = 3.1415926;
const double FRICTION_COEF = 0.004;
const double GRAVITY = 0.02;
const double COLLISION_COEF = 0.02;
const double PANINC = 1;                    //how much to pan in plotting coordinate
const double ZOOMRATE = 1;                  //how much to zoom in plotting coordinate
const double MIN_RANGE = 3;                 //smallest range for the graph 


const float SCREEN_WIDTH = 1400;
const float SCREEN_HEIGHT = 800;


const float SETB_X = SCREEN_WIDTH * 4/5;
const float SETB_Y = SCREEN_HEIGHT - 100;
const float SETB_W = SCREEN_WIDTH * 1/5;
const float SETB_H = 100;

const float SIDEB_X = SCREEN_WIDTH * 4/5;
const float SIDEB_Y = 0;
const float SIDEB_W = SCREEN_WIDTH * 1/5;
const float SIDEB_H = SCREEN_HEIGHT - SETB_H - 5;

const float INB_X = 0;
const float INB_Y = 0;
const float INB_W = SIDEB_W;
const float INB_H = 100;

const int PARTS = 5;
const int TYPES = 3;
const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;
const int SB_HISTORY = SB_KEY_PRESSED + 1;

const int IN_EQUATION = 1;

const int ST_SAVE = 0;
const int ST_CLEAR = 1;


#endif 
