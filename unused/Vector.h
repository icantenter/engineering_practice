#pragma once
#include "SDL2/SDL.h"
#include <cmath>
#include <iostream>
typedef struct
{
    float x_vector, y_vector;
    float speed;

}VECTOR;

int move_point(VECTOR *vector, SDL_FPoint *move_point, SDL_Point *border_point);
VECTOR *create_vector(SDL_Point *init_point, SDL_Point *des_point, float speed);