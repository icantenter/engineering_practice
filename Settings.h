#ifndef _settings_h_
#define _settings_h_
#include "SDL2/SDL.h"
class Settings
{

public:
    int window_width = 1200;
    int window_height = 800;
    SDL_Color title_color = {255, 255, 255};
    int button_color_r = 255;
    int button_color_g = 255;
    int button_color_b = 255;

    Settings();
    ~Settings();
};

#endif