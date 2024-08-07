#pragma once

class Grid { 
public:
    Grid();
    ~Grid();

    void init(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void update();
    void render();
    void clean();

private:
    int grid_size = 5;
};