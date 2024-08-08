#pragma once

#include <SDL2/SDL.h>

class GridBlock { 
public:
    GridBlock(SDL_Renderer* renderer, int grid_size, int x_pos, int y_pos);
    ~GridBlock();

    int get_x_pos();
    int get_y_pos();

    void draw();
    

private:
    SDL_Renderer* renderer = nullptr;
    SDL_Rect rect;

    int grid_size;
    int x_pos;
    int y_pos;

    double v;
    double u;

};