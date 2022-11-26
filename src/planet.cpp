#include "Planet.hpp"

#include <math.h>

Planet::Planet(double newX, double newY, double newMass, vector<int> newColor) {
    x = newX;
    y = newY;
    mass = newMass;
    radius = sqrt(mass / (M_PI * 10));
    acceleration = {0, 0};
    velocity = {0, 0};

    color = newColor;
}

void Planet::addForce(double force, double angle, double deltaTime) {
    force = force * deltaTime;

    double deltaAcceleration = force / mass;
    acceleration = {acceleration[0] + deltaAcceleration * cos(angle), acceleration[1] + deltaAcceleration * sin(angle)};
}

void Planet::tick(double deltaTime) {
    velocity = {velocity[0] + acceleration[0], velocity[1] - acceleration[1]};

    x = x + (velocity[0] * deltaTime);
    y = y - (velocity[1] * deltaTime);

    acceleration = {0, 0};
}

void Planet::setVelocity(vector<double> newVelocity) {
    velocity = newVelocity;
}

double Planet::calcForce(Planet& p1, Planet& p2) {
    double distance = calcDistance(p1, p2);

    if (distance == 0) {
        return 0;
    } 

    return (p1.mass * p2.mass) / pow(distance, 2);
}

double Planet::calcDistance(Planet& p1, Planet& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double Planet::calcAngle(Planet& p1, Planet& p2) {
    double angle = atan(abs(p1.y - p2.y) / abs(p2.x - p1.x));

    if (p2.x < p1.x) {
        angle = M_PI - angle;
    }

    if (p1.y > p2.y) {
        angle = 2 * M_PI - angle;
    }

    return angle;
}

bool Planet::checkCollision(Planet& p1, Planet& p2) {
    return calcDistance(p1, p2) <= (p1.radius + p2.radius);
}