#pragma once

#include <chrono>

class Timer{
public:
    Timer(double p_time);
    ~Timer();

    void start();
    void stop();

    double getTime();
    double getFrameTime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;

    double old_time;
    double time;
    double frame_time;
};