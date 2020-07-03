#include "Apple.h"
/**
*@File: Apple.cpp
*@Description: 存放苹果类的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
/*************************************************
  Function:构造函数       函数名称
  Description:创建实例时调用的函数     函数功能、性能等的描述
  Input:渲染器，苹果的des_rect  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
Apple::Apple(SDL_Renderer *renderer, SDL_Rect *apple_rect)
{
    this->renderer = renderer;
    this->rect = *apple_rect;
}


/*************************************************
  Function:reset_apple()       函数名称
  Description:重置苹果位置     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
void Apple::reset_apple()
{
    this->rect.y = (rand() % (map_size / this->rect.h)) * this->rect.h + map_top;
    this->rect.x = (rand() % (map_size / this->rect.w)) * this->rect.w + map_left;
}
SDL_Rect Apple::get_rect()
{
    return this->rect;
}


/*************************************************
  Function:draw()       函数名称
  Description:在渲染器上画出苹果     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
void Apple::draw()
{
    SDL_SetRenderDrawColor(this->renderer, this->rect_color.r, this->rect_color.g,
                           this->rect_color.b, this->rect_color.a);
    SDL_RenderFillRect(this->renderer, &this->rect);
    SDL_SetRenderDrawColor(this->renderer, 200, 200, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(this->renderer, &this->rect);
}


/*************************************************
  Function:析构函数       函数名称
  Description:删除实例时调用的函数     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
Apple::~Apple()
{
}