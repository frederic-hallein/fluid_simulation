#include <iostream>
#include <format>
#include <stdexcept>


#include "Game.hpp"


const double GRAV_ACC = 9.81;

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
    this->w = SCREEN_WIDTH; 
    this->h = SCREEN_HEIGHT;

    this->grid_w = w / grid_size;
    this->grid_h = h / grid_size;

    // initialize grid blocks
    for (int i = 0; i <= grid_w; i++)
    {    
        for (int j = 0; j <= grid_h; j++)
        {
            GridBlock grid_block(renderer, grid_size, i * grid_size, j * grid_size);
            grid_blocks.push_back(std::vector<GridBlock>());
            grid_blocks[i].push_back(grid_block);

            // set window border cells
            if (i == 0 || j == 0)
            {
                grid_blocks[i][j].set_boundary();
                //std::cout << i << ',' << j << '\n';

            }

            if (i == grid_w - 1 || j == grid_h - 1)
            {
                grid_blocks[i][j].set_boundary();
                //std::cout << i << ',' << j << '\n';
   
            }
            
        }
    }



    //std::cout << grid_blocks[0].size() << '\n'; // 80
    //std::cout << grid_blocks.size() / grid_blocks[0].size() << '\n'; // 40

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

    // gravity
    for (int i = 1; i <= grid_w - 2; i++) {
        for (int j = 1; j <= grid_h - 2; j++) {
            double v = grid_blocks[i][j].get_v();
            v += delta_t * GRAV_ACC;
            grid_blocks[i][j].set_v(v);
        }
    }
    /*
    double v;
    double v_up;
    double v_right;
    double v_down;
    double v_left;

    double u;
    double u_up;
    double u_right;
    double u_down;
    double u_left;

    int s;
    int s_up;
    int s_right;
    int s_down;
    int s_left;
    */
    // incompressibility
    for (int i = 1; i <= grid_w - 2; i++) {
        for (int j = 1; j <= grid_h - 2; j++) {
            double v       = grid_blocks[i][j].get_v();
            double v_up    = grid_blocks[i][j-1].get_v();
            double v_right = grid_blocks[i+1][j].get_v();
            double v_down  = grid_blocks[i][j+1].get_v();
            double v_left  = grid_blocks[i-1][j].get_v();

            double u       = grid_blocks[i][j].get_u();
            double u_up    = grid_blocks[i][j-1].get_u();
            double u_right = grid_blocks[i+1][j].get_u();
            double u_down  = grid_blocks[i][j+1].get_u();
            double u_left  = grid_blocks[i-1][j].get_u();
            
            int s       = grid_blocks[i][j].get_s();
            int s_up    = grid_blocks[i][j-1].get_s();
            int s_right = grid_blocks[i+1][j].get_s();
            int s_down  = grid_blocks[i][j+1].get_s();
            int s_left  = grid_blocks[i-1][j].get_s();

            double d = o * (u_right - u + v_down - v); // divergence
            int total_s = s_right + s_left + s_down + s_up;

            //std::cout << "d = " << d << ", " << "s = " << total_s <<  '\n';
            try {

                if (total_s == 0) {
                    std::string error_message = std::format("Division by zero in grid block: {}, {}", i, j);
                    throw std::runtime_error(error_message); 
                    is_running = false;
                }
                
                u       += d * (s_left  / (double)total_s);
                u_right -= d * (s_right / (double)total_s);
                v       += d * (s_up    / (double)total_s); // + (or -)
                v_down  -= d * (s_down  / (double)total_s); // - (or +)


                // update velocity
                grid_blocks[i][j].set_u(u);
                grid_blocks[i+1][j].set_u(u_right);
                grid_blocks[i][j].set_v(v);
                grid_blocks[i][j+1].set_v(v_down);

                if (i == 1 && j == 3){
                std::cout << "(" << i << ", " << j << ") " << "u = " << u << ", " << "u_right = " << u_right << ", " << "v = " << v << ", " << "v_down = " << v_down << ", " << "d = " << d << ", " << "s = " << total_s << '\n';
                }
                if (i == 2 && j == 3){
                std::cout << "(" << i << ", " << j << ") " << "u = " << u << ", " << "u_right = " << u_right << ", " << "v = " << v << ", " << "v_down = " << v_down << ", " << "d = " << d << ", " << "s = " << total_s << '\n';
                }
                // update pressure
                double rho = grid_blocks[i][j].get_rho();
                double p = grid_blocks[i][j].get_p();
                p += (d/s) * (rho * grid_size / delta_t);
                grid_blocks[i][j].set_p(p);



            } catch (const std::exception& e) {std::cout << "Exception: " << e.what() << '\n';}

            
        }
    }

    double x;
    double y;

    double w_00;
    double w_10;
    double w_01;
    double w_11;

    // advection
    
    for (int i = 1; i <= grid_w - 2; i++) {
        for (int j = 1; j <= grid_h - 2; j++) {

            double v       = grid_blocks[i][j].get_v();
            double v_up    = grid_blocks[i][j-1].get_v();
            double v_right = grid_blocks[i+1][j].get_v();
            double v_down  = grid_blocks[i][j+1].get_v();
            double v_left  = grid_blocks[i-1][j].get_v();

            double u       = grid_blocks[i][j].get_u();
            double u_up    = grid_blocks[i][j-1].get_u();
            double u_right = grid_blocks[i+1][j].get_u();
            double u_down  = grid_blocks[i][j+1].get_u();
            double u_left  = grid_blocks[i-1][j].get_u();

            x;
            y;

            w_00;
            w_10;
            w_01;
            w_11;

            // u component
            x = grid_blocks[i][j].get_x_pos();
            y = grid_blocks[i][j].get_y_pos() + grid_size / 2;

            double v_left_down = grid_blocks[i-1][j+1].get_v();
            double v_avg = (v_down + v + v_left_down + v_left) / 4;


            x -= delta_t * u;
            y -= delta_t * v_avg;


            w_00 = 1 - x / grid_size; 
            w_10 = 1 - y / grid_size;
            w_01 = x / grid_size;
            w_11 = y / grid_size;

            double u_right_up = grid_blocks[i+1][j-1].get_u();
            double u_old = (w_00 * w_10) * u + (w_01 * w_10) * u_right + (w_01 * w_11) * u_up + (w_00 * w_11) * u_right_up;


            grid_blocks[i][j].set_u(u_old);




        }
    }

    for (int i = 1; i <= grid_w - 2; i++) {
        for (int j = 1; j <= grid_h - 2; j++) {

            double v       = grid_blocks[i][j].get_v();
            double v_up    = grid_blocks[i][j-1].get_v();
            double v_right = grid_blocks[i+1][j].get_v();
            double v_down  = grid_blocks[i][j+1].get_v();
            double v_left  = grid_blocks[i-1][j].get_v();

            double u       = grid_blocks[i][j].get_u();
            double u_up    = grid_blocks[i][j-1].get_u();
            double u_right = grid_blocks[i+1][j].get_u();
            double u_down  = grid_blocks[i][j+1].get_u();
            double u_left  = grid_blocks[i-1][j].get_u();

            double x;
            double y;

            double w_00;
            double w_10;
            double w_01;
            double w_11;


            // v component
            x = grid_blocks[i][j].get_x_pos() + grid_size / 2;
            y = grid_blocks[i][j].get_y_pos();

            double u_right_up = grid_blocks[i+1][j-1].get_u();
            double u_avg = (u_right + u_right_up + u + u_up) / 4;

            x -= delta_t * u_avg;
            y -= delta_t * v;

            w_00 = 1 - x / grid_size; 
            w_10 = 1 - y / grid_size;
            w_01 = x / grid_size;
            w_11 = y / grid_size;

            double v_right_up = grid_blocks[i+1][j-1].get_v();
            double v_old = (w_00 * w_10) * v + (w_01 * w_10) * v_right + (w_01 * w_11) * v_up + (w_00 * w_11) * v_right_up;


            //grid_blocks[i][j].set_v(v_old);


 


        }
    }

    for (int i = 1; i <= grid_w - 2; i++) {
        for (int j = 1; j <= grid_h - 2; j++) {
            //std::cout << '(' << i << ", " << j << "), (" << grid_blocks[i][j].get_x_pos() << ", " << grid_blocks[i][j].get_y_pos() << ')' << ": v = " << grid_blocks[i][j].get_v() << ", u = " << grid_blocks[i][j].get_u() << '\n';
            if (std::isnan(grid_blocks[i][j].get_v()) || std::isnan(grid_blocks[i][j].get_u()))
            {
                is_running= false;
            }

        }
    }
    


    
    
}

void Game::render()
{
    int grid_color[3] = {255, 255, 255}; //white


    // draw grid
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int x = 0; x < w; x += grid_size)
    {
        SDL_SetRenderDrawColor(renderer, grid_color[0], grid_color[1], grid_color[2], 255);
        SDL_RenderDrawLine(renderer, x, 0, x, h);
    }

    for (int y = 0; y < h; y += grid_size)
    {
        SDL_SetRenderDrawColor(renderer, grid_color[0], grid_color[1], grid_color[2], 255);
        SDL_RenderDrawLine(renderer, 0, y, w, y);
    }

    //color squares
    for (int i = 0; i <= grid_w; i++)
    {
        //std::cout << i << '\n';
        for (int j = 0; j <= grid_h; j++)
        {
            //grid_blocks[i][j].set_rho(1.0);

            //draw window border
            if (!grid_blocks[i][j].get_s())
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                grid_blocks[i][j].draw();

            }
        }
    }
    
    //grid_blocks[1][1].draw();
    //grid_blocks[2][10].draw();
    //grid_blocks[8][8].draw();
    //grid_blocks[40][30].draw();
    

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::running() {return is_running;}




