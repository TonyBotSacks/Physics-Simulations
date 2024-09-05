#pragma once
#include <raylib.h>
#include <vector>
#include <chrono>
using namespace std;

class SpaceSimulation2D
{
public:
    SpaceSimulation2D();
    void Simulate();

private:
    struct Planets{
        Vector2 position;
        Vector2 position_previous;
        Vector2 force;
        chrono::high_resolution_clock::time_point time;
        double mass;
        float radius;
        int color;
        vector<Vector2> planet_points;
    };
    Vector2 origin;
    double G;
    Planets Sun;
    vector<Planets> planets;
    Camera2D camera;
    void DrawSimulation();
    void Physics();
    void ForceUpdate(Planets& planet, Planets& planet2);
    void Kinematics(Planets& planet);
    void AddPlanets();
};