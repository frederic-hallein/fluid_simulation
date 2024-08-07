#pragma once

#include <SDL2/SDL.h>

#include "Map.hpp"

class Player {
public:
    Player();
    ~Player();

    enum Direction
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    void handleEvents(SDL_Event event);

    void printPlayerInfo();
    void update();

    void setMoveSpeed(double frame_time);
    void setRotSpeed(double frame_time);

    double getXPos();
    double getYPos();
    double getXDir();
    double getYDir();
    double getXPlane();
    double getYPlane();
    double getMoveScale();
    double getRotScale();

private:
    SDL_Event event;
    Direction direction;
    Map map;

    double x_pos = 22;
    double y_pos = 21.5;
    double x_dir = -1;
    double y_dir = 0;
    double x_plane = 0;
    double y_plane = 0.66;
    double move_speed;
    double rot_speed;
    double move_scale = 5.0;
    double rot_scale = 3.0;
    double old_x_dir;
    double old_x_plane;
};