#include "GridBlock.hpp"

GridBlock::GridBlock(SDL_Renderer* renderer, int grid_size, double x_pos, double y_pos) 
{
    this->renderer = renderer;
    this->grid_size = grid_size;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

GridBlock::~GridBlock() {}

double GridBlock::get_x_pos() {return x_pos;}

double GridBlock::get_y_pos() {return y_pos;}

void GridBlock::set_v(double v) {this->v = v;}

void GridBlock::set_u(double u) {this->u = u;}

double GridBlock::get_v() {return v;}

double GridBlock::get_u() {return u;}

void GridBlock::set_boundary() {this->s = 0;}

int GridBlock::get_s() {return s;}

void GridBlock::set_p(double p) {this->p=p;}

double GridBlock::get_p() {return p;}

void GridBlock::set_rho(double rho) {this->rho=rho;}

double GridBlock::get_rho() {return rho;}

void GridBlock::draw()
{
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = grid_size;
    rect.h = grid_size;
    SDL_RenderFillRect(renderer, &rect);
}