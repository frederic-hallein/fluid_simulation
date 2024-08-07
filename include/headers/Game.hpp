#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Player.hpp"
#include "Map.hpp"
#include "Ray.hpp"

class Game {  
public:
    Game();
    ~Game();

    void init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

    void setSpeedModifierPlayer(double frame_time);

private:
    int w;
    int h;
    bool is_running = true;   
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    Player player;
    Map map;
    std::vector<Ray> rays;
};
