#include "Vector.h"
VECTOR *create_vector(SDL_Point *init_point, SDL_Point *des_point, float speed)
{
    float total_distance;

    //勾股定理
    total_distance = sqrt(pow(init_point->x - des_point->x, 2) + pow(init_point->y - des_point->y, 2));
    if (total_distance == 0)
    {
        return NULL;
    }
    VECTOR *create_vector = (VECTOR *)malloc(sizeof(VECTOR));
    create_vector->speed = speed;

    create_vector->x_vector = (des_point->x - init_point->x) / total_distance;
    create_vector->y_vector = (des_point->y - init_point->y) / total_distance;

    return create_vector;
}
bool check_syntropy(float a, float b)
{
    return (a < 0 && b < 0) || (a > 0 && b > 0);
}

int move_point(VECTOR *vector, SDL_FPoint *move_point, SDL_Point *border_point)
{
    float x_distance, y_distance;
    if (!vector)
    {
        return 1;
    }

    move_point->x += vector->x_vector * vector->speed;
    move_point->y += vector->y_vector * vector->speed;
    if (border_point)
    {
        x_distance = border_point->x - move_point->x;
        y_distance = border_point->y - move_point->y;
        if (!check_syntropy(x_distance, vector->x_vector))
        {
            move_point->x = border_point->x;
        }
        if (!check_syntropy(x_distance, vector->x_vector))
        {
            move_point->y = border_point->y;
        }
    }

    return 0;
}