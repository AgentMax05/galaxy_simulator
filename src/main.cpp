#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Clock.hpp"

#include "Planet.hpp"

using namespace std;

const int SCREENWIDTH = 800, SCREENHEIGHT = 800;
const int REFRESHRATE = 60;

const int MAX_MASS = 10;
const int MIN_MASS = 10;
const int NUM_PLANETS = 100;

int mainloop(RenderWindow& window);

int main(int argc, char* args[]) {

    // initialize sdl video
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        cout << "SDL INIT FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        cout << "SDL IMAGE INIT FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
    }
    
    RenderWindow window("Game Window", SCREENWIDTH, SCREENHEIGHT);

    mainloop(window);

    window.cleanUp();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

int mainloop(RenderWindow& window) {
    bool mainloopRunning = true;
    SDL_Event event;
    Clock clock(REFRESHRATE);

    srand((unsigned) time(NULL));

    vector<Planet> planets = {};

    for (int i = 0; i < NUM_PLANETS; i++) {
        Planet newPlanet(rand() % 700 + 50, rand() % 700 + 50, rand() % (MAX_MASS-MIN_MASS+1) + MIN_MASS, {rand() % 256, rand() % 256, rand() % 256});
        newPlanet.setVelocity({double(rand() % 21 - 10), double(rand() % 21 - 10)});
        planets.push_back(newPlanet);
    }

    while (mainloopRunning) {
        clock.tick();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        window.clear();

        for (int i = 0; i < planets.size(); i++) {
            for (int j = 0; j < planets.size(); j++) {
                if (i == j) {
                    continue;
                }
                planets[i].addForce(planets[j]);
            }
        }

        for (int i = 0; i < planets.size(); i++) {
            planets[i].tick();
            window.render(planets[i]);
        }

        window.display();
    }
}