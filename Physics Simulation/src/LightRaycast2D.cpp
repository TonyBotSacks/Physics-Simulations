#include "globals.h"
#include "LightRaycast2D.h"
#include "raylib.h"
#include <cmath>
LightRaycast2D::LightRaycast2D(){
    lamp = {(Vector2){screenWidth/2, screenHeight/2}, 15};
    pressed = false;
    light_dispersion = 0.2;
    build = false;
    wall_dim = 50;
}
void LightRaycast2D::DrawSimulation(){
    ClearBackground(Background_color);
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        Vector2 mouse_pos = GetMousePosition();
        if(mouse_pos.x < lamp.position.x + lamp.radius && mouse_pos.x > lamp.position.x - lamp.radius
            && mouse_pos.y < lamp.position.y + lamp.radius && mouse_pos.y > lamp.position.y - lamp.radius){
                pressed = true;
         }
    }
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        pressed = false;
    }
    if(pressed == true && build == false){
        Vector2 mouse_pos = GetMousePosition();
        if(mouse_pos.x < screenWidth && mouse_pos.x > 0 && mouse_pos.y < screenHeight && mouse_pos.y > 0){
            int count = 0;
            for(const auto& wall : walls){
                if(mouse_pos.x - lamp.radius <= wall.x + wall.width && mouse_pos.x + lamp.radius >= wall.x
                    && mouse_pos.y - lamp.radius <= wall.y + wall.height && mouse_pos.y + lamp.radius >= wall.y){
                    count++;
                }
            }
            if(count == 0){
                lamp.position = mouse_pos; 
            }
        }
    }
    DrawCircleV(lamp.position, lamp.radius, RED);
    size_t walls_num = walls.size();
    if (walls_num > 0){
        for(const auto& wall : walls){
            DrawRectangleRec(wall, WHITE);
        } 
    }

    LightMechanic();
    Rectangle Reset = {40, 30, 60, 20};
    DrawRectangleRoundedLines(Reset, 0.8, 4, 3, WHITE);
    DrawText("RESET", Reset.x + 14, Reset.y + 6, 10, WHITE);
    Rectangle Build = {140, 30, 60, 20};
    DrawRectangleRoundedLines(Build, 0.8, 4, 3, WHITE);
    if(build){
        DrawText("BUILD", Build.x + 14, Build.y + 6, 10, WHITE);
    }
    else{
        DrawText("MOVE", Build.x + 14, Build.y + 6, 10, WHITE);
    }
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mouse_pos = GetMousePosition();
        if(mouse_pos.x >= Reset.x && mouse_pos.x <= Reset.x + Reset.width && mouse_pos.y >= Reset.y && mouse_pos.y <= Reset.y + Reset.height){
            walls.clear();
        }
        if(mouse_pos.x >= Build.x && mouse_pos.x <= Build.x + Build.width && mouse_pos.y >= Build.y && mouse_pos.y <= Build.y + Build.height){
            if(build){
                build = false;
            }
            else{
                build = true;
            }
        }
    }
}
void LightRaycast2D::LightMechanic(){
    for(int i = 0; i < (int)(M_PI * 2 * lamp.radius / light_dispersion); i++){
        Vector2 light_spot = {lamp.position.x + (cos(light_dispersion * i) * lamp.radius), lamp.position.y - (sin(light_dispersion * i) * lamp.radius)};
        Vector2 light_end;
        WallMechanics();
        //Raycast
        for(int cast = 1; cast < (int)sqrt(pow(screenWidth, 2) + pow(screenHeight, 2)); cast++){
            light_end = {lamp.position.x + (cos(light_dispersion * i) * cast), lamp.position.y - (sin(light_dispersion * i) * cast)};
            for(auto& wall : walls){
                if(light_end.x <= wall.x + wall.width && light_end.x >= wall.x
                && light_end.y <= wall.y + wall.height && light_end.y >= wall.y){
                    light_end = {lamp.position.x + cos(light_dispersion * i) * (cast - 1), lamp.position.y - sin(light_dispersion * i) * (cast - 1)};
                    cast = (int)sqrt(pow(screenWidth, 2) + pow(screenHeight, 2)) + 10;
                    break;
                }
            }
        }
        DrawLineEx(light_spot, light_end, 1, RED);
    }
}
void LightRaycast2D::WallMechanics(){
    if(build){
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            size_t walls_num = walls.size();
            if(walls_num == 0){
                Rectangle wall = {floor(mouse_pos.x/wall_dim) * wall_dim, floor(mouse_pos.y/wall_dim) * wall_dim, wall_dim, wall_dim};
                if(pow(wall.x + wall_dim, 2) + pow(wall.y + wall_dim, 2) > pow(200, 2) + pow(50, 2)){
                    walls.push_back(wall);
                }
            }
            else if(sqrt(pow(walls[walls_num-1].x/wall_dim, 2) + pow(walls[walls_num-1].y/wall_dim, 2)) != sqrt(pow(floor(mouse_pos.x/wall_dim), 2) + pow(floor(mouse_pos.y/wall_dim), 2))){
                Rectangle wall = {floor(mouse_pos.x/wall_dim) * wall_dim, floor(mouse_pos.y/wall_dim) * wall_dim, wall_dim, wall_dim};
                if(pow(wall.x + wall_dim, 2) + pow(wall.y + wall_dim, 2) > pow(200, 2) + pow(50, 2)){
                    walls.push_back(wall);
                }
                else if(wall.y >= 50){
                    walls.push_back(wall);
                }
            }
        }
    }
}
void LightRaycast2D::Simulate(){
    DrawSimulation();
}