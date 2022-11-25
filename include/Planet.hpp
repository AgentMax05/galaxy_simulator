#pragma once

#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class Planet {
public:
    Planet(double x, double y, double mass, vector<int> color);
    void addForce(Planet& planet);
    double mass, radius, x, y;
    vector<double> acceleration, velocity;
    void tick();
    void setVelocity(vector<double> newVelocity);
    
    vector<int> color;
private:
    double getDistance(Planet& planet);
    double getAngle(Planet& planet);
    int lastTick;
    const double SPEEDMULTIPLIER = 5;
};