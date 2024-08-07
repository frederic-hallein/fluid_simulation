#pragma once

class Timer{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void delayFrame();

private:
    uint32_t frame_start;
    int frame_time;
};