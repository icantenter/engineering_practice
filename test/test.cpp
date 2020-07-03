//#include "SDL2/SDL.h"
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include "GasterBlaster.h"
#include "Settings.h"
using namespace std;
float calculate_distance(SDL_FPoint *point_a, SDL_FPoint *point_b);
float calculate_distance(SDL_Point *point_a, SDL_Point *point_b);
float calculate_distance(SDL_Point *point_a, SDL_FPoint *point_b);

//const int map_size = 300;
//const int map_left = 450;
//const int map_top = 200;

void init_textures(SDL_Renderer *renderer, SDL_Texture *gast_texture[], SDL_Texture *blast_texture[]);
void initialize_gasts(SDL_Renderer *renderer, GasterBlaster *gasts[], Settings *setting);
int update_gast_blast(GasterBlaster *gast);

vector<GasterBlaster *> active_gasts;
vector<SDL_Rect *> active_barriers;

int main(int args, char *argv[])
{
    SDL_Texture *gast_texture[4];
    SDL_Texture *blast_texture[4];
    int point, surplus_distance;

    clock_t start, end;
    Settings *setting = new Settings();

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
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

    init_textures(renderer, gast_texture, blast_texture);
    GasterBlaster *gasts[4];
    while (1)
    {
        start = clock();
        SDL_RenderClear(renderer);
        if (active_gasts.size() == 0)
        {
            initialize_gasts(renderer, gasts, setting);
        }
        update(active_gasts);
        for (auto &gast : active_gasts)
        {
            surplus_distance = get_surplus_distance(&gast->body);

            if (surplus_distance < 100 && gast->body.current_des == 0)
            {
                gast->body.vector->speed = std::max((int)gast->body.vector->speed - 5, 10);
            }
            else if (gast->body.current_des == 1)
            {
                gast->body.vector->speed = std::min((int)gast->body.vector->speed + 10, 30);
                if (surplus_distance < 150)
                {
                    gast->gast_frame = std::max(gast->gast_frame - 1, 0);
                    gast->blast_frame = std::max(gast->blast_frame - 1, 0);
                    if (gast->blast_frame == 0)
                    {
                        gast->blast_visible = false;
                    }
                }
                else
                {
                    gast->gast_frame = std::min(gast->gast_frame + 1, 4);
                    gast->blast_frame = std::min(gast->blast_frame + 1, 3);
                }
            }
            if (check_arrive(&gast->body) && gast->body.current_des == 0)
            {
                remove(active_gasts.begin(), active_gasts.end(), gast);
                active_gasts.erase(active_gasts.end() - 1);
                delete gast;
            }
        }
        for (auto &gast : active_gasts)
        {
            switch (gast->direction)
            {
            case DOWN:
                point = 0;
                break;
            case UP:
                point = 1;
                break;
            case RIGHT:
                point = 2;
                break;
            case LEFT:
                point = 3;
                break;
            }
            SDL_RenderCopy(renderer, gast_texture[point], &gast->gast_slice_rect, &gast->body.rect);
            if (gast->blast_visible)
            {
                SDL_RenderCopy(renderer, blast_texture[point], &gast->blast_slice_rect, &gast->blast_des_rect);
            }
        }
        end = clock();
        if (60 - (end - start) > 0)
            SDL_Delay(60 - (end - start));
        SDL_RenderPresent(renderer);
    }
}

void init_textures(SDL_Renderer *renderer, SDL_Texture *gast_texture[], SDL_Texture *blast_texture[])
{
    SDL_Surface *gast_surface, *blast_surface;
    std::string gasts_images[4] = {{"sources\\GasterBlaster_activated_top.png"},
                                   {"sources\\GasterBlaster_activated_bottom.png"},
                                   {"sources\\GasterBlaster_activated_left.png"},
                                   {"sources\\GasterBlaster_activated_right.png"}};
    std::string blasts_images[4] = {
        {"sources\\top_blast.png"},
        {"sources\\bottom_blast.png"},
        {"sources\\left_blast.png"},
        {"sources\\right_blast.png"},
    };

    for (int i = 0; i < 4; i++)
    {
        gast_surface = IMG_Load(gasts_images[i].c_str());
        gast_texture[i] = SDL_CreateTextureFromSurface(renderer, gast_surface);
        SDL_FreeSurface(gast_surface);
    }
    for (int i = 0; i < 4; i++)
    {
        blast_surface = IMG_Load(blasts_images[i].c_str());
        blast_texture[i] = SDL_CreateTextureFromSurface(renderer, blast_surface);
        SDL_FreeSurface(blast_surface);
    }
}

void initialize_gasts(SDL_Renderer *renderer, GasterBlaster *gasts[], Settings *setting)
{
    SDL_Rect gast_initial_rects[4] = {{0, -1 * gast_slice_height, gast_slice_width, gast_slice_height},
                                      {setting->window_width - gast_slice_width, setting->window_height, gast_slice_width, gast_slice_height},
                                      {0, -1 * gast_slice_height, gast_slice_height, gast_slice_width},
                                      {setting->window_width - gast_slice_width, setting->window_height, gast_slice_height, gast_slice_width}};

    SDL_Point gasts_blast_destinations[4] = {{map_left, map_top - gast_slice_height},
                                             {map_left + map_size - gast_slice_width, map_top + map_size},
                                             {map_left - gast_slice_width, map_top},
                                             {map_left + map_size, map_top + map_size - gast_slice_height}};
    SDL_Point gasts_ending[4] = {
        {map_left, -1 * gast_slice_height},
        {map_left + map_size - gast_slice_width, setting->window_height},
        {-1 * gast_slice_width, map_top},
        {setting->window_width, map_top + map_size - gast_slice_height},
    };

    int directions[4] = {DOWN, UP, RIGHT, LEFT};

    for (int i = 0; i < 4; i++)
    {
        gasts[i] = (GasterBlaster *)malloc(sizeof(GasterBlaster));
        (gasts[i]->body).destinations[0] = gasts_blast_destinations[i];
        (gasts[i]->body).destinations[1] = gasts_ending[i];
        gasts[i]->body.rect = gast_initial_rects[i];
        gasts[i]->body.current_point.x = gast_initial_rects[i].x;
        gasts[i]->body.current_point.y = gast_initial_rects[i].y;
        gasts[i]->direction = directions[i],

        active_gasts.push_back(gasts[i]);
    }
    init_gasts(active_gasts);
}
/*initialize the gast before calling this function*/
/*
int update_gast_blast(GasterBlaster *gast)
{
    int distance;
    SDL_FPoint gast_current_point;

    gast_current_point = gast->get_current_point();
    distance = calculate_distance(gast->destinations[0], &gast_current_point);

    gast->update();
    if (gast->check_arrive() == 1)
    {

        
        return 1;
    }*/
/*calculate the distance*/ /*
    if (distance < 100)
    {
        gast->blast(1000, gast->blast_direction);
    }
    else if (distance > 150)
    {
        gast->die_down(1);
    }
    return 0;
}*/

float calculate_distance(SDL_FPoint *point_a, SDL_FPoint *point_b)
{
    float x_distance = point_a->x - point_b->x;
    float y_distance = point_a->y - point_b->y;

    return sqrt(pow(x_distance, 2) + pow(y_distance, 2));
}

float calculate_distance(SDL_Point *point_a, SDL_Point *point_b)
{
    float x_distance = point_a->x - point_b->x;
    float y_distance = point_a->y - point_b->y;

    return sqrt(pow(x_distance, 2) + pow(y_distance, 2));
}

float calculate_distance(SDL_Point *point_a, SDL_FPoint *point_b)
{
    float x_distance = point_a->x - point_b->x;
    float y_distance = point_a->y - point_b->y;

    return sqrt(pow(x_distance, 2) + pow(y_distance, 2));
}