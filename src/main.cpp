#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Clock.hpp"

#include "Galaxy.hpp"
#include "Planet.hpp"

using namespace std;

const int SCREENWIDTH = 800, SCREENHEIGHT = 800;
const int REFRESHRATE = 60;

const int MAX_MASS = 100000;
const int MIN_MASS = 10000;
const int NUM_PLANETS = 3;
const int MAX_VELOCITY = 1;

int mainloop(RenderWindow& window);

int main(int argc, char* args[]) {

    // initialize sdl video
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        cout << "SDL INIT FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        cout << "SDL IMAGE INIT FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
    }
    
    RenderWindow window("Galaxy Simulator", SCREENWIDTH, SCREENHEIGHT);

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

    Galaxy galaxy;

    for (int i = 0; i < NUM_PLANETS; i++) {
        Planet newPlanet(rand() % 700 + 50, rand() % 700 + 50, rand() % (MAX_MASS-MIN_MASS+1) + MIN_MASS, {rand() % 256, rand() % 256, rand() % 256});
        newPlanet.setVelocity({double(rand() % (MAX_VELOCITY * 2 + 1) - MAX_VELOCITY), double(rand() % 21 - 10)});
        galaxy.addPlanet(newPlanet);
    }

    while (mainloopRunning) {
        clock.tick();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        window.clear();

        galaxy.tick(window);

        window.display();
    }
}