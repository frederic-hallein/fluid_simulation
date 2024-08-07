#include <iostream>
#include <cmath>

#include "Player.hpp"
#include "Map.hpp"

Player::Player() {}

Player::~Player() {}

void Player::handleEvents(SDL_Event event)
{

    switch(event.type){
        case SDL_KEYDOWN:
            {
            Uint8 const* keys = SDL_GetKeyboardState(nullptr);
            if(keys[SDL_SCANCODE_W] == 1)
                direction = Direction::UP;
            else if(keys[SDL_SCANCODE_S] == 1)
                direction = Direction::DOWN;
            else if(keys[SDL_SCANCODE_A] == 1)
                direction = Direction::LEFT;
            else if(keys[SDL_SCANCODE_D] == 1)
                direction = Direction::RIGHT;
            break;
            }
        case SDL_KEYUP:
            {
            Uint8 const* keys = SDL_GetKeyboardState(nullptr);
            if(keys[SDL_SCANCODE_W] == 0){
                direction = Direction::NONE;}
            else if(keys[SDL_SCANCODE_S] == 0)
                direction = Direction::NONE;
            else if(keys[SDL_SCANCODE_A] == 0)
                direction = Direction::NONE;
            else if(keys[SDL_SCANCODE_D] == 0)
                direction = Direction::NONE;
            }
            break;
    }
}

void Player::printPlayerInfo()
{
    std::cout << "(" << x_pos << ", " << y_pos << ")" << ", ";
    std::cout << "(" << x_dir << ", " << y_dir << ")" << ", ";
    std::cout << "(" << x_plane << ", " << y_plane << ")" << std::endl;
}

void Player::update()
{
    switch (direction){
        case Direction::NONE:
            x_pos += 0.0;
            y_pos += 0.0;
            break;
        case Direction::UP:
            if (map.getValue((int)(x_pos + x_dir * move_speed), (int)y_pos) == false) {x_pos += x_dir * move_speed;}
            if (map.getValue((int)x_pos, (int)(y_pos + y_dir * move_speed)) == false) {y_pos += y_dir * move_speed;}
            break;
        case Direction::DOWN:
            if (map.getValue((int)(x_pos - x_dir * move_speed), (int)y_pos) == false) {x_pos -= x_dir * move_speed;}
            if (map.getValue((int)x_pos, (int)(y_pos - y_dir * move_speed)) == false) {y_pos -= y_dir * move_speed;}
            break;
        case Direction::LEFT:
            //both camera direction and camera plane must be rotated
            old_x_dir = x_dir;
            x_dir = x_dir * cos(rot_speed) - y_dir * sin(rot_speed);
            y_dir = old_x_dir * sin(rot_speed) + y_dir * cos(rot_speed);
            
            old_x_plane = x_plane;
            x_plane = x_plane * cos(rot_speed) - y_plane * sin(rot_speed);
            y_plane = old_x_plane * sin(rot_speed) + y_plane * cos(rot_speed);
            break;
        case Direction::RIGHT:
            //both camera direction and camera plane must be rotated
            old_x_dir = x_dir;
            x_dir = x_dir * cos(-rot_speed) - y_dir * sin(-rot_speed);
            y_dir = old_x_dir * sin(-rot_speed) + y_dir * cos(-rot_speed);

            old_x_plane = x_plane;
            x_plane = x_plane * cos(-rot_speed) - y_plane * sin(-rot_speed);
            y_plane = old_x_plane * sin(-rot_speed) + y_plane * cos(-rot_speed);
            break;
    }
}

void Player::setMoveSpeed(double frame_time) {move_speed = frame_time;}
void Player::setRotSpeed(double frame_time) {rot_speed = frame_time;}

double Player::getXPos() {return x_pos;}
double Player::getYPos() {return y_pos;}
double Player::getXDir() {return x_dir;}
double Player::getYDir() {return y_dir;}
double Player::getXPlane() {return x_plane;}
double Player::getYPlane() {return y_plane;}
double Player::getMoveScale() {return move_scale;}
double Player::getRotScale() {return rot_scale;}









