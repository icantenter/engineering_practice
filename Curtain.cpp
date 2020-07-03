#include "Curtain.h"
/**
*@File: Curtain.cpp
*@Description: 存放Curtain类的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/

/*************************************************
  Function:构造函数       函数名称
  Description:创造实例时调用的函数     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void         其它说明
*************************************************/
Curtain::Curtain(SDL_Renderer *renderer, SDL_Rect *des_rect)
{
    this->renderer = renderer;
    this->curtain_rect = *des_rect;
    SDL_Surface *curtain_surface = IMG_Load(curtain_image.c_str());
    curtain_texture = SDL_CreateTextureFromSurface(renderer, curtain_surface);
    SDL_SetTextureBlendMode(curtain_texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(curtain_surface);
}

/*************************************************
  Function:析构函数       函数名称
  Description:删除实例时调用的函数     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void         其它说明
*************************************************/
Curtain::~Curtain()
{
    SDL_DestroyTexture(this->curtain_texture);
}

/*************************************************
  Function:访问器       函数名称
  Description:访问私有属性     函数功能、性能等的描述
  Input:将要重置的des_rect  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void         其它说明
*************************************************/
void Curtain::set_rect(SDL_Rect *des_rect)
{
    this->curtain_rect = *des_rect;
}

/*************************************************
  Function:访问器       函数名称
  Description:访问私有属性     函数功能、性能等的描述
  Input:重置的透明度  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void         其它说明
*************************************************/
void Curtain::set_alpha(int alpha)
{
    this->alpha = std::max(alpha, 0);
    SDL_SetTextureAlphaMod(this->curtain_texture, alpha);
}

/*************************************************
  Function:draw()       函数名称
  Description:画出幕布     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void         其它说明
*************************************************/
void Curtain::draw()
{
    SDL_RenderCopy(this->renderer, this->curtain_texture, NULL, &this->curtain_rect);
}
