#pragma once
#include "Settings.h"
#include "SDL2/SDL.h"
#include <string>
#include <vector>
#include "DataBase.h"

void log_in(SDL_Renderer *renderer, Settings *setting, DataBase *players);
void init_log_textures(SDL_Renderer *renderer, SDL_Texture **background_texture,
                       std::vector<SDL_Texture *> &log_button_textures, 
                       std::vector<SDL_Texture *> &exit_button_textures,
                       std::vector<SDL_Texture *> & enter_button_textures);