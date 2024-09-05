#pragma once
#include "raylib.h"
#include <string>
#include <vector>
using namespace std;

class UI{
public:
    UI();
    void GUI(Texture2D& sim_1_texture, Texture2D& sim_2_texture, Texture2D& sim_3_texture, Texture2D& sim_4_texture, Camera2D& camera);
    bool picked;
    
private:
    int simulation_index;
    Vector2 vec_sim1;
    Vector2 vec_sim2;
    Vector2 vec_sim3;
    vector<Vector2> Simulation_Buttons;
    int scroll_length;
    bool PressedSpot(Rectangle button, Vector2 mouse_pos);
};