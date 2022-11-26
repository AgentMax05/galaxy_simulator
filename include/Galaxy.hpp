#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Planet.hpp"
#include "RenderWindow.hpp"

using namespace std;

class Galaxy {
public:
    Galaxy();
    void addPlanet(Planet planet);
    void tick(RenderWindow& window);
    vector<Planet> planets = {};
private:
    double lastTick;
    const double SPEEDMULTIPLIER = 5;
};