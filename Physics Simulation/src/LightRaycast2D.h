#pragma once
#include "raylib.h"
#include <vector>

class LightRaycast2D{
    public:
    LightRaycast2D();
    void Simulate();

    private:
    struct Light{
        Vector2 position;
        float radius;
    };

    Light lamp;
    vector<Rectangle> walls;
    bool pressed;
    bool build;
    int wall_dim;
    float light_dispersion;
    void DrawSimulation();
    void LightMechanic();
    void WallMechanics();
};