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

    int grid_width;
    int grid_height;

    float f0; float f0_eq; float f0_tmp;
    float f1; float f1_eq; float f1_tmp;
    float f2; float f2_eq; float f2_tmp;
    float f3; float f3_eq; float f3_tmp;
    float f4; float f4_eq; float f4_tmp;
    float f5; float f5_eq; float f5_tmp;
    float f6; float f6_eq; float f6_tmp;
    float f7; float f7_eq; float f7_tmp;
    float f8; float f8_eq; float f8_tmp;

    std::vector<float> c0; bool wall_0;
    std::vector<float> c1; bool wall_1;
    std::vector<float> c2; bool wall_2;
    std::vector<float> c3; bool wall_3;
    std::vector<float> c4; bool wall_4;
    std::vector<float> c5; bool wall_5;
    std::vector<float> c6; bool wall_6;
    std::vector<float> c7; bool wall_7;
    std::vector<float> c8; bool wall_8;

private:


    int dx = 2; 
    float dt = 1;

    float tau = 150;
    float c_s;
    float nu;
    

    bool is_running = true;   
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Event event;

    std::vector<std::vector<GridBlock>> grid_blocks;
    std::vector<std::vector<GridBlock>> grid_blocks_tmp;

    Uint32* pixels; 

};
