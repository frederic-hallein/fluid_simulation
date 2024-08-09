#include "GridBlock.hpp"

GridBlock::GridBlock(SDL_Renderer* renderer, int grid_size, int x_pos, int y_pos) 
{
    this->renderer = renderer;
    this->grid_size = grid_size;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

GridBlock::~GridBlock() {}

int GridBlock::get_x_pos() {return x_pos;}

int GridBlock::get_y_pos() {return y_pos;}

void GridBlock::set_velocity(double v_bottom, double v_top, double u_left, double v_right)
{
    this->v_bottom = v_bottom;
    this->v_top = v_top;
    this->u_left = u_left;
    this->u_right = u_right;
}

void GridBlock::set_wall() {}

double GridBlock::get_v_bottom() {return v_bottom;}

double GridBlock::get_v_top() {return v_top;}

double GridBlock::get_u_left() {return u_left;}

double GridBlock::get_u_right() {return u_right;}

double GridBlock::get_s_bottom() {return s_bottom;}

double GridBlock::get_s_top() {return s_top;}

double GridBlock::get_s_left() {return s_left;}

double GridBlock::get_s_right() {return s_right;}

void GridBlock::draw()
{
    rect.x = x_pos * grid_size;
    rect.y = y_pos * grid_size;
    rect.w = grid_size;
    rect.h = grid_size;
    SDL_RenderFillRect(renderer, &rect);
}