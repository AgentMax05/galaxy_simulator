#include "RenderWindow.hpp"

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

RenderWindow::RenderWindow(const char* winTitle, int winWidth, int winHeight) {
    window = NULL;
    renderer = NULL;

    window = SDL_CreateWindow(winTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << "\n";
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL) {
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << "\n";
    }
    return texture;
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

void RenderWindow::render(Entity& entity) {
    SDL_Rect dest;
    dest.x = entity.getX();
    dest.y = entity.getY();
    dest.w = entity.getW();
    dest.h = entity.getH();

    SDL_Rect src = entity.getCurrentFrame();

    SDL_RenderCopyEx(renderer, entity.getTexture(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::render(Planet& planet) {
    drawCircle({planet.x, planet.y}, planet.radius, planet.color);
}

void RenderWindow::drawCircle(vector<double> center, int radius, vector<int> color) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);

    for (int width = 0; width < radius * 2; width++) {
        for (int height = 0; height < radius * 2; height++) {
            if (pow(radius - width, 2) + pow(radius - height, 2) < pow(radius, 2))
            SDL_RenderDrawPoint(renderer, center[0] + radius - width, center[1] + radius - height);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}