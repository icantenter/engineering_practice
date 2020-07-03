#include "MoveableRect.h"

void reorientate(MOVEABLERECT *rect)
{
    SDL_Point temp{rect->rect.x, rect->rect.y};
    if (rect->vector)
    {
        free(rect->vector);
    }
    rect->vector = create_vector(&temp, &rect->destinations[rect->current_des], 25);
}

int update(MOVEABLERECT *rect)
{
    move_point(rect->vector, &rect->current_point, &rect->destinations[rect->current_des]);
    rect->rect.x = rect->current_point.x;
    rect->rect.y = rect->current_point.y;
    
    return 0;
}

double get_surplus_distance(MOVEABLERECT *rect)
{
    SDL_Point current_destination = rect->destinations[rect->current_des];

    float x_distance = current_destination.x - rect->current_point.x;
    float y_distance = current_destination.y - rect->current_point.y;

    return sqrt(pow(x_distance, 2) + pow(y_distance, 2));

}

bool check_arrive(MOVEABLERECT *rect)
{
    SDL_Point current_destination = rect->destinations[rect->current_des];

    float x_distance = current_destination.x - rect->current_point.x;
    float y_distance = current_destination.y - rect->current_point.y;

    if (x_distance == 0  && y_distance == 0)
    {
        return true;
    }
    return false;
}

/*
if (check_arrive(rect))
    {
        rect->current_des = (rect->current_des + 1) % rect->destinations.size();
        reorientate(rect);
    }*/