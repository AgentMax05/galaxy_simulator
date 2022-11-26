#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "Entity.hpp"
#include "Planet.hpp"

using namespace std;

class RenderWindow {
public:
    RenderWindow(const char* winTitle, int winWidth, int winHeight);
    SDL_Texture* loadTexture(const char* filePath);
    void cleanUp();
    void clear();
    void display();
    void render(Entity& entity);
    void render(Planet& planet);

    void drawLine(vector<double> p1, vector<double> p2, vector<int> color);
    
    void drawCircle(vector<double> center, int radius, vector<int> color);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};