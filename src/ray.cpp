#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>

#include "Ray.hpp"
#include "Map.hpp"

Ray::Ray() {}

Ray::~Ray() {}

void Ray::setXCamera(int x_pos_camera_space, int SCREEN_WIDTH) {x_camera = 2 * x_pos_camera_space / (double)SCREEN_WIDTH - 1;}
void Ray::setXDir(double player_x_dir, double x_plane, double x_camera) {ray_x_dir = player_x_dir + x_plane * x_camera;}
void Ray::setYDir(double player_y_dir, double y_plane, double x_camera) {ray_y_dir = player_y_dir + y_plane * x_camera;}
void Ray::setDeltaXDist() {delta_x_dist = (ray_x_dir == 0) ? 1e30 : std::fabs(1 / ray_x_dir);}
void Ray::setDeltaYDist() {delta_y_dist = (ray_y_dir == 0) ? 1e30 : std::fabs(1 / ray_y_dir);}
void Ray::setLineHeight(int SCREEN_HEIGHT) {line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);}

void Ray::setPerpWallDist()
{
    if (side == 0) 
    {
        perp_wall_dist = (side_x_dist - delta_x_dist);
    }
    else
    {
        perp_wall_dist = (side_y_dist - delta_y_dist);
    }
}

void Ray::setDrawStart(int SCREEN_HEIGHT)
{
    draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_start < 0){
        draw_start = 0;
    }
}


void Ray::setDrawEnd(int SCREEN_HEIGHT)
{
    draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_end >= SCREEN_HEIGHT){
        draw_end = SCREEN_HEIGHT - 1;
    }
}

double Ray::getXCamera() {return x_camera;}
double Ray::getXDir() {return ray_x_dir;}
double Ray::getYDir() {return ray_y_dir;}
double Ray::getSideXDist() {return side_x_dist;}
double Ray::getSideYDist() {return side_y_dist;}
double Ray::getDeltaXDist() {return delta_x_dist;}
double Ray::getDeltaYDist() {return delta_y_dist;}
double Ray::getPerpWallDist() {return perp_wall_dist;}

int Ray::getLineHeight() {return line_height;}
int Ray::getDrawStart() {return draw_start;}
int Ray::getDrawEnd() {return draw_end;}
int Ray::getSide() {return side;}

void Ray::calculateStep(double player_x_pos, double player_y_pos, int x_map, int y_map)
{
    if (ray_x_dir < 0)
    {
        x_step = -1;
        side_x_dist = (player_x_pos - x_map) * delta_x_dist;
    }
    else
    {
        x_step = 1;
        side_x_dist = (x_map + 1.0 - player_x_pos) * delta_x_dist;
    }


    if (ray_y_dir < 0)
    {
        y_step = -1;
        side_y_dist = (player_y_pos - y_map) * delta_y_dist;
    }
    else
    {
        y_step = 1;
        side_y_dist = (y_map + 1.0 - player_y_pos) * delta_y_dist;
    }
}

void Ray::performDDA(int& tmp_x_map, int& tmp_y_map, Map& map)
{
    while (hit == 0){
        // jump to next map square, either in x-direction, or in y-direction
        if (side_x_dist < side_y_dist)
        {
            side_x_dist += delta_x_dist;
            tmp_x_map += x_step;
            side = 0;
        }
        else
        {
            side_y_dist += delta_y_dist;
            tmp_y_map += y_step;
            side = 1;
        }
        
        // check if ray has hit a wall
        if (map.getValue(tmp_x_map, tmp_y_map) > 0) {hit = 1;}         
    }

    // reset hit to 0
    hit = 0;
}









