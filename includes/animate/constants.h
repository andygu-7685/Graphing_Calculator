#ifndef CONSTANTS_H
#define CONSTANTS_H

const double pi = 3.1415926;
const double FRICTION_COEF = 0.004;
const double GRAVITY = 0.02;
const double COLLISION_COEF = 0.02;


const float SCREEN_WIDTH = 1400;
const float SCREEN_HEIGHT = 800;
const float WORK_PANEL = SCREEN_WIDTH*4/5;
const float SIDE_BAR = SCREEN_WIDTH*1/5;

const int PARTS = 5;
const int TYPES = 3;
const int PANINC = 1;
const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;
#endif // CONSTANTS_H
