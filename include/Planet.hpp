#pragma once

#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class Planet {
public:
    double mass, radius, x, y;
    vector<double> acceleration, velocity;

    Planet(double x, double y, double mass, vector<int> color);
    void addForce(double force, double angle, double deltaTime);

    void tick(double deltaTime);
    void setVelocity(vector<double> newVelocity);

    static double calcForce(Planet& p1, Planet& p2);
    static double calcAngle(Planet& p1, Planet& p2);
    static double calcDistance(Planet& p1, Planet& p2);
    static bool checkCollision(Planet& p1, Planet& p2);

    vector<int> color;
private:
};