#pragma once

#include <SDL2/SDL.h>
#include "Grid.hpp"


class Game {  
public:
    Game();
    ~Game();

    void init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

private:
    bool is_running = true;   
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    Grid grid;

};
