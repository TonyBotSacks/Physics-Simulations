#pragma once
using namespace std;

class FallingSandSimulation
{
public:
    FallingSandSimulation();
    void Simulate();

private:
    int gravity;
    void DrawSimulation();
    void GridMechanics();
};