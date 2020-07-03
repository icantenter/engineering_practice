#include "Snake.h"
#include <time.h>
#include "Settings.h"
int main(int args, char *argv[])
{
    clock_t start, end;
    Settings *setting = new Settings();

    SDL_Init(SDL_INIT_EVERYTHING);
    //TTF_Init();
    SDL_Window *window =
        SDL_CreateWindow("GreedySnake",
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         setting->window_width, setting->window_height,
                         SDL_WINDOW_SHOWN); //SDL_WINDOW_FULLSCREEN
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (!window)
        return -1;
    if (!renderer)
        return -2;
    SDL_Rect head_rect{200, 200, 40, 40};
    Snake *snake = new Snake(renderer, &head_rect);
    snake->grow(3, LEFT);
     while (1)
    {
        start = clock();
        SDL_RenderClear(renderer);
        snake->draw();
        end = clock();
        if (60 - (end - start) > 0)
            SDL_Delay(60 - (end - start));
        SDL_RenderPresent(renderer);
    }
    return 0;
}
