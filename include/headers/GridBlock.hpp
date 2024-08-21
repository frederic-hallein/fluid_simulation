#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include <iostream>

class GridBlock { 
public:
    GridBlock(SDL_Renderer* renderer, int dx, float dt, float x_pos, float y_pos);
    ~GridBlock();

    float get_x_pos();
    float get_y_pos();

    void set_grid_velocity();

    void set_f0(float f0); void set_f0_eq(float c_s);
    void set_f1(float f1); void set_f1_eq(float c_s);
    void set_f2(float f2); void set_f2_eq(float c_s);
    void set_f3(float f3); void set_f3_eq(float c_s);
    void set_f4(float f4); void set_f4_eq(float c_s);
    void set_f5(float f5); void set_f5_eq(float c_s);
    void set_f6(float f6); void set_f6_eq(float c_s);
    void set_f7(float f7); void set_f7_eq(float c_s);
    void set_f8(float f8); void set_f8_eq(float c_s);

    float get_f0(); float get_f0_eq();
    float get_f1(); float get_f1_eq();
    float get_f2(); float get_f2_eq();
    float get_f3(); float get_f3_eq();
    float get_f4(); float get_f4_eq();
    float get_f5(); float get_f5_eq();
    float get_f6(); float get_f6_eq();
    float get_f7(); float get_f7_eq();
    float get_f8(); float get_f8_eq();

    void set_rho(std::vector<float> f);
    float get_rho();

    void set_u(std::vector<float> f);
    std::vector<float> get_u();
    std::vector<float> get_u_normalized();

    std::vector<float> get_c0();
    std::vector<float> get_c1();
    std::vector<float> get_c2();
    std::vector<float> get_c3();
    std::vector<float> get_c4();
    std::vector<float> get_c5();
    std::vector<float> get_c6();
    std::vector<float> get_c7();
    std::vector<float> get_c8();

    void set_boundary();
    bool is_boundary();

    void draw();
    

private:
    SDL_Renderer* renderer = nullptr;
    SDL_Rect rect;

    int dx; float dt;
    float x_pos, y_pos;

    float m = 1.0;
    std::vector<float> w = { 0.444, 0.111 , 0.111, 0.111, 0.111, 0.028, 0.028, 0.028, 0.028 };

    float f0, f1, f2, f3, f4, f5, f6, f7, f8;
    float f0_eq, f1_eq, f2_eq, f3_eq, f4_eq, f5_eq, f6_eq, f7_eq, f8_eq;
     

    float rho;
    std::vector<float> u = { 0, 0 };


    std::vector<float> c0 = { 0, 0 };
    std::vector<float> c1 = { 1, 0 };
    std::vector<float> c2 = { 0, 1 };
    std::vector<float> c3 = {-1, 0 };
    std::vector<float> c4 = { 0,-1 };
    std::vector<float> c5 = { 1, 1 };
    std::vector<float> c6 = {-1, 1 };
    std::vector<float> c7 = {-1,-1 };
    std::vector<float> c8 = { 1,-1 };

    bool is_wall = false;

};