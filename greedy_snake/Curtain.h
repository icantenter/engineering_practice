#ifndef _Curtain_h_
#define _Curtain_h_
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class Curtain
{
private:
    std::string curtain_image = "sources\\curtain.png";
    SDL_Rect curtain_rect;
    int alpha = 10;
    SDL_Texture *curtain_texture;
    SDL_Renderer *renderer;

public:
    Curtain(SDL_Renderer *renderer, SDL_Rect *des_rect);
    void set_alpha(int alpha);
    void set_rect(SDL_Rect *des_rect);
    void draw();
    ~Curtain();
};


#endif