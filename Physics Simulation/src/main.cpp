#include "raylib.h"
#include "globals.h"
#include "UI.h"
#include <string>
#include <cmath>
int main(){
    UI GUI_SCREEN;

    InitWindow(screenWidth, screenHeight, "Physics Simulator");
    SetTargetFPS(fps);

    string sim_1_path = "images/sim_1.png";
    Image sim_1_image = LoadImage(sim_1_path.c_str());
    ImageResize(&sim_1_image, button_sizex, button_sizey);
    Texture2D sim_1_texture = LoadTextureFromImage(sim_1_image);

    string sim_2_path = "images/sim_2.png";
    Image sim_2_image = LoadImage(sim_2_path.c_str());
    ImageResize(&sim_2_image, button_sizex, button_sizey);
    Texture2D sim_2_texture = LoadTextureFromImage(sim_2_image);

    string sim_3_path = "images/sim_3.png";
    Image sim_3_image = LoadImage(sim_3_path.c_str());
    ImageResize(&sim_3_image, button_sizex, button_sizey);
    Texture2D sim_3_texture = LoadTextureFromImage(sim_3_image);
    
    string sim_4_path = "images/sim_4.png";
    Image sim_4_image = LoadImage(sim_4_path.c_str());
    ImageResize(&sim_4_image, button_sizex, button_sizey);
    Texture2D sim_4_texture = LoadTextureFromImage(sim_4_image);
    Camera2D camera = {0};
    camera.target = (Vector2){screenWidth/2.0f, screenHeight/2.0f};
    camera.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    float texture_num = 4;
    int scroll_length = ((ceil(texture_num/2) - 2) * (50 + button_sizey));

    while (!WindowShouldClose()){
        if(GUI_SCREEN.picked == false){
            float mouse_scroll = GetMouseWheelMove() * 10.0f;
            if(scroll_length + mouse_scroll <= ((ceil(texture_num/2) - 2) * (50 + button_sizey)) && scroll_length + mouse_scroll >= 0) camera.target.y -= mouse_scroll;
            if(scroll_length + mouse_scroll <= ((ceil(texture_num/2) - 2) * (50 + button_sizey)) && scroll_length + mouse_scroll >= 0) scroll_length += mouse_scroll;
            if(scroll_length > ((ceil(texture_num/2) - 2) * (50 + button_sizey))) scroll_length = ((ceil(texture_num/2) - 2) * (50 + button_sizey));
            if(scroll_length < 0) scroll_length = 0;
        }
        BeginDrawing();
        BeginMode2D(camera);
        if(GUI_SCREEN.picked){
            EndMode2D();
        }
        GUI_SCREEN.GUI(sim_1_texture, sim_2_texture, sim_3_texture, sim_4_texture, camera);
        EndMode2D();
        EndDrawing();
    }   
    UnloadTexture(sim_1_texture);
    UnloadTexture(sim_2_texture);
    UnloadTexture(sim_3_texture);
    UnloadTexture(sim_4_texture);

    CloseWindow();
    return 0;
}