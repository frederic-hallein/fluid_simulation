#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "GridBlock.hpp"


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
    int w;
    int h;

    bool is_running = true;   
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    int grid_size = 10;
    std::vector<std::vector<GridBlock>> grid_blocks;


};
