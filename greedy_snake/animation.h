#ifndef _animation_h_
#define _animation_h_

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Curtain.h"
#include "Settings.h"


void fade_out(SDL_Renderer *renderer, Settings *setting);
#endif