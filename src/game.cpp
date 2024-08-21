#include <iostream>
#include <format>
#include <cmath>


#include "Game.hpp"



Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen)
{
    // initialize window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_Init has failed." << '\n';
        std::cout << "Error: " << SDL_GetError() << '\n'; 
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Could not create window." << '\n';
        std::cout << "Error: " << SDL_GetError() << '\n';
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Could not create renderer." << '\n';
        std::cout << "Error: " << SDL_GetError() << '\n';
    }

    // keep hold of SCREEN_WIDTH and SCREEN_HEIGHT
    this->grid_width = SCREEN_WIDTH / dx;
    this->grid_height = SCREEN_HEIGHT / dx;


    // set viscosity and speed of sound
    this->c_s = 0.57735026919 * (dx / dt);
    this->nu = c_s * c_s * (tau - dt / 2);

    std::cout << "c_s = " << c_s << ", nu = " << nu << '\n';
 


    // initialize grid blocks
    for (int i = 0; i <= grid_width; i++) {    
        for (int j = 0; j <= grid_height; j++) {

            GridBlock grid_block(renderer, dx, dt, i * dx, j * dx);
            grid_blocks.push_back(std::vector<GridBlock>());
            grid_blocks[i].push_back(grid_block);

            GridBlock grid_block_tmp(renderer, dx, dt, i * dx, j * dx);
            grid_blocks_tmp.push_back(std::vector<GridBlock>());
            grid_blocks_tmp[i].push_back(grid_block_tmp);
            
            // set window border 
            if (i == 0 || j == 0 || i == grid_width - 1 || j == grid_height - 1) {
                grid_blocks[i][j].set_boundary();
                grid_blocks_tmp[i][j].set_boundary();
            } 

            // draw disk
            //if ((i - grid_width / 4) * (i - grid_width / 4) + (j - grid_height / 2) * (j - grid_height / 2) < 90) {
            //    grid_blocks[i][j].set_boundary();
            //    grid_blocks_tmp[i][j].set_boundary();
            //} 

            // draw rectangle
            if (i < grid_width / 4 + 5 && i > grid_width / 4 - 5 && j < grid_height / 2 - 1) {
                grid_blocks[i][j].set_boundary();
                grid_blocks_tmp[i][j].set_boundary();
            } 

            if (i < grid_width / 4 + 5 && i > grid_width / 4 - 5 && j > grid_height / 2 + 1) {
                grid_blocks[i][j].set_boundary();
                grid_blocks_tmp[i][j].set_boundary();
            } 
            if (i < grid_width / 2 + 5 && i > grid_width / 2 - 5 && j > grid_height / 2 + 5) {
                grid_blocks[i][j].set_boundary();
                grid_blocks_tmp[i][j].set_boundary();
            } 
            if (i < grid_width * 0.75 + 5 && i > grid_width * 0.75 - 5 && j < grid_height / 2 + 5) {
                grid_blocks[i][j].set_boundary();
                grid_blocks_tmp[i][j].set_boundary();
            } 

            
        }
    }   

    // initialize fi's
    for (int i = 0; i <= grid_width; i++) {    
        for (int j = 0; j <= grid_height; j++) {

            std::vector<float>  f;
            bool is_wall = grid_blocks[i][j].is_boundary();
            
            //if (!is_wall) {f = { 0,1,1,1,1,1,1,1,1 };}
            //else {f = { 0,0,0,0,0,0,0,0,0 };}

            if (i == 1) {f = {  0,1,0,0,0,0,0,0,0  };}
            else {f = { 0,0,0,0,0,0,0,0,0 };}

            grid_blocks[i][j].set_grid_velocity();

            grid_blocks[i][j].set_f0(f[0]);
            grid_blocks[i][j].set_f1(f[1]);
            grid_blocks[i][j].set_f2(f[2]);
            grid_blocks[i][j].set_f3(f[3]);
            grid_blocks[i][j].set_f4(f[4]);
            grid_blocks[i][j].set_f5(f[5]);
            grid_blocks[i][j].set_f6(f[6]);
            grid_blocks[i][j].set_f7(f[7]);
            grid_blocks[i][j].set_f8(f[8]);

            
        }
    }  


    
    //int x = 1; int y = 1;
    //std::cout << "f0  = " << grid_blocks[x][y].get_f0() << ", f0_eq = " << grid_blocks[x][y].get_f0_eq()  << '\n'; 
    //std::cout << "f1  = " << grid_blocks[x][y].get_f1() << ", f1_eq = " << grid_blocks[x][y].get_f1_eq()  <<'\n';
    //std::cout << "f2  = " << grid_blocks[x][y].get_f2() << ", f2_eq = " << grid_blocks[x][y].get_f2_eq()  <<'\n';
    //std::cout << "f3  = " << grid_blocks[x][y].get_f3() << ", f3_eq = " << grid_blocks[x][y].get_f3_eq()  <<'\n';
    //std::cout << "f4  = " << grid_blocks[x][y].get_f4() << ", f4_eq = " << grid_blocks[x][y].get_f4_eq()  <<'\n';
    //std::cout << "f5  = " << grid_blocks[x][y].get_f5() << ", f5_eq = " << grid_blocks[x][y].get_f5_eq()  <<'\n';
    //std::cout << "f6  = " << grid_blocks[x][y].get_f6() << ", f6_eq = " << grid_blocks[x][y].get_f6_eq()  <<'\n';
    //std::cout << "f7  = " << grid_blocks[x][y].get_f7() << ", f7_eq = " << grid_blocks[x][y].get_f7_eq()  <<'\n';
    //std::cout << "f8  = " << grid_blocks[x][y].get_f8() << ", f8_eq = " << grid_blocks[x][y].get_f8_eq()  <<'\n';
    //
    //std::cout << "rho = " << grid_blocks[x][y].get_rho()  << ", u = (" << grid_blocks[x][y].get_u()[0] << ", " << grid_blocks[x][y].get_u()[1] << ")" <<'\n';
    

}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            is_running = false;   
            break;

        default:
            break;
    }
}

void Game::update()
{
    float f0; float f0_eq; float f0_tmp;
    float f1; float f1_eq; float f1_tmp;
    float f2; float f2_eq; float f2_tmp;
    float f3; float f3_eq; float f3_tmp;
    float f4; float f4_eq; float f4_tmp;
    float f5; float f5_eq; float f5_tmp;
    float f6; float f6_eq; float f6_tmp;
    float f7; float f7_eq; float f7_tmp;
    float f8; float f8_eq; float f8_tmp;

    for (int i = 1; i <= grid_width - 2; i++) {    
        for (int j = 1; j <= grid_height - 2; j++) {

            f0 = grid_blocks[i][j].get_f0(); 
            f1 = grid_blocks[i][j].get_f1(); 
            f2 = grid_blocks[i][j].get_f2(); 
            f3 = grid_blocks[i][j].get_f3(); 
            f4 = grid_blocks[i][j].get_f4(); 
            f5 = grid_blocks[i][j].get_f5(); 
            f6 = grid_blocks[i][j].get_f6(); 
            f7 = grid_blocks[i][j].get_f7(); 
            f8 = grid_blocks[i][j].get_f8(); 

            std::vector<float> f = { f0, f1, f2, f3, f4, f5, f6, f7, f8 };
            grid_blocks[i][j].set_rho(f);
            grid_blocks[i][j].set_u(f);

            grid_blocks[i][j].set_f0_eq(c_s);
            grid_blocks[i][j].set_f1_eq(c_s);
            grid_blocks[i][j].set_f2_eq(c_s);
            grid_blocks[i][j].set_f3_eq(c_s);
            grid_blocks[i][j].set_f4_eq(c_s);
            grid_blocks[i][j].set_f5_eq(c_s);
            grid_blocks[i][j].set_f6_eq(c_s);
            grid_blocks[i][j].set_f7_eq(c_s);
            grid_blocks[i][j].set_f8_eq(c_s);

            f0_eq = grid_blocks[i][j].get_f0_eq();
            f1_eq = grid_blocks[i][j].get_f1_eq();
            f2_eq = grid_blocks[i][j].get_f2_eq();
            f3_eq = grid_blocks[i][j].get_f3_eq();
            f4_eq = grid_blocks[i][j].get_f4_eq();
            f5_eq = grid_blocks[i][j].get_f5_eq();
            f6_eq = grid_blocks[i][j].get_f6_eq();
            f7_eq = grid_blocks[i][j].get_f7_eq();
            f8_eq = grid_blocks[i][j].get_f8_eq();

            // collision step 
            f0_tmp = f0 - (dt / tau) * (f0 - f0_eq);
            f1_tmp = f1 - (dt / tau) * (f1 - f1_eq);
            f2_tmp = f2 - (dt / tau) * (f2 - f2_eq);
            f3_tmp = f3 - (dt / tau) * (f3 - f3_eq);
            f4_tmp = f4 - (dt / tau) * (f4 - f4_eq);
            f5_tmp = f5 - (dt / tau) * (f5 - f5_eq);
            f6_tmp = f6 - (dt / tau) * (f6 - f6_eq);
            f7_tmp = f7 - (dt / tau) * (f7 - f7_eq);
            f8_tmp = f8 - (dt / tau) * (f8 - f8_eq);

            grid_blocks_tmp[i][j].set_f0(f0_tmp);
            grid_blocks_tmp[i][j].set_f1(f1_tmp);
            grid_blocks_tmp[i][j].set_f2(f2_tmp);
            grid_blocks_tmp[i][j].set_f3(f3_tmp);
            grid_blocks_tmp[i][j].set_f4(f4_tmp);
            grid_blocks_tmp[i][j].set_f5(f5_tmp);
            grid_blocks_tmp[i][j].set_f6(f6_tmp);
            grid_blocks_tmp[i][j].set_f7(f7_tmp);
            grid_blocks_tmp[i][j].set_f8(f8_tmp);
            
        }
    }

    std::vector<float> c0; bool wall_0;
    std::vector<float> c1; bool wall_1;
    std::vector<float> c2; bool wall_2;
    std::vector<float> c3; bool wall_3;
    std::vector<float> c4; bool wall_4;
    std::vector<float> c5; bool wall_5;
    std::vector<float> c6; bool wall_6;
    std::vector<float> c7; bool wall_7;
    std::vector<float> c8; bool wall_8;

    for (int i = 1; i <= grid_width - 2; i++) {    
        for (int j = 1; j <= grid_height - 2; j++) {
            
            c0 = grid_blocks[i][j].get_c0();
            c1 = grid_blocks[i][j].get_c1();
            c2 = grid_blocks[i][j].get_c2();
            c3 = grid_blocks[i][j].get_c3();
            c4 = grid_blocks[i][j].get_c4();
            c5 = grid_blocks[i][j].get_c5();
            c6 = grid_blocks[i][j].get_c6();
            c7 = grid_blocks[i][j].get_c7();
            c8 = grid_blocks[i][j].get_c8();
            
            f0_tmp = grid_blocks_tmp[i][j].get_f0();
            f1_tmp = grid_blocks_tmp[i][j].get_f1();
            f2_tmp = grid_blocks_tmp[i][j].get_f2();
            f3_tmp = grid_blocks_tmp[i][j].get_f3();
            f4_tmp = grid_blocks_tmp[i][j].get_f4();
            f5_tmp = grid_blocks_tmp[i][j].get_f5();
            f6_tmp = grid_blocks_tmp[i][j].get_f6();
            f7_tmp = grid_blocks_tmp[i][j].get_f7();
            f8_tmp = grid_blocks_tmp[i][j].get_f8();
            
            wall_0 = grid_blocks[(int)(i + c0[0] * dt / dx)][(int)(j + c0[1] * dt / dx)].is_boundary();
            wall_1 = grid_blocks[(int)(i + c1[0] * dt / dx)][(int)(j + c1[1] * dt / dx)].is_boundary();
            wall_2 = grid_blocks[(int)(i + c2[0] * dt / dx)][(int)(j + c2[1] * dt / dx)].is_boundary();
            wall_3 = grid_blocks[(int)(i + c3[0] * dt / dx)][(int)(j + c3[1] * dt / dx)].is_boundary();
            wall_4 = grid_blocks[(int)(i + c4[0] * dt / dx)][(int)(j + c4[1] * dt / dx)].is_boundary();
            wall_5 = grid_blocks[(int)(i + c5[0] * dt / dx)][(int)(j + c5[1] * dt / dx)].is_boundary();
            wall_6 = grid_blocks[(int)(i + c6[0] * dt / dx)][(int)(j + c6[1] * dt / dx)].is_boundary();
            wall_7 = grid_blocks[(int)(i + c7[0] * dt / dx)][(int)(j + c7[1] * dt / dx)].is_boundary();
            wall_8 = grid_blocks[(int)(i + c8[0] * dt / dx)][(int)(j + c8[1] * dt / dx)].is_boundary();
            
            // propagation step
            if (!wall_0) {grid_blocks[(int)(i + c0[0] * dt / dx)][(int)(j + c0[1] * dt / dx)].set_f0(f0_tmp);}
            else {grid_blocks[i][j].set_f0(f0_tmp);}  

            
            if (!wall_1) {grid_blocks[(int)(i + c1[0] * dt / dx)][(int)(j + c1[1] * dt / dx)].set_f1(f1_tmp);}
            else {grid_blocks[i][j].set_f1(f3_tmp);}       
            
            if (!wall_2) {grid_blocks[(int)(i + c2[0] * dt / dx)][(int)(j + c2[1] * dt / dx)].set_f2(f2_tmp);}
            else {grid_blocks[i][j].set_f2(f4_tmp);}  

            if (!wall_3) {grid_blocks[(int)(i + c3[0] * dt / dx)][(int)(j + c3[1] * dt / dx)].set_f3(f3_tmp);}
            else {grid_blocks[i][j].set_f3(f1_tmp);}  

            if (!wall_4) {grid_blocks[(int)(i + c4[0] * dt / dx)][(int)(j + c4[1] * dt / dx)].set_f4(f4_tmp);}
            else {grid_blocks[i][j].set_f4(f2_tmp);}  

            if (!wall_5) {grid_blocks[(int)(i + c5[0] * dt / dx)][(int)(j + c5[1] * dt / dx)].set_f5(f5_tmp);}
            else {grid_blocks[i][j].set_f5(f7_tmp);}  

            if (!wall_6) {grid_blocks[(int)(i + c6[0] * dt / dx)][(int)(j + c6[1] * dt / dx)].set_f6(f6_tmp);}
            else {grid_blocks[i][j].set_f6(f8_tmp);}  

            if (!wall_7) {grid_blocks[(int)(i + c7[0] * dt / dx)][(int)(j + c7[1] * dt / dx)].set_f7(f7_tmp);}
            else {grid_blocks[i][j].set_f7(f5_tmp);}  

            if (!wall_8) {grid_blocks[(int)(i + c8[0] * dt / dx)][(int)(j + c8[1] * dt / dx)].set_f8(f8_tmp);}
            else {grid_blocks[i][j].set_f8(f6_tmp);}  
            
            
            // FIXME : periodic boundary conditions 
            /*
            if (!wall_1) {grid_blocks[(int)(i + c1[0] * dt / dx)][(int)(j + c1[1] * dt / dx)].set_f1(f1_tmp);}
            else {grid_blocks[1][j].set_f1(f1_tmp);}      
            
            if (!wall_2) {grid_blocks[(int)(i + c2[0] * dt / dx)][(int)(j + c2[1] * dt / dx)].set_f2(f2_tmp);}
            else {grid_blocks[i][grid_height-2].set_f2(f2_tmp);}  

            if (!wall_3) {grid_blocks[(int)(i + c3[0] * dt / dx)][(int)(j + c3[1] * dt / dx)].set_f3(f3_tmp);}
            else {grid_blocks[grid_width-2][j].set_f3(f3_tmp);}  

            if (!wall_4) {grid_blocks[(int)(i + c4[0] * dt / dx)][(int)(j + c4[1] * dt / dx)].set_f4(f4_tmp);}
            else {grid_blocks[i][1].set_f4(f4_tmp);}  

            if (!wall_5) {grid_blocks[(int)(i + c5[0] * dt / dx)][(int)(j + c5[1] * dt / dx)].set_f5(f5_tmp);}
            else 
            {
                if (wall_5 && wall_6)
                {
                    grid_blocks[i][grid_height-2].set_f5(f5_tmp);
                }
                else
                {
                    grid_blocks[1][j].set_f5(f5_tmp);       
                }
            }  

            if (!wall_6) {grid_blocks[(int)(i + c6[0] * dt / dx)][(int)(j + c6[1] * dt / dx)].set_f6(f6_tmp);}
            else 
            {
                if (wall_6 && wall_5)
                {
                    grid_blocks[i][grid_height-2].set_f6(f6_tmp);

                }
                else
                {
                    grid_blocks[1][j].set_f6(f6_tmp);

                }
            }  

            if (!wall_7) {grid_blocks[(int)(i + c7[0] * dt / dx)][(int)(j + c7[1] * dt / dx)].set_f7(f7_tmp);}
            else 
            {
                if (wall_7 && wall_8)
                {
                    grid_blocks[i][1].set_f7(f7_tmp);

                }
                else
                {
                    grid_blocks[grid_width-2][j].set_f7(f7_tmp);

                }
            }  

            if (!wall_8) {grid_blocks[(int)(i + c8[0] * dt / dx)][(int)(j + c8[1] * dt / dx)].set_f8(f8_tmp);}
            else 
            {
                if (wall_8 && wall_5)
                {
                    grid_blocks[1][j].set_f8(f8_tmp);

                }
                else
                {
                    grid_blocks[i][1].set_f8(f8_tmp);
        
                }
            } 
            */
                
        }
    }


    
    int x = 1; int y = 1;
    //std::cout << "f0  = " << grid_blocks[x][y].get_f1() << ", f0_eq = " << grid_blocks[x][y].get_f1_eq()  << '\n'; 
    //std::cout << "f1  = " << grid_blocks[x][y].get_f1() << ", f1_eq = " << grid_blocks[x][y].get_f1_eq()  <<'\n';
    //std::cout << "f2  = " << grid_blocks[x][y].get_f2() << ", f2_eq = " << grid_blocks[x][y].get_f2_eq()  <<'\n';
    //std::cout << "f3  = " << grid_blocks[x][y].get_f3() << ", f3_eq = " << grid_blocks[x][y].get_f3_eq()  <<'\n';
    //std::cout << "f4  = " << grid_blocks[x][y].get_f4() << ", f4_eq = " << grid_blocks[x][y].get_f4_eq()  <<'\n';
    //std::cout << "f5  = " << grid_blocks[x][y].get_f5() << ", f5_eq = " << grid_blocks[x][y].get_f5_eq()  <<'\n';
    //std::cout << "f6  = " << grid_blocks[x][y].get_f6() << ", f6_eq = " << grid_blocks[x][y].get_f6_eq()  <<'\n';
    //std::cout << "f7  = " << grid_blocks[x][y].get_f7() << ", f7_eq = " << grid_blocks[x][y].get_f7_eq()  <<'\n';
    //std::cout << "f8  = " << grid_blocks[x][y].get_f8() << ", f8_eq = " << grid_blocks[x][y].get_f8_eq()  <<'\n';
    //
    //std::cout << "rho = " << grid_blocks[x][y].get_rho()  << ", u_norm = (" << grid_blocks[x][y].get_u_normalized()[0] << ", " << grid_blocks[x][y].get_u_normalized()[1] << ")" <<'\n';
    

}

void Game::render()
{


    // draw grid
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i <= grid_width; i++) 
    {
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderDrawLine(renderer, i * dx, 0, i * dx, grid_height * dx);
    }

    for (int j = 0; j <= grid_height; j++) 
    {
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderDrawLine(renderer, 0, j * dx, grid_width * dx, j * dx);
    }

    //color squares
    for (int i = 0; i <= grid_width; i++)
    {
        for (int j = 0; j <= grid_height; j++)
        {
            bool is_wall = grid_blocks[i][j].is_boundary();

            std::vector<float> u = grid_blocks[i][j].get_u();
            std::vector<float> u_norm = grid_blocks[i][j].get_u_normalized();
            float u_magn = std::sqrt(u[0]*u[0] + u[1]*u[1]);

            float theta = std::atan2(u_norm[1], u_norm[0]);
            //draw window border
            if (!is_wall)
            {


                SDL_SetRenderDrawColor(renderer, std::abs(u[0] / u_magn) * 125, 0, std::abs(u[1] / u_magn) * 255, 255);
                //SDL_RenderDrawLine(renderer, i * dx + (dx / 2), j * dx + (dx / 2), i * dx + (dx / 2) + (u_norm[0]) , j * dx + (dx / 2) + (u_norm[1]) );
                SDL_RenderDrawPoint(renderer, i * dx + (dx / 2), j * dx + (dx / 2));
                //grid_blocks[i][j].draw();
                
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                grid_blocks[i][j].draw();

            }


        }
    }

    

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::running() {return is_running;}




