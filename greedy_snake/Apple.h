#ifndef _Apple_h_
#define _Apple_h_
#include "SDL2/SDL.h"
#include "direction.h"
class Apple
{
private:
    SDL_Renderer *renderer;
    SDL_Rect rect;
    SDL_Color rect_color{50, 50, 50, 255};
public:
    Apple(SDL_Renderer *renderer, SDL_Rect *apple_rect);
    void draw();
    void reset_apple();
    SDL_Rect get_rect();
    ~Apple();
};


#endif