#pragma once
#include <vector>
#include "raylib.h"
using namespace std;

class DoublePendulum
{
public:
    int fps;
    DoublePendulum();
    void Simulate();

private:
    Vector2 origin;
    int gravity;
    struct Pendulum{
        Vector2 position;
        double force;
        double angle_velocity;
        double angle_acceleration;
        double angle_previous;
        double theta;
        int length;
        int direction;
        int mass;
        vector<Vector2> positions;
    };
    int pendulum1_length;
    int pendulum2_length;
    int pendulum_mass1;
    int pendulum_mass2;
    double starting_angle;
    Pendulum Pendulum_1;
    Pendulum Pendulum_2;
    Rectangle pendulum_1;
    Vector2 pendulum1_start;
    Vector2 pendulum2_start;
    bool simulation_type;
    void DrawSimulation();
    void Kinematics_Euler(Pendulum& Pendulum);
    void TwoPendulumDynamics();
};