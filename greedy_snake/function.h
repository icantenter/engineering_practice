#pragma once
#include "SDL2/SDL.h"
#include <vector>
typedef struct
{
    SDL_Rect *hit_rect;
    SDL_Rect *hitted_rect;

}COLLIDEDRECTS;

bool collide(SDL_Rect *rect_a, SDL_Rect *rect_b);
bool collide(std::vector<SDL_Rect> rects, SDL_Rect *rect_b);