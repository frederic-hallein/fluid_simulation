#pragma once

#include <SDL2/SDL.h>

class GridBlock { 
public:
    GridBlock(SDL_Renderer* renderer, int grid_size, int x_pos, int y_pos);
    ~GridBlock();

    int get_x_pos();
    int get_y_pos();

    void set_velocity(double v_bottom, double v_top, double u_left, double v_right);
    void set_wall();
    
    double get_v_bottom();
    double get_v_top();
    double get_u_left();
    double get_u_right();

    double get_s_bottom();
    double get_s_top();
    double get_s_left();
    double get_s_right();

    void draw();
    

private:
    SDL_Renderer* renderer = nullptr;
    SDL_Rect rect;

    int grid_size;
    int x_pos;
    int y_pos;

    double v_bottom = 0.0;
    double v_top = 0.0;
    double u_left = 0.0;
    double u_right = 0.0;

    double s_bottom = 1;
    double s_top = 1;
    double s_left = 1;
    double s_right = 1;

};