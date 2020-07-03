#include "GasterBlaster.h"

/*frame count from zero*/
/*max_gast_frame is 5 , max_gast->blast_frame is 2*/

void init_gasts(std::vector<GasterBlaster *> &active_gasts)
{
    int i = 0;

    for (auto &&gast : active_gasts)
    {
        gast->gast_slice_rect.x = 0;
        gast->gast_slice_rect.y = 0;
        gast->blast_slice_rect.x = 0;
        gast->blast_slice_rect.y = 0;
        gast->body.current_des = 0;
        gast->body.vector = NULL;
        reorientate(&gast->body);
        gast->blast_frame = 2;
        gast->gast_frame = 0;
        gast->freeze_frame = 0;
        gast->blast_visible = false;
        if (gast->direction == UP || gast->direction == DOWN)
        {
            gast->gast_slice_rect.w = gast_slice_width;
            gast->gast_slice_rect.h = gast_slice_height;
        }
        else if (gast->direction == LEFT || gast->direction == RIGHT)
        {
            gast->gast_slice_rect.w = gast_slice_height;
            gast->gast_slice_rect.h = gast_slice_width;
        }
    }
}

void blast(GasterBlaster *gast, int blast_length)
{
    int blast_slice_diameter[max_blast_frame + 1] = {11, 22, 44, 66};
    int blast_slice_pos[max_blast_frame + 1] = {0, 11, 33, 77};

    if (gast->direction == UP || gast->direction == DOWN)
    {
        gast->blast_des_rect.w = blast_slice_diameter[gast->blast_frame];
        gast->blast_slice_rect.x = blast_slice_pos[gast->blast_frame];
        gast->blast_slice_rect.w = gast->blast_des_rect.w;
        gast->blast_slice_rect.h = 350;
        gast->blast_des_rect.h = blast_length;
    }
    else if (gast->direction == LEFT || gast->direction == RIGHT)
    {
        gast->blast_des_rect.h = blast_slice_diameter[gast->blast_frame];
        gast->blast_slice_rect.y = blast_slice_pos[gast->blast_frame];
        gast->blast_slice_rect.h = gast->blast_des_rect.h;
        gast->blast_slice_rect.w = 200;
        gast->blast_des_rect.w = blast_length;
    }
}

void update(std::vector<GasterBlaster *> &active_gasts)
{
    for (auto &&gast : active_gasts)
    {
        if (gast->freeze_frame == 0)
        {
            update(&gast->body);
            if (check_arrive(&gast->body) && gast->body.current_des == 0)
            {
                gast->body.current_des = (gast->body.current_des + 1) % 2; //rect->destinations.size();
                gast->freeze_frame = 3;
                reorientate(&gast->body);
            }
            if (gast->blast_visible)
            {
                
                if (gast->direction == UP || gast->direction == DOWN)
                {
                    gast->blast_des_rect.x = gast->body.rect.x + (gast->body.rect.w - gast->blast_des_rect.w) / 2;
                    if (gast->direction == UP)
                    {
                        gast->blast_des_rect.y = gast->body.rect.y - gast->blast_des_rect.h + gast->blast_frame * 5;
                    }
                    else
                    {
                        gast->blast_des_rect.y = gast->body.rect.y + gast->body.rect.h - gast->blast_frame * 5;
                    }

                    gast->gast_slice_rect.y = gast_slice_height * gast->gast_frame;
                }
                else
                {
                    gast->blast_des_rect.y = gast->body.rect.y + (gast->body.rect.h - gast->blast_des_rect.h) / 2;
                    if (gast->direction == LEFT)
                    {
                        gast->blast_des_rect.x = gast->body.rect.x - gast->blast_des_rect.w + gast->blast_frame * 5;
                    }
                    else
                    {
                        gast->blast_des_rect.x = gast->body.rect.x + gast->body.rect.w - gast->blast_frame * 5;
                    }

                    gast->gast_slice_rect.y = gast_slice_width * gast->gast_frame;
                }
            }
        }
        else 
        {
            gast->freeze_frame--;
            if (gast->freeze_frame == 0)
            {
                gast->blast_visible = true;
                blast(gast, 1000);
            }
        }
    }
}
/*


SDL_Surface *gast_surface, *blast_surface;

switch (point_direction)
{
case UP:
    point_direction = 0;
    break;
case DOWN:
    point_direction = 1;
    break;
case LEFT:
    point_direction = 2;
    break;
case RIGHT:
    point_direction = 3;
    break;
default:
    point_direction = 0;
    break;
}
blast_direction = point_direction;

SDL_FreeSurface(blast_surface);
SDL_FreeSurface(gast_surface);
}
    for (int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(blast_texture[i]);
        SDL_DestroyTexture(gast_texture[i]);
    }
}

for (int i = 0; i < 4; i++)
{
    gast_surface = IMG_Load(gast_image[i].c_str());
    blast_surface = IMG_Load(blast_image[i].c_str());
    if (!gast_surface || !blast_surface)
    {
        throw error_msgs[ERROR_ARGUMENT];
    }
    else
    {
        gast_texture[i] = SDL_CreateTextureFromSurface(renderer, gast_surface);
        blast_texture[i] = SDL_CreateTextureFromSurface(renderer, blast_surface);
        SDL_SetTextureBlendMode(blast_texture[i], SDL_BLENDMODE_BLEND);
    }
}
}
catch (const std::string msg)
{
    std::cerr << "GasterBlaster:" << msg << '\n';
}


if (blast_direction == UP || blast_direction == DOWN)
    {
        gast->blast_slice_rect.h = blast_surface->h;
        gast->gast_slice_rect.w = gast_surface->w;
        gast->gast_slice_rect.h = gast_slice_height;
    }
    else
    {
        gast->blast_slice_rect.w = blast_surface->w;
        gast->gast_slice_rect.w = gast_surface->w;
        gast->gast_slice_rect.h = gast_slice_width;
    }*/