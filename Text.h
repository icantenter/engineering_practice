#pragma once
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>


class Text
{
protected:
    SDL_Texture *text_texture;
    SDL_Color text_color;
    SDL_Renderer *renderer;
    std::string text;

public:
    Text(SDL_Renderer *renderer, const std::string text, SDL_Color text_color);
    const std::string get() { return this->text; };
    void reset_text(const std::string &text);
    void draw(SDL_Rect *text_rect);
    ~Text();
};


