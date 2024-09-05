#include "DoublePendulum.h"
#include <raylib.h>
#include <iostream>
#include "globals.h"
#include <cmath>
using namespace std;

DoublePendulum::DoublePendulum(){
    fps = 60;
    origin = {screenWidth/2, screenHeight/2};
    gravity = 9;
    pendulum1_length = 150;
    pendulum2_length = 150;
    pendulum_mass1 = 1;
    pendulum_mass2 = 1;
    pendulum_1 = {origin.x, origin.y, 5, pendulum1_length};
    starting_angle = -M_PI/2;
    pendulum1_start = {cos(starting_angle) * pendulum1_length, sin(starting_angle) * pendulum1_length};
    pendulum2_start = {cos(starting_angle) * pendulum2_length, sin(starting_angle) * pendulum2_length};

    Pendulum_1 = {pendulum1_start, gravity, 0, gravity, starting_angle, starting_angle, pendulum1_length, 1, pendulum_mass1};
    Pendulum_2 = {pendulum2_start, gravity, 0, gravity, starting_angle, starting_angle, pendulum2_length, 1, pendulum_mass2};
}
void DoublePendulum::DrawSimulation(){
    ClearBackground(Background_color);
    size_t point_draw_size = Pendulum_2.positions.size();
    for(int i = 0; i < point_draw_size; i++){
        DrawCircleV(Pendulum_2.positions[i], 1, WHITE);
        if(i != point_draw_size-1){
        DrawLineEx(Pendulum_2.positions[i], Pendulum_2.positions[i + 1], 2, WHITE);
        }
    }
    DrawLineEx((Vector2){origin.x + Pendulum_1.position.x, origin.y - Pendulum_1.position.y}, 
    (Vector2){origin.x + pendulum_1.width/2, origin.y}, 4, WHITE);
    DrawCircle(pendulum_1.x + (pendulum_1.width/2), pendulum_1.y, 8, RED);
    Vector2 pendlum2_screen_pos = {origin.x + Pendulum_1.position.x + Pendulum_2.position.x, origin.y - Pendulum_1.position.y - Pendulum_2.position.y};
    DrawLineEx(pendlum2_screen_pos, (Vector2){origin.x + Pendulum_1.position.x, origin.y - Pendulum_1.position.y}, 4, WHITE);
    DrawCircleV((Vector2){origin.x + Pendulum_1.position.x, origin.y - Pendulum_1.position.y}, 8, RED);
    DrawCircleV(pendlum2_screen_pos, 8, RED);
    //Pendulum Length
    DrawTriangle((Vector2){50, 20 + (int)sqrt(300)}, (Vector2){70, 20 + (int)sqrt(300)}, (Vector2){60, 20}, WHITE);
    DrawTriangle((Vector2){50, 80}, (Vector2){60, (int)sqrt(300) + 80}, (Vector2){70, 80}, WHITE);
    DrawText(to_string(Pendulum_1.length).c_str(), 50, 50, 20, WHITE);
    DrawText("L1", 20, 50, 20, WHITE);
    DrawTriangle((Vector2){120, 20 + (int)sqrt(300)}, (Vector2){140, 20 + (int)sqrt(300)}, (Vector2){130, 20}, WHITE);
    DrawTriangle((Vector2){120, 80}, (Vector2){130, (int)sqrt(300) + 80}, (Vector2){140, 80}, WHITE);
    DrawText(to_string(Pendulum_2.length).c_str(), 120, 50, 20, WHITE);
    DrawText("L2", 90, 50, 20, WHITE);
    //Gravity Scale
    DrawTriangle((Vector2){190, 20 + (int)sqrt(300)}, (Vector2){210, 20 + (int)sqrt(300)}, (Vector2){200, 20}, WHITE);
    DrawTriangle((Vector2){190, 80}, (Vector2){200, (int)sqrt(300) + 80}, (Vector2){210, 80}, WHITE);
    DrawText(to_string(gravity).c_str(), 190, 50, 20, WHITE);
    DrawText("G", 160, 50, 20, WHITE);
    //Mass
    DrawTriangle((Vector2){260, 20 + (int)sqrt(300)}, (Vector2){280, 20 + (int)sqrt(300)}, (Vector2){270, 20}, WHITE);
    DrawTriangle((Vector2){260, 80}, (Vector2){270, (int)sqrt(300) + 80}, (Vector2){280, 80}, WHITE);
    DrawText(to_string(Pendulum_1.mass).c_str(), 260, 50, 20, WHITE);
    DrawText("M1", 225, 50, 20, WHITE);
    DrawTriangle((Vector2){330, 20 + (int)sqrt(300)}, (Vector2){350, 20 + (int)sqrt(300)}, (Vector2){340, 20}, WHITE);
    DrawTriangle((Vector2){330, 80}, (Vector2){340, (int)sqrt(300) + 80}, (Vector2){350, 80}, WHITE);
    DrawText(to_string(Pendulum_2.mass).c_str(), 330, 50, 20, WHITE);
    DrawText("M2", 295, 50, 20, WHITE);
    //Reset Button
    Rectangle Reset;
    Reset = {370, 50, 60, 20};
    DrawRectangleRoundedLines(Reset, 0.8, 4, 3, WHITE);
    DrawText("RESET", Reset.x + 14, Reset.y + 6, 10, WHITE);
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        Vector2 mouse_pos = GetMousePosition();
        //Pendulum Length
        if(mouse_pos.x >= 50 && mouse_pos.x <= 70 && mouse_pos.y >= 20 && mouse_pos.y <= 20 + (int)sqrt(300) && Pendulum_1.length + Pendulum_2.length < screenHeight/2 - 10){
            Pendulum_1.length += 1;
        }
        if(mouse_pos.x >= 50 && mouse_pos.x <= 70 && mouse_pos.y >= 60 && mouse_pos.y <= 80 + (int)sqrt(300) && Pendulum_1.length - 1 >= 20){
            Pendulum_1.length -= 1;
        }
        if(mouse_pos.x >= 120 && mouse_pos.x <= 140 && mouse_pos.y >= 20 && mouse_pos.y <= 20 + (int)sqrt(300) && Pendulum_1.length + Pendulum_2.length < screenHeight/2 - 10){
            Pendulum_2.length += 1;
        }
        if(mouse_pos.x >= 120 && mouse_pos.x <= 140 && mouse_pos.y >= 60 && mouse_pos.y <= 80 + (int)sqrt(300) && Pendulum_2.length - 1 >= 20){
            Pendulum_2.length -= 1;
        }
        //Gravity
        if(mouse_pos.x >= 190 && mouse_pos.x <= 210 && mouse_pos.y >= 20 && mouse_pos.y <= 20 + (int)sqrt(300) && (int)gravity + 1 <= 100){
            gravity += 1;
        }
        if(mouse_pos.x >= 190 && mouse_pos.x <= 210 && mouse_pos.y >= 60 && mouse_pos.y <= 80 + (int)sqrt(300) && (int)gravity - 1 >= 1){
            gravity -= 1;
        }
        //Mass
        if(mouse_pos.x >= 260 && mouse_pos.x <= 280 && mouse_pos.y >= 20 && mouse_pos.y <= 20 + (int)sqrt(300)){
            Pendulum_1.mass += 1;
        }
        if(mouse_pos.x >= 260 && mouse_pos.x <= 280 && mouse_pos.y >= 60 && mouse_pos.y <= 80 + (int)sqrt(300) && (int)Pendulum_1.mass - 1 > 0){
            Pendulum_1.mass -= 1;
        }
        if(mouse_pos.x >= 330 && mouse_pos.x <= 350 && mouse_pos.y >= 20 && mouse_pos.y <= 20 + (int)sqrt(300)){
        Pendulum_2.mass += 1;
        }
        if(mouse_pos.x >= 330 && mouse_pos.x <= 350 && mouse_pos.y >= 60 && mouse_pos.y <= 80 + (int)sqrt(300) && (int)Pendulum_2.mass - 1 > 0){
            Pendulum_2.mass -= 1;
        }
        if(mouse_pos.x >= Reset.x && mouse_pos.x <= Reset.x + Reset.width && mouse_pos.y >= Reset.y && mouse_pos.y <= Reset.y + Reset.height){
            Pendulum_1.position = pendulum1_start;
            Pendulum_1.angle_velocity = 0.0f;
            Pendulum_1.angle_acceleration = gravity;
            Pendulum_1.angle_previous = starting_angle;
            Pendulum_1.theta = starting_angle;
            Pendulum_1.angle_previous = gravity;
            Pendulum_1.positions.clear();
            Pendulum_2.position = pendulum2_start;
            Pendulum_2.angle_velocity = 0.0f;
            Pendulum_2.angle_acceleration = gravity;
            Pendulum_2.angle_previous = starting_angle;
            Pendulum_2.theta = starting_angle;
            Pendulum_2.angle_previous = gravity;
            Pendulum_2.positions.clear();

            DrawRectangleRoundedLines(Reset, 0.8, 4, 3, RED);
            DrawText("RESET", Reset.x + 14, Reset.y + 6, 10, RED);
        }
    }
}
void DoublePendulum::TwoPendulumDynamics(){
    //Transform Angles       
    if((int)abs(Pendulum_1.theta * (180/M_PI)) % 180 == 0){
        Pendulum_1.theta *= -1;
    }
    if((int)abs(Pendulum_2.theta * (180/M_PI)) % 180 == 0){
        Pendulum_2.theta *= -1;
    }
    const float l1 = Pendulum_1.length;
    const float l2 = Pendulum_2.length;

    double equation_part1 = -gravity*(2*Pendulum_1.mass + Pendulum_2.mass) * sin(Pendulum_1.theta);
    double equation_part2 = -Pendulum_2.mass*gravity*sin(Pendulum_1.theta - 2*Pendulum_2.theta);
    double equation_part3 = -2*sin(Pendulum_1.theta - Pendulum_2.theta)*Pendulum_2.mass
            *(pow(Pendulum_2.angle_velocity, 2)*l2 + pow(Pendulum_1.angle_velocity, 2) * 
            l1 * cos(Pendulum_1.theta - Pendulum_2.theta));
    double equation_part4 = l1*(2*Pendulum_1.mass + Pendulum_2.mass -
            Pendulum_2.mass * cos(2*Pendulum_1.theta - 2*Pendulum_2.theta));

    Pendulum_1.angle_acceleration = (equation_part1 + equation_part2 + equation_part3) / equation_part4 / Pendulum_1.length;

    double equation_part1_2 = 2*sin(Pendulum_1.theta - Pendulum_2.theta) * (pow(Pendulum_1.angle_velocity, 2) * l1*
    (Pendulum_1.mass + Pendulum_2.mass) + gravity*(Pendulum_1.mass + Pendulum_2.mass)*cos(Pendulum_1.theta) +
            pow(Pendulum_2.angle_velocity, 2) * l2 * Pendulum_2.mass * cos(Pendulum_1.theta - Pendulum_2.theta));
    double equation_part2_2 = l2 * (2*Pendulum_1.mass + Pendulum_2.mass - 
            Pendulum_2.mass*cos(2*Pendulum_1.theta - 2*Pendulum_2.theta));
    Pendulum_2.angle_acceleration = equation_part1_2 / equation_part2_2/ Pendulum_2.length;
    Kinematics_Euler(Pendulum_1);
    Kinematics_Euler(Pendulum_2);
}

void DoublePendulum::Kinematics_Euler(Pendulum& Pendulum){
    //Eulerian Method 
    Pendulum.angle_velocity += Pendulum.angle_acceleration;
    Pendulum.theta += Pendulum.angle_velocity;
    Pendulum.position.x = Pendulum.length * cos(Pendulum.theta - M_PI/2);
    Pendulum.position.y = Pendulum.length * sin(Pendulum.theta - M_PI/2);
    Pendulum.angle_previous = Pendulum.theta;
}
void DoublePendulum::Simulate(){
    DrawSimulation();
    TwoPendulumDynamics();
    Vector2 pos = {origin.x + Pendulum_1.position.x + Pendulum_2.position.x, origin.y - Pendulum_1.position.y - Pendulum_2.position.y};
    Pendulum_2.positions.push_back(pos);
}