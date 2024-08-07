#include <iostream>

#include "Game.hpp"


Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen)
{
    // initialize window and renderer
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

    // initialize grid
    grid.init(SCREEN_WIDTH, SCREEN_HEIGHT);

}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
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

}

void Game::render()
{

}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::running() {return is_running;}


