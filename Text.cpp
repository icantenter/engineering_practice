#include "Text.h"

/**
*@File: Text.cpp
*@Description: 存放Text类的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/


Text::Text(SDL_Renderer *renderer, const std::string text, SDL_Color text_color)
{
    this->text_color = text_color;
    this->text = text;
    this->renderer = renderer;
    TTF_Font *font;
    SDL_Surface *text_surface;
    font = TTF_OpenFont("typeface\\technology.ttf", 16);
    text_surface = TTF_RenderText_Blended(font, this->text.c_str(), this->text_color);
    TTF_CloseFont(font);
    this->text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    SDL_FreeSurface(text_surface);
}

void Text::draw(SDL_Rect *text_rect)
{
    SDL_RenderCopy(this->renderer, this->text_texture, NULL, text_rect);
}
/*************************************************
  Function:reset_text()       函数名称
  Description:重置文本     函数功能、性能等的描述
  Input:将要重置的文本  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void         其它说明
*************************************************/
void Text::reset_text(const std::string &text)
{
    TTF_Font *font = TTF_OpenFont("typeface\\technology.ttf", 16);
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, 
        text.c_str(), this->text_color);
    this->text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    TTF_CloseFont(font);
    SDL_FreeSurface(text_surface);
}

Text::~Text()
{
    SDL_DestroyTexture(text_texture);
}
