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

void GridBlock::draw()
{
    rect.x = x_pos * grid_size;
    rect.y = y_pos * grid_size;
    rect.w = grid_size;
    rect.h = grid_size;
    SDL_RenderFillRect(renderer, &rect);
}