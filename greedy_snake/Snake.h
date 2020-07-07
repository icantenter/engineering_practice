#pragma once
#include "SDL2/SDL.h"
#include <vector>
#include <algorithm>
#include "direction.h"
#include "function.h"
#include "error.h"

typedef struct SNAKEBLOCK
{
    SDL_Rect rect;
    SNAKEBLOCK *next = NULL;
    SDL_Color rect_color;

} SNAKEBLOCK;

class Snake
{
private:
    SDL_Renderer *renderer;
    int length = 1;
    int direction = DIRECTIONLESS;
    int grow_direction = DIRECTIONLESS;
    int block_width, block_height;

public:
    SNAKEBLOCK *head = NULL;
    Snake(SDL_Renderer *renderer, SDL_Rect *head_rect);
    bool grow(int length, int direction = DIRECTIONLESS);
    bool check_collides(SDL_Rect *detecting_rect);
    std::vector<SDL_Rect *> check_collides(std::vector<SDL_Rect *>& detecting_rects);
    bool check_self_collide();
    bool check_head_collide(SDL_Rect *detecting_rect);
    void update(int direction);
    void change_color();
    int get_length();
    int get_direction();
    void draw();
    ~Snake();
};



/*void SNAKEBLOCK::set_rect_color(SDL_Color *color)
{
    this->rect_color.a = (color->a > 0) ? color->a % 255 : 0;
    this->rect_color.b = (color->a > 0) ? color->b % 255 : 0;
    this->rect_color.g = (color->a > 0) ? color->g % 255 : 0;
    this->rect_color.r = (color->a > 0) ? color->r % 255 : 0;

    void kill(SNAKEBLOCK *previous_block);

void Snake::kill(SNAKEBLOCK *previous_block)
{
    SNAKEBLOCK *killing_block;

    try
    {
        if (previous_block != this->head)
        {
            if (previous_block == NULL || previous_block->next == NULL)
            {
                throw error_msgs[ERROR_ARGUMENT];
            }
            killing_block = previous_block->next;
            previous_block->next = killing_block->next;
            if (killing_block == this->tail)
            {
                previous_block = this->tail;
                previous_block->next = NULL;
            }
        }
        else
        {
            killing_block = this->head;
            this->head = this->head->next;
        }

        if (killing_block == NULL)
        {
            throw error_msgs[ERROR_ARGUMENT];
        }

        delete killing_block;
    }
    catch (const std::string msg)
    {
        std::cerr << "Snake" << msg << '\n';
    }
}
}*/