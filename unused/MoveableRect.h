#pragma once
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "Vector.h"

typedef struct
{
    VECTOR *vector;
    SDL_FPoint current_point;
    SDL_Rect rect;
    int current_des;
    SDL_Point destinations[2];;
} MOVEABLERECT;

int update(MOVEABLERECT *rect);
void reorientate(MOVEABLERECT *rect);
double get_surplus_distance(MOVEABLERECT *rect);
bool check_arrive(MOVEABLERECT *rect);