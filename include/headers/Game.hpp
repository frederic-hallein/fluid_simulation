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
    int grid_width;
    int grid_height;


    int dx = 5; 
    float dt = 0.001;

    float tau = 1.0;
    float c_s;
    float nu;
    

    bool is_running = true;   
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    std::vector<std::vector<GridBlock>> grid_blocks;
    std::vector<std::vector<GridBlock>> grid_blocks_tmp;


};
