#pragma once
#include "MoveableRect.h"
#include "direction.h"
#include "error.h"

//the GasterBlaster's width is 88, and the height is 114
//there are six pictures
const int blast_slice_length = 300;
const int gast_slice_width = 88;
const int gast_slice_height = 114; //正放
const int max_gast_frame = 5;
const int max_blast_frame = 3;

typedef struct
{
    MOVEABLERECT body;
    SDL_Rect gast_slice_rect, blast_slice_rect;
    SDL_Rect blast_des_rect;
    int blast_alpha;
    int gast_frame, blast_frame, freeze_frame;
    int direction;
    bool blast_visible;
} GasterBlaster;


void update(std::vector<GasterBlaster *> &active_gasts);
void init_gasts(std::vector<GasterBlaster *> &active_gasts);
void blast(GasterBlaster *gast, int blast_length);
