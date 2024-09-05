#include "SpaceSimulation2D.h"
#include <raylib.h>
#include <cmath>
#include <chrono>
#include "globals.h"
using namespace std;

SpaceSimulation2D::SpaceSimulation2D(){
    origin = {screenWidth/2, screenHeight/2};
    G = 6.6743 * (1 / pow(10, 11));
    planets.clear();
    Sun = {origin, origin, (Vector2){0.0f, 0.0f}, start, pow(10, 12), 50, 1};
    camera = {{screenWidth / 2.0f, screenHeight / 2.0f}, origin, 0.0f, 1.0f};
}
void SpaceSimulation2D::DrawSimulation(){
        ClearBackground(Background_color);
        BeginMode2D(camera);
        for(const auto& planet : planets){
            size_t points_size = planet.planet_points.size();
            for(int index = 0; index < points_size; index++){
                DrawCircleV(planet.planet_points[index], 2, BLUE);
                if(index + 1 <= points_size-1){
                    DrawLineEx(planet.planet_points[index], planet.planet_points[index + 1], 4, BLUE);
                }
            }
            DrawCircleV(planet.position, planet.radius, colors[planet.color]);
            }
        DrawCircleV(origin, Sun.radius, colors[Sun.color]);
        EndMode2D();
        Rectangle Reset = {40, 30, 60, 20};
        DrawRectangleRoundedLines(Reset, 0.8, 4, 3, WHITE);
        DrawText("RESET", Reset.x + 14, Reset.y + 6, 10, WHITE);
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            if(mouse_pos.x >= Reset.x && mouse_pos.x <= Reset.x + Reset.width && mouse_pos.y >= Reset.y && mouse_pos.y <= Reset.y + Reset.height){
                DrawRectangleRoundedLines(Reset, 0.8, 4, 3, RED);
                DrawText("RESET", Reset.x + 14, Reset.y + 6, 10, RED);
                planets.clear();
            }
        }
    }
void SpaceSimulation2D::Physics(){
        size_t planets_num = planets.size();
        for(int planet_index = 0; planet_index < planets_num; planet_index++){
            Kinematics(planets[planet_index]);
            ForceUpdate(planets[planet_index], planets[(planet_index + 1) % planets_num]);
            if(sqrt(pow(planets[planet_index].position.x - Sun.position.x, 2) + pow(planets[planet_index].position.y - Sun.position.y, 2)) < planets[planet_index].radius + Sun.radius){
                planets.erase(planets.begin() + planet_index);
            }
        }
        AddPlanets();
    }
void SpaceSimulation2D::ForceUpdate(Planets& planet, Planets& planet2){
        double r_squared = pow(Sun.position.x - planet.position.x, 2) + pow(Sun.position.y - planet.position.y, 2);
        double gravitational_force = G * (planet.mass * Sun.mass) / r_squared;
        double planet_theta = -atan((Sun.position.y - planet.position.y) / (planet.position.x - Sun.position.x)) - M_PI;
        if(atan((Sun.position.y - planet.position.y) / (planet.position.x - Sun.position.x)) * (Sun.position.y - planet.position.y)/abs(Sun.position.y - planet.position.y) < 0){
            planet_theta = -atan((Sun.position.y - planet.position.y) / (planet.position.x - Sun.position.x));
        }
        double x_gravity = gravitational_force * cos(planet_theta);
        double y_gravity = gravitational_force * sin(planet_theta);
        planet.force.x += x_gravity;
        planet.force.y += y_gravity;

        r_squared = pow(planet2.position.x - planet.position.x, 2) + pow(planet2.position.y - planet.position.y, 2);
        gravitational_force = G * (planet.mass * planet2.mass) / r_squared;
        planet_theta = -atan((planet2.position.y - planet.position.y) / (planet.position.x - planet2.position.x)) - M_PI;
        if(atan((planet2.position.y - planet.position.y) / (planet.position.x - planet2.position.x)) * (planet2.position.y - planet.position.y)/abs(planet2.position.y - planet.position.y) < 0){
            planet_theta = -atan((planet2.position.y - planet.position.y) / (planet.position.x - planet2.position.x));
        }
        x_gravity = gravitational_force * cos(planet_theta);
        y_gravity = gravitational_force * sin(planet_theta);
        if(r_squared != 0){
            planet.force.x += x_gravity;
            planet.force.y += y_gravity;            
        }
    }
void SpaceSimulation2D::Kinematics(Planets& planet){
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> time_delta = end - planet.time;
        //Vertlet Integration
        double planet_pos_x = planet.position.x;
        double x_t = (2*planet.position.x);
        double x_minus_t = planet.position_previous.x;
        double a_t_x = (planet.force.x / planet.mass) * pow(time_delta.count(), 2);
        planet.position.x = (x_t - x_minus_t + a_t_x);
        planet.position_previous.x = planet.position.x;
        double planet_pos_y = planet.position.y;
        double y_t = (2*planet.position.y);
        double y_minus_t = planet.position_previous.y;
        double a_t_y = (planet.force.y / planet.mass) * pow(time_delta.count(), 2);
        planet.position.y = (y_t - y_minus_t + a_t_y);
        planet.position_previous.y = planet.position.y;
        planet.position_previous.x = planet_pos_x;
        planet.position_previous.y = planet_pos_y;
        planet.planet_points.push_back(planet.position);
    }
void SpaceSimulation2D::AddPlanets(){
        Planets planet;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mouse_pos = GetMousePosition();
            mouse_pos = GetScreenToWorld2D(mouse_pos, camera);
            Vector2 force = {10.0f, 0.0f};
            start = chrono::high_resolution_clock::now();
            srand(time(NULL));
            int random_color = rand() % 6;
            planet = {mouse_pos, mouse_pos, force, start, pow(10, 2), 10, random_color};
            planets.push_back(planet);
        }
    }
void SpaceSimulation2D::Simulate(){
        camera.zoom += GetMouseWheelMove() * 0.02f;
        if (camera.zoom < 0.02f) camera.zoom = 0.02f;
        DrawSimulation();
        Physics();
    }