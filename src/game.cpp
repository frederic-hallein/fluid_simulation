#include <iostream>
#include <format>
#include <stdexcept>


#include "Game.hpp"


const int GRAV_ACC = 9.81;

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen)
{
    // initialize window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_Init has failed." << '\n';
        std::cout << "Error:" << SDL_GetError() << '\n'; 
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
    
    this->grid_w = SCREEN_WIDTH / grid_size;
    this->grid_h = SCREEN_HEIGHT / grid_size;

    // initialize grid blocks
    for (int i = 0; i <= grid_w + 2; i++)
    {    
        for (int j = 0; j <= grid_h + 2; j++)
        {
            GridBlock grid_block(renderer, grid_size, i, j);
            grid_blocks.push_back(std::vector<GridBlock>());
            grid_blocks[i].push_back(grid_block);

            // set window border cells
            if (i < 1 || j < 1)
            {
                grid_blocks[i][j].set_wall();
                //std::cout << i << ',' << j << '\n';

            }

            if (i > grid_w + 1 || j > grid_h + 1)
            {
                grid_blocks[i][j].set_wall();
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
    
    for (int i = 1; i <= grid_w; i++)
    {
        for (int j = 1; j <= grid_h; j++)
        {
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


            //std::cout << "pos: " << i << ',' << j << " : " << s << ',' << s_up << ',' << s_right << ',' << s_down << ',' << s_left;
            
            // gravity 
            v += delta_t * GRAV_ACC;

            // incompressibility
            double d = o * (u_right - u + v_down - v);
            int total_s = s_right + s_left + s_down + s_up;
            //std::cout << "pos:" << i << ',' << j << d << ',' << total_s << ':' << s_right << ',' << s_left << ',' << s_down << ',' << s_up  << '\n';

            //pressure
            double p = grid_blocks[i][j].get_p();

            //density
            double rho = grid_blocks[i][j].get_rho();


            try
            {
                if (total_s == 0) 
                {
                    std::string error = std::format("Division by zero in grid block: {}, {}", i, j);
                    throw std::runtime_error(error); 
                }

                u       += d * (s_left  / total_s);
                u_right -= d * (s_right / total_s);
                v       += d * (s_up    / total_s);
                v_down  -= d * (s_down  / total_s);
                
                p += (d/s) * (rho * grid_size / delta_t);

                // update velocity
                grid_blocks[i][j].set_velocity(v, u);
                grid_blocks[i+1][j].set_velocity(v_right, u_right);
                grid_blocks[i][j+1].set_velocity(v_down, u_down);

                // update pressure
                grid_blocks[i][j].set_p(p);
            }

            catch (const std::exception& e)
            {
                std::cout << "Exception " << e.what() << '\n';
            }

            
        }
    }
    
    
}

void Game::render()
{
    int grid_color[3] = {255, 255, 255};


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
    for (int i = 1; i <= grid_w; i++)
    {
        //std::cout << i << '\n';
        for (int j = 10; j <= 15; j++)
        {
            grid_blocks[i][j].draw();
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




