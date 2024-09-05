#include "globals.h"

chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
const double M_PI = 3.14159265358979323846;
Color Background_color = {0, 0, 50};
Color colors[] = {
    {255, 255, 255, 255},
    {255, 165, 0, 255},
    {0, 255, 0, 255},
    {255, 255, 0, 255},
    {0, 0, 255, 255},
    {255, 0, 0, 255}
};
const int button_sizex = 400;
const int button_sizey = 260;

const int fps = 60;
const int screenWidth = 1000;
const int screenHeight = 650;