#include "Planet.hpp"

#include <math.h>

Planet::Planet(double newX, double newY, double newMass, vector<int> newColor) {
    x = newX;
    y = newY;
    mass = newMass;
    radius = sqrt(100 * mass / 3.14);
    acceleration = {0, 0};
    velocity = {0, 0};
    lastTick = SDL_GetTicks();

    color = newColor;
}

void Planet::addForce(Planet& planet) {
    double deltaTime = (SDL_GetTicks() - lastTick) * SPEEDMULTIPLIER / 1000.0;
    
    double gravForce;
    double angle;
    if (getDistance(planet) == 0) {
        gravForce = 0;
        angle = 0;
    } else {

        gravForce = (mass * planet.mass * deltaTime) / (getDistance(planet));
        angle = getAngle(planet);
    }

    int multiplierX = planet.x < x ? -1 : 1;
    int multiplierY = planet.y > y ? -1 : 1;

    double deltaAcceleration = gravForce / mass;
    acceleration = {acceleration[0] + (deltaAcceleration * abs(cos(angle)) * multiplierX), acceleration[1] + (deltaAcceleration * abs(sin(angle)) * multiplierY)};
}

double Planet::getDistance(Planet& planet) {
    return sqrt(pow(x - planet.x, 2) + pow(y - planet.y, 2));
}

double Planet::getAngle(Planet& planet) {
    return atan((y - planet.y) / (planet.x -x));
}

void Planet::tick() {
    velocity = {velocity[0] + acceleration[0], velocity[1] + acceleration[1]};
    x += velocity[0];
    y -= velocity[1];
    acceleration = {0, 0};
    lastTick = SDL_GetTicks();
}

void Planet::setVelocity(vector<double> newVelocity) {
    velocity = newVelocity;
}