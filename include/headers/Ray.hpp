#pragma once

#include "Map.hpp"

class Ray {
public:
    Ray();
    ~Ray();

    void setXCamera(int x_pos_camera_space, int SCREEN_WIDTH);
    void setXDir(double player_x_dir, double x_plane, double x_camera);
    void setYDir(double player_y_dir, double y_plane, double x_camera);
    void setDeltaXDist();
    void setDeltaYDist();
    void setLineHeight(int SCREEN_HEIGHT);
    void setPerpWallDist();
    void setDrawStart(int SCREEN_HEIGHT);
    void setDrawEnd(int SCREEN_HEIGHT);

    double getXCamera();
    double getXDir();
    double getYDir();
    double getSideXDist();
    double getSideYDist();
    double getDeltaXDist();
    double getDeltaYDist();
    double getPerpWallDist();
    int getLineHeight();
    int getDrawStart();
    int getDrawEnd();
    int getSide();

    void calculateStep(double player_x_pos, double player_y_pos, int x_map, int y_map);
    void performDDA(int& tmp_x_map, int& tmp_y_map, Map& map);

private:
    double x_camera;
    double ray_x_dir;
    double ray_y_dir;
    double side_x_dist;
    double side_y_dist;
    double delta_x_dist;
    double delta_y_dist;
    double x_step;
    double y_step;
    double perp_wall_dist;

    int hit = 0;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
};