#include "animation.h"
/*
*@File: animation.cpp
*@Description: 存放用于动画效果的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/

/*
  Function: fade_out()       函数名称
  Description:渐隐效果     函数功能、性能等的描述
  Input:渲染器，Settings的类指针 输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void        函数返回值的说明
  Others:void        其它说明
*/
void fade_out(SDL_Renderer *renderer, Settings *setting)
{
    int alpha = 0;
    SDL_Rect des_rect{0, 0, setting->window_width, setting->window_height};
    Curtain *window_curtain = new Curtain(renderer, &des_rect);
    while (alpha <= 255)
    {
        window_curtain->draw();
        SDL_RenderPresent(renderer);
        SDL_Delay(100.00);
        alpha += 50;
        window_curtain->set_alpha(alpha);
    }
    delete window_curtain;
}
