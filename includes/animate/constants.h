#ifndef CONSTANTS_H
#define CONSTANTS_H

using namespace std;

//math and physics constants
const double pi = 3.1415926;
const double e = 2.7182818;
const double _EPSILON = 0.00000000000001;
const double FRICTION_COEF = 0.004;
const double GRAVITY = 0.02;
const double COLLISION_COEF = 0.02;

//graph constants
const double PANFRAC = 1.0 / 50.0;          //how much to pan as fraction plotting domain or range
const double ZOOMRATE = 2;                  //how much to zoom in plotting coordinate
const double MIN_RANGE = 0.01;                 //smallest range for the graph 
extern double POLAR_RENDER_H;
extern double POLAR_RENDER_L;

//UI constants
const float SCREEN_WIDTH = 1400;
const float SCREEN_HEIGHT = 800;

const float SETB_X = SCREEN_WIDTH * 4/5;
const float SETB_Y = SCREEN_HEIGHT - 100;
const float SETB_W = SCREEN_WIDTH * 1/5;
const float SETB_H = 100;

const float SIDEB_X = SCREEN_WIDTH * 4/5;
const float SIDEB_Y = 0;
const float SIDEB_W = SCREEN_WIDTH * 1/5;
const float SIDEB_H = 200;

const float INB_X = 0;
const float INB_Y = 0;
const float INB_W = SCREEN_WIDTH * 1/3;
const float INB_H = 100;

const float FNB_X = SCREEN_WIDTH * 4/5;
const float FNB_Y = 205;
const float FNB_W = SCREEN_WIDTH * 1/5;
const float FNB_H = SCREEN_HEIGHT - SETB_H - SIDEB_H - 10;

const float HISTB_X = SCREEN_WIDTH * 4/5;
const float HISTB_Y = 205;
const float HISTB_W = SCREEN_WIDTH * 1/5;
const float HISTB_H = SCREEN_HEIGHT - SETB_H - SIDEB_H - 10;

const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;
const int SB_MODE = SB_KEY_PRESSED + 1;
const int SB_HISTORY = SB_MODE + 1;
const int SB_HISTORY_END = 20;

const int ST_SAVE = 0;
const int ST_CLEAR = 1;
const int ST_MODE = 2;

const int SIDEB_UID = 1;
const int INB_UID = 2;
const int SETB_UID = 3;
const int FNB_UID = 4;
const int HISTB_UID = 5;

const int CART_MODE = 0;
const int POLAR_MODE = CART_MODE + 1;
const int DERIVE_MODE = POLAR_MODE + 1;
const int ARD_MODE = DERIVE_MODE + 1;

const int PARTS = 5;
const int TYPES = 3;



#endif 
