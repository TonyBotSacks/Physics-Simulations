#include "FallingSandSimulation.h"
#include <raylib.h>
#include <iostream>
#include "globals.h"
#include <cmath>
using namespace std;

static constexpr int screenwidth = 1000;
static constexpr int screenheight = 650;
static constexpr int grain_size = 2;
static constexpr int grid_sizex = screenwidth / grain_size;
static constexpr int grid_sizey = screenheight / grain_size;

int sand_grid[grid_sizey][grid_sizex];

FallingSandSimulation::FallingSandSimulation(){
    gravity = 1;
    for(int i = 0; i < grid_sizex; i++){
        for(int j = 0; j < grid_sizey; j++){
            sand_grid[j][i] = 0;
        }
    }
}
void FallingSandSimulation::DrawSimulation(){
    ClearBackground(Background_color);
    for(int i = 0; i < grid_sizex; i++){
        for(int j = 0; j < grid_sizey; j++){
            if(sand_grid[j][i] == 1){
                DrawRectangle(i * grain_size, j * grain_size, grain_size, grain_size, WHITE);
            }
            if(sand_grid[j][i] == 2){
                DrawRectangle(i * grain_size, j * grain_size, grain_size, grain_size, RED);
            }
        }
    }
    //Reset Button
    Rectangle Reset = {100, 50, 60, 20};
    DrawRectangleRoundedLines(Reset, 0.8, 4, 3, WHITE);
    DrawText("RESET", Reset.x + 14, Reset.y + 6, 10, WHITE);
    //Gravity Scale
    DrawTriangle((Vector2){60, 20 + (int)sqrt(300)}, (Vector2){80, 20 + (int)sqrt(300)}, (Vector2){70, 20}, WHITE);
    DrawTriangle((Vector2){60, 80}, (Vector2){70, (int)sqrt(300) + 80}, (Vector2){80, 80}, WHITE);
    DrawText(to_string(gravity).c_str(), 65, 50, 20, WHITE);
    DrawText("G", 30, 50, 20, WHITE);
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        Vector2 mouse_pos = GetMousePosition();
        if(mouse_pos.x >= 60 && mouse_pos.x <= 80 && mouse_pos.y >= 20 && mouse_pos.y <= 20 + (int)sqrt(300) && gravity + 1 <= 10){
            gravity += 1;
        }
        if(mouse_pos.x >= 60 && mouse_pos.x <= 80 && mouse_pos.y >= 60 && mouse_pos.y <= 80 + (int)sqrt(300) && gravity - 1 >= 1){
            gravity -= 1;
        }
        if(mouse_pos.x >= Reset.x && mouse_pos.x <= Reset.x + Reset.width && mouse_pos.y >= Reset.y && mouse_pos.y <= Reset.y + Reset.height){
            DrawRectangleRoundedLines(Reset, 0.8, 4, 3, RED);
            DrawText("RESET", Reset.x + 14, Reset.y + 6, 10, RED); 
            for(int i = 0; i < grid_sizex; i++){
                for(int j = 0; j < grid_sizey; j++){
                    sand_grid[j][i] = 0;
                }
            }
        }
    }
}
void FallingSandSimulation::GridMechanics(){
    for(int i = 0; i < grid_sizex; i++){
        for(int j = 0; j < grid_sizey; j++){
            if(sand_grid[j][i] == 1){
                if(sand_grid[j + 1][i] == 2 || j + 1 >= grid_sizey){
                    if(sand_grid[j + 1][i + 1] == 0 && sand_grid[j + 1][i - 1] == 0 && (i + 1) <= grid_sizex-1 && (i - 1) >= 0){
                        int side = GetRandomValue(-1, 1);
                        sand_grid[j][i] = 0;
                        sand_grid[j + 1][i + side] = -1;
                    }
                    else if(sand_grid[j + 1][i + 1] == 0 && (i + 1) && (i + 1) <= grid_sizex - 1){
                        sand_grid[j][i] = 0;
                        sand_grid[j + 1][i + 1] = -1;
                    }
                    else if(sand_grid[j + 1][i - 1] == 0 && (i - 1) >= 0){
                        sand_grid[j][i] = 0;
                        sand_grid[j + 1][i - 1] = -1;
                    }
                    else{
                        sand_grid[j][i] = 2;
                    }
                }
                else{
                    sand_grid[j][i] = 0;
                    sand_grid[j + 1][i] = -1;
                }
            }
        }
    }
    for(int i = 0; i < grid_sizex; i++){
        for(int j = 0; j < grid_sizey; j++){
            if(sand_grid[j][i] == -1){
                sand_grid[j][i] = 1;
            }
        }
    }
}
void FallingSandSimulation::Simulate(){
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        Vector2 mouse_position = GetMousePosition();
        if(mouse_position.x <= screenWidth && mouse_position.x >= 0 && mouse_position.y <= screenHeight && mouse_position.y >= 0){
            sand_grid[(int)mouse_position.y/grain_size][(int)mouse_position.x/grain_size] = 1;
        }
    }
    DrawSimulation();
    for(int i = 0; i < gravity; i++){
        GridMechanics();
    }
}