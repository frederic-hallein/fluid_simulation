#include <iostream>
#include <SDL2/SDL.h>

#include "Game.hpp"
#include "Timer.hpp"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* argv[]){
    Game game;
    game.init("Ray Casting", SCREEN_WIDTH, SCREEN_HEIGHT);

    double old_time = 0; 
    while (game.running()){
        Timer timer(old_time); 
        game.handleEvents();
        game.update();

        timer.start();
        game.render();
        timer.stop();

        old_time = timer.getTime();
        game.setSpeedModifierPlayer(timer.getFrameTime());
    }

    game.clean();
    return 0;
}