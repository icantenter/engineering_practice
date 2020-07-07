
#pragma once

#include "SDL2/SDL.h"
#include <SDL_draw.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <time.h>
#include "error.h"
#include "Settings.h"
const int button_count = 4;

static const std::string button_text[] = {
    "play", "log in", "data", "quit"};
enum player_requests
{
    PLAY = 0,
    LOG_IN = 1,
    DATA = 2,
    QUIT = 3,
    EGG = 4,
    INVALID_REQUEST = 5
};
int menu(SDL_Renderer *renderer, Settings *setting);