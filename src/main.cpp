#include <iostream>
#include <SDL2/SDL.h>

#include "Game.hpp"
#include "Timer.hpp"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

int main(int argc, char* argv[])
{
    Game game;
    game.init("Fluid Simulation", SCREEN_WIDTH, SCREEN_HEIGHT, false);

    Timer timer; 
    while (game.running()){
        timer.start();

        game.handleEvents();
        game.render();
        game.update();

        timer.stop();
        timer.delayFrame();
        
    }

    game.clean();
    return 0;
}

