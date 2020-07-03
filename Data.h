#pragma once
#include "Settings.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <sstream>
#include "DataBase.h"
#include "Button.h"
#include "Text.h"

int search_data(SDL_Renderer *renderer, DataBase *players, Settings *setting);
void init_textures(SDL_Renderer *renderer, std::vector<SDL_Texture *>& exit_button_textures);