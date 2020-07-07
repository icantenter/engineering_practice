#include "function.h"
/**
*@File: function.cpp
*@Description: 存放碰撞检测的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
/* ************************************************
  Function:collide()       函数名称
  Description:判断两个矩形是否碰撞    函数功能、性能等的描述
  Input:第个矩形，第二个矩形  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:是否碰撞的bool值         函数返回值的说明
  Others:重载          其它说明
************************************************ */
bool collide(SDL_Rect *rect_a, SDL_Rect *rect_b)
{
    return rect_a->x + rect_a->w > rect_b->x &&
           rect_a->x < rect_b->x + rect_b->w &&
           rect_a->y + rect_a->h > rect_b->y &&
           rect_a->y < rect_b->y + rect_b->h;
}


/*************************************************
  Function:collide()       函数名称
  Description:判断一个矩形是否和一堆矩形中至少一个矩形碰撞     函数功能、性能等的描述
  Input:一堆矩形的vector，一个矩形  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:是否碰撞的bool值         函数返回值的说明
  Others:重载          其它说明
*************************************************/
bool collide(std::vector<SDL_Rect> rects, SDL_Rect *rect_b)
{
    for (auto &&rect_a : rects)
    {
        if (collide(&rect_a, rect_b))
        {
            return true;
        }
    }
    return false;
}
