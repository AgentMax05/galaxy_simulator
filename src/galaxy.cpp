#include "Galaxy.hpp"

#include <iostream>

#include <math.h>

Galaxy::Galaxy() {
    lastTick = SDL_GetTicks();
}

void Galaxy::addPlanet(Planet planet) {
    planets.push_back(planet);
}

void Galaxy::tick(RenderWindow& window) {
    double deltaTime = (SDL_GetTicks() - lastTick) * SPEEDMULTIPLIER / 1000.0;
    for (int i = 0; i < planets.size(); i++) {
        for (int j = i + 1; j < planets.size(); j++) {
            double force = Planet::calcForce(planets[i], planets[j]);
            double angle = Planet::calcAngle(planets[i], planets[j]);

            planets[i].addForce(force, angle, deltaTime);
            planets[j].addForce(force, angle + M_PI, deltaTime);
        }

        planets[i].tick(deltaTime);

        window.render(planets[i]);
    }
    lastTick = SDL_GetTicks();
}