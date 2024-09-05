#ifndef GLOBALS_H
#define GLOBALS_H
#include <raylib.h>
#include <chrono>
using namespace std;

extern chrono::high_resolution_clock::time_point start;
extern const double M_PI;
extern Color Background_color;
extern Color colors[];
extern const int button_sizex;
extern const int button_sizey;
extern const int fps;
extern const int screenWidth;
extern const int screenHeight;

#endif // GLOBALS_H