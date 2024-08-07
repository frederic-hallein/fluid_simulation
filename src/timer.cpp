#include <iostream>
#include <cmath>

#include "Timer.hpp"

Timer::Timer(double p_time)
{
    old_time = p_time;
}

Timer::~Timer() {}

void Timer::start()
{
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    end_time = std::chrono::high_resolution_clock::now();
    time = std::chrono::time_point_cast<std::chrono::milliseconds>(end_time).time_since_epoch().count();

    frame_time = (time - old_time) / 1000.0;

    double FPS = 1.0 / frame_time;
    //std::cout << "FPS = " << (int)FPS << " \n";
}

double Timer::getTime() {return time;}
double Timer::getFrameTime() {return frame_time;}



