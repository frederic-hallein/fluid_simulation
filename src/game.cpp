#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Ray.hpp"

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // initiatlize window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "SDL_Init has failed." << std::endl;
        std::cout << "Error:" << SDL_GetError() << std::endl; 
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << "Could not create window." << std::endl;
        std::cout << "Error: " << SDL_GetError() <<std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        std::cout << "Could not create renderer." << std::endl;
        std::cout << "Error: " << SDL_GetError() <<std::endl;
    }


    // keep hold of SCREEN_WIDTH and SCREEN_HEIGHT
    w = SCREEN_WIDTH;
    h = SCREEN_HEIGHT;

    // initialize array of rays
    for (int x = 0; x < w; x++){
        Ray ray;
        rays.push_back(ray);
    }
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    player.handleEvents(event);
    switch (event.type){
        case SDL_QUIT:
            is_running = false;   
            break;

        default:
            break;
    }
}

void Game::update()
{
    player.update();
    // player.printPlayerInfo();

    for (int x = 0; x < w; x++){        
        // set x-coordinate in camera space
        rays[x].setXCamera(x, w);
        
        // calculate ray position and direction
        rays[x].setXDir(player.getXDir(), player.getXPlane(), rays[x].getXCamera());
        rays[x].setYDir(player.getYDir(), player.getYPlane(), rays[x].getXCamera());

        // which box of the map we're in
        map.setMapPos(player.getXPos(), player.getYPos());

        // length of ray from one x or y-side to next x or y-side
        rays[x].setDeltaXDist();
        rays[x].setDeltaYDist();

        // calculate step and initial sideDist
        rays[x].calculateStep(player.getXPos(), player.getYPos(), map.getXMap(), map.getYMap());

        // perform DDA
        int tmp_x_map = map.getXMap();
        int tmp_y_map = map.getYMap();
        rays[x].performDDA(tmp_x_map, tmp_y_map, map);

        // calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        rays[x].setPerpWallDist();

        // calculate height of line to draw on screen
        rays[x].setLineHeight(h);
        rays[x].setDrawStart(h);
        rays[x].setDrawEnd(h);
    }
}

void Game::render()
{
    int front_wall_RGB[3] = {214, 222, 167};
    int side_wall_RGB[3] = {195, 203, 110};
    int floor_RGB[3] = {130, 118, 47};
    int celing_RGB[3] = {167, 164, 122};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int x = 0; x < w; x++)
    {
        if (rays[x].getSide() == 1)
        {
            SDL_SetRenderDrawColor(renderer, side_wall_RGB[0], side_wall_RGB[1], side_wall_RGB[2], 255);
        }
        else 
        {
            SDL_SetRenderDrawColor(renderer, front_wall_RGB[0], front_wall_RGB[1], front_wall_RGB[2], 255);   
        }
    
        SDL_RenderDrawLine(renderer, x, rays[x].getDrawStart(), x, rays[x].getDrawEnd());
                
        // draw floor
        SDL_SetRenderDrawColor(renderer, floor_RGB[0], floor_RGB[1], floor_RGB[2], 255);
        SDL_RenderDrawLine(renderer, x, rays[x].getDrawEnd(), x, h);

        // draw ceiling
        SDL_SetRenderDrawColor(renderer, celing_RGB[0], celing_RGB[1], celing_RGB[2], 255);
        SDL_RenderDrawLine(renderer, x, 0, x, rays[x].getDrawStart());
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

void Game::setSpeedModifierPlayer(double frame_time)
{
    player.setMoveSpeed(frame_time * player.getMoveScale());
    player.setRotSpeed(frame_time * player.getRotScale());
}

