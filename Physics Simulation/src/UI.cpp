#include "UI.h"
#include "raylib.h"
#include "globals.h"
#include "SpaceSimulation2D.h"
#include "FallingSandSimulation.h"
#include "DoublePendulum.h"
#include "LightRaycast2D.h"
#include <string>
#include <iostream>
using namespace std;

//Simulation classes
DoublePendulum Double_Pendulum;
FallingSandSimulation Falling_Sand_Simulation;
SpaceSimulation2D Space_Simulation;
LightRaycast2D Light_Raycast;

UI::UI(){
    picked = false;
}
bool UI::PressedSpot(Rectangle button, Vector2 mouse_pos){
    if(mouse_pos.x >= button.x && mouse_pos.x <= button.width + button.x && 
        mouse_pos.y >= button.y && mouse_pos.y <= button.height + button.y){
        return true;
    }
    else{
        return false;
    }
}

void UI::GUI(Texture2D& sim_1_texture, Texture2D& sim_2_texture, Texture2D& sim_3_texture, Texture2D& sim_4_texture, Camera2D& camera){
    Vector2 vec_sim1 = {50, 50};
    Vector2 vec_sim2 = {screenWidth - button_sizex - 50, vec_sim1.y};
    Vector2 vec_sim3 = {vec_sim1.x, vec_sim1.y + button_sizey + 50};
    Vector2 vec_sim4 = {screenWidth - button_sizex - 50, vec_sim3.y};
    Simulation_Buttons = {vec_sim1, vec_sim2, vec_sim3, vec_sim4};
    if(picked == false){
        ClearBackground(Background_color);
        DrawTexture(sim_1_texture, vec_sim1.x, vec_sim1.y, WHITE);
        DrawTexture(sim_2_texture, vec_sim2.x, vec_sim2.y, WHITE);
        DrawTexture(sim_3_texture, vec_sim3.x, vec_sim3.y, WHITE);
        DrawTexture(sim_4_texture, vec_sim4.x, vec_sim4.y, WHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            mouse_pos = GetScreenToWorld2D(mouse_pos, camera);
            size_t Buttons_num = Simulation_Buttons.size();
            for(int index = 0; index < Buttons_num; index++){
                Rectangle button = {Simulation_Buttons[index].x, Simulation_Buttons[index].y, button_sizex, button_sizey};
                if(PressedSpot(button, mouse_pos)){
                    picked = true;
                    simulation_index = index;
                    break;
                }
            }
        }
    }
    else{
        if(simulation_index == 0){
            Space_Simulation.Simulate();
        }
        else if(simulation_index == 1){
            Falling_Sand_Simulation.Simulate();
        }
        else if(simulation_index == 2){
            Double_Pendulum.Simulate();
        }
        else if(simulation_index == 3){
            Light_Raycast.Simulate();
        }
        Rectangle back_button_rec = {screenWidth-50, 30, 25, 20};
        DrawRectangleRec(back_button_rec, RED);
        DrawTriangle((Vector2){back_button_rec.x, back_button_rec.y + back_button_rec.height}, (Vector2){back_button_rec.x, back_button_rec.y}, 
            (Vector2){back_button_rec.x - 20, back_button_rec.y + back_button_rec.height/2}, RED);

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            if(PressedSpot((Rectangle){back_button_rec.x - 20, back_button_rec.y, back_button_rec.x + 20, back_button_rec.height}, mouse_pos)){
                picked = false;
            }
        }
    }
}