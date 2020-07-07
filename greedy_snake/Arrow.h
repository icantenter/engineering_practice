#ifndef  _arrow_h_
#define _arrow_h_
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class Arrow
{
private:
    SDL_Renderer *renderer;
    SDL_Texture *arrow_texture;
    int direction = 1;
    int speed = 6;

public:
    SDL_Rect arrow_rect;
    float x, y;
    void draw();
    void update(SDL_Point points[], int point_direction);
    void set_range(SDL_Point points[], int point_direction);
    Arrow(SDL_Rect *arrow_rect, SDL_Renderer *renderer, const std::string image);
    ~Arrow();
};


#endif