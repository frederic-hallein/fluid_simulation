#pragma once

#include <SDL2/SDL.h>

class GridBlock { 
public:
    GridBlock(SDL_Renderer* renderer, int grid_size, double x_pos, double y_pos);
    ~GridBlock();

    double get_x_pos();
    double get_y_pos();

    void set_v(double v);
    void set_u(double u);
    double get_v();
    double get_u();

    void set_boundary();
    int get_s();

    void set_p(double p);
    double get_p();

    void set_rho(double rho);
    double get_rho();

    void draw();
    

private:
    SDL_Renderer* renderer = nullptr;
    SDL_Rect rect;

    int grid_size;
    double x_pos;
    double y_pos;

    double v = 0.0;
    double u = 0.0;
    int s = 1;

    double p = 0.0;
    double rho = 0.0;

};