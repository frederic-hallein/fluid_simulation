#include "GridBlock.hpp"

GridBlock::GridBlock(SDL_Renderer* renderer, int dx, float dt, float x_pos, float y_pos) 
{
    this->renderer = renderer;
    this->dx = dx;
    this->dt = dt;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
  
}

GridBlock::~GridBlock() {}

float GridBlock::get_x_pos() {return x_pos;}
float GridBlock::get_y_pos() {return y_pos;}

void GridBlock::set_grid_velocity()
{
    if (!is_wall)
    {
        this->c0[0] *= (dx / dt); this->c0[1] *= (dx / dt);
        this->c1[0] *= (dx / dt); this->c1[1] *= (dx / dt);
        this->c2[0] *= (dx / dt); this->c2[1] *= (dx / dt);
        this->c3[0] *= (dx / dt); this->c3[1] *= (dx / dt);
        this->c4[0] *= (dx / dt); this->c4[1] *= (dx / dt);
        this->c5[0] *= (dx / dt); this->c5[1] *= (dx / dt);
        this->c6[0] *= (dx / dt); this->c6[1] *= (dx / dt);
        this->c7[0] *= (dx / dt); this->c7[1] *= (dx / dt);
        this->c8[0] *= (dx / dt); this->c8[1] *= (dx / dt);
    } 
    else
    {
        this->c0[0] = 0.0; this->c0[1] = 0.0;
        this->c1[0] = 0.0; this->c1[1] = 0.0;
        this->c2[0] = 0.0; this->c2[1] = 0.0;
        this->c3[0] = 0.0; this->c3[1] = 0.0;
        this->c4[0] = 0.0; this->c4[1] = 0.0;
        this->c5[0] = 0.0; this->c5[1] = 0.0;
        this->c6[0] = 0.0; this->c6[1] = 0.0;
        this->c7[0] = 0.0; this->c7[1] = 0.0;
        this->c8[0] = 0.0; this->c8[1] = 0.0;      
    }
}


void GridBlock::set_f0(float f0) {this->f0 = f0;}
void GridBlock::set_f1(float f1) {this->f1 = f1;}
void GridBlock::set_f2(float f2) {this->f2 = f2;}
void GridBlock::set_f3(float f3) {this->f3 = f3;}
void GridBlock::set_f4(float f4) {this->f4 = f4;}
void GridBlock::set_f5(float f5) {this->f5 = f5;}
void GridBlock::set_f6(float f6) {this->f6 = f6;}
void GridBlock::set_f7(float f7) {this->f7 = f7;}
void GridBlock::set_f8(float f8) {this->f8 = f8;}

void GridBlock::set_f0_eq(float c_s) 
{    
    float f0_eq = w[0] * rho * (1 + 3 * (c0[0] * u[0] + c0[1] * u[1]) / (c_s * c_s) 
                  + 9 *((c0[0] * u[0] + c0[1] * u[1]) * (c0[0] * u[0] + c0[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f0_eq = f0_eq;
}
void GridBlock::set_f1_eq(float c_s) 
{
    float f1_eq = w[1] * rho * (1 + 3 * (c1[0] * u[0] + c1[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c1[0] * u[0] + c1[1] * u[1]) * (c1[0] * u[0] + c1[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f1_eq = f1_eq;
}

void GridBlock::set_f2_eq(float c_s) 
{
    float f2_eq = w[2] * rho * (1 + 3 * (c2[0] * u[0] + c2[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c2[0] * u[0] + c2[1] * u[1]) * (c2[0] * u[0] + c2[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - 3 * (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f2_eq = f2_eq;
}
void GridBlock::set_f3_eq(float c_s) 
{
    float f3_eq = w[3] * rho * (1 + 3 * (c3[0] * u[0] + c3[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c3[0] * u[0] + c3[1] * u[1]) * (c3[0] * u[0] + c3[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - 3 * (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f3_eq = f3_eq;
}

void GridBlock::set_f4_eq(float c_s) 
{
    float f4_eq = w[4] * rho * (1 + 3 * (c4[0] * u[0] + c4[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c4[0] * u[0] + c4[1] * u[1]) * (c4[0] * u[0] + c4[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - 3 * (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f4_eq = f4_eq;
}

void GridBlock::set_f5_eq(float c_s) 
{
    float f5_eq = w[5] * rho * (1 + 3 * (c5[0] * u[0] + c5[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c5[0] * u[0] + c5[1] * u[1]) * (c5[0] * u[0] + c5[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - 3 * (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f5_eq = f5_eq;
}

void GridBlock::set_f6_eq(float c_s) 
{
    float f6_eq = w[6] * rho * (1 + 3 * (c6[0] * u[0] + c6[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c6[0] * u[0] + c6[1] * u[1]) * (c6[0] * u[0] + c6[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - 3 * (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f6_eq = f6_eq;
}

void GridBlock::set_f7_eq(float c_s) 
{
    float f7_eq = w[7] * rho * (1 + 3 * (c7[0] * u[0] + c7[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c7[0] * u[0] + c7[1] * u[1]) * (c7[0] * u[0] + c7[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - 3 * (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f7_eq = f7_eq;
}

void GridBlock::set_f8_eq(float c_s) 
{
    float f8_eq = w[8] * rho * (1 + 3 * (c8[0] * u[0] + c8[1] * u[1]) / (c_s * c_s) 
                  + 9 * ((c8[0] * u[0] + c8[1] * u[1]) * (c8[0] * u[0] + c8[1] * u[1])) / (2 * c_s * c_s * c_s * c_s) 
                  - 3 * (u[0] * u[0] + u[1] * u[1]) / (2 * c_s * c_s));
    this->f8_eq = f8_eq;
}

float GridBlock::get_f0() {return f0;}
float GridBlock::get_f1() {return f1;}
float GridBlock::get_f2() {return f2;}
float GridBlock::get_f3() {return f3;}
float GridBlock::get_f4() {return f4;}
float GridBlock::get_f5() {return f5;}
float GridBlock::get_f6() {return f6;}
float GridBlock::get_f7() {return f7;}
float GridBlock::get_f8() {return f8;}

float GridBlock::get_f0_eq() {return f0_eq;}
float GridBlock::get_f1_eq() {return f1_eq;}
float GridBlock::get_f2_eq() {return f2_eq;}
float GridBlock::get_f3_eq() {return f3_eq;}
float GridBlock::get_f4_eq() {return f4_eq;}
float GridBlock::get_f5_eq() {return f5_eq;}
float GridBlock::get_f6_eq() {return f6_eq;}
float GridBlock::get_f7_eq() {return f7_eq;}
float GridBlock::get_f8_eq() {return f8_eq;}

void GridBlock::set_rho(std::vector<float> f) {this->rho = m * (f[0] + f[1] + f[2] + f[3] + f[4] + f[5] + f[6] + f[7] + f[8]);}
float GridBlock::get_rho() {return rho;}

void GridBlock::set_u(std::vector<float> f)
{
    std::vector<float> c0f0 = { c0[0] * f[0], c0[1] * f[0]};
    std::vector<float> c1f1 = { c1[0] * f[1], c1[1] * f[1]};
    std::vector<float> c2f2 = { c2[0] * f[2], c2[1] * f[2]};
    std::vector<float> c3f3 = { c3[0] * f[3], c3[1] * f[3]};
    std::vector<float> c4f4 = { c4[0] * f[4], c4[1] * f[4]};
    std::vector<float> c5f5 = { c5[0] * f[5], c5[1] * f[5]};
    std::vector<float> c6f6 = { c6[0] * f[6], c6[1] * f[6]};
    std::vector<float> c7f7 = { c7[0] * f[7], c7[1] * f[7]};
    std::vector<float> c8f8 = { c8[0] * f[8], c8[1] * f[8]};

    if (rho > 0.0)
    {
        float u_x = (m / rho) * (c0f0[0] + c1f1[0] + c2f2[0] + c3f3[0] + c4f4[0] + c5f5[0] + c6f6[0] + c7f7[0] + c8f8[0]);
        float u_y = (m / rho) * (c0f0[1] + c1f1[1] + c2f2[1] + c3f3[1] + c4f4[1] + c5f5[1] + c6f6[1] + c7f7[1] + c8f8[1]);

        this->u[0] = u_x;
        this->u[1] = u_y;
    }
    else
    {
        this->u[0] = 0.0;
        this->u[1] = 0.0;
    }

}

std::vector<float> GridBlock::get_u() {return u;}

std::vector<float> GridBlock::get_u_normalized() 
{
    float norm = std::sqrt(u[0]*u[0] + u[1]*u[1]);
    std::vector<float> u_norm = { u[0], u[1] };
    if (norm <= 0.0)
    {
        return u_norm;
    }
    else
    {
        u_norm[0] /= norm;
        u_norm[1] /= norm;
        return u_norm;
    }
}

std::vector<float> GridBlock::get_c0() {return c0;}
std::vector<float> GridBlock::get_c1() {return c1;}
std::vector<float> GridBlock::get_c2() {return c2;}
std::vector<float> GridBlock::get_c3() {return c3;}
std::vector<float> GridBlock::get_c4() {return c4;}
std::vector<float> GridBlock::get_c5() {return c5;}
std::vector<float> GridBlock::get_c6() {return c6;}
std::vector<float> GridBlock::get_c7() {return c7;}
std::vector<float> GridBlock::get_c8() {return c8;}

void GridBlock::set_boundary() {this->is_wall = true;}
bool GridBlock::is_boundary() {return is_wall;}

void GridBlock::draw()
{
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = dx;
    rect.h = dx;
    SDL_RenderFillRect(renderer, &rect);
}