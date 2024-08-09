#include <iostream>

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
    for (int i = -1; i < grid_w + 1; i++)
    {    
        for (int j = -1; j < grid_h + 1; j++)
        {
            GridBlock grid_block(renderer, grid_size, i, j);
            grid_blocks.push_back(std::vector<GridBlock>());
            grid_blocks[i].push_back(grid_block);

            if (i < 0 || i > grid_w || j < 0 || j > grid_h)
            {
                //grid_blocks[i][j].get_s_bottom();
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
    for (int i = 0; i < w / grid_size; i++)
    {
        for (int j = 0; j < h / grid_size; j++)
        {
            double v_bottom = grid_blocks[i][j].get_v_bottom();
            double v_top = grid_blocks[i][j].get_v_top();
            double u_left = grid_blocks[i][j].get_u_left();
            double u_right = grid_blocks[i][j].get_u_right();

            
            /*
            double s_bottom = grid_blocks[i][j].get_s_bottom();
            double s_top = grid_blocks[i][j].get_s_top();
            double s_left = grid_blocks[i][j].get_s_left();
            double s_right = grid_blocks[i][j].get_s_right();
            */

            // gravity 
            v_bottom += delta_t * GRAV_ACC;
            v_top += delta_t * GRAV_ACC;

            // incompressibility
            double d, s;
            d += u_right - u_left + v_top - v_bottom;
            //s += 

            u_left += d/4;
            u_right -= d/4;
            v_bottom += d/4;
            v_top -= d/4;


            grid_blocks[i][j].set_velocity(v_bottom, v_top, u_left, u_right);
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
    for (int i = 0; i < w / grid_size; i++)
    {
        //std::cout << i << '\n';
        for (int j = 10; j <= 15; j++)
        {
            grid_blocks[i][j].draw();
        }
    }
    //grid_blocks[5][3].draw();
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




