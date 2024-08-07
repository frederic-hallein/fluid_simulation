#include <SDL2/SDL.h>
#include <iostream>

#include "Timer.hpp"

static const int FPS = 60;
static const int frame_delay = 1000 / FPS;

Timer::Timer() {}

Timer::~Timer() {}

void Timer::start() {frame_start = SDL_GetTicks();}

void Timer::stop() {frame_time = SDL_GetTicks() - frame_start;}

void Timer::delayFrame()
{
    if (frame_delay > frame_time) {SDL_Delay(frame_delay - frame_time);}
}



