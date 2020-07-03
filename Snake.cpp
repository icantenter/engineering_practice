#include "Snake.h"

/**
*@File: Snake.cpp
*@Description: 存放Snake类的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/

/*************************************************
  Function: 构造函数      // 函数名称
  Description:创建实例时调用的函数    // 函数功能、性能等的描述
  Input:渲染器，蛇头的des_rect // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
Snake::Snake(SDL_Renderer *renderer, SDL_Rect *head_rect)
{
    this->renderer = renderer;
    this->block_width = head_rect->w;
    this->block_height = head_rect->h;
    this->head = (SNAKEBLOCK *)malloc(sizeof(SNAKEBLOCK));
    this->head->rect = *head_rect;
    this->head->rect_color = {50, 50, 50, 255};
    this->head->next = NULL;
}
/*访问器*/
int Snake::get_length()
{
    return this->length;
}
/*访问器*/
int Snake::get_direction()
{
    return this->direction;
}

/*************************************************
  Function: update()      // 函数名称
  Description:更新蛇    // 函数功能、性能等的描述
  Input:玩家的命令方向 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:会判断命令是否有效        // 其它说明
*************************************************/
void Snake::update(int direction)
{
    SNAKEBLOCK *new_head;
    SNAKEBLOCK *previous = this->head, *next = this->head->next;

    if (this->direction != direction * -1 && direction != DIRECTIONLESS)
    {
        this->direction = direction % 3;
    }
    if (this->direction != DIRECTIONLESS)
    {
        new_head = (SNAKEBLOCK *)malloc(sizeof(SNAKEBLOCK));
        new_head->rect = this->head->rect;
        new_head->rect_color = {50, 50, 50, 255};
        new_head->next = this->head;
        this->head = new_head;
        switch (this->direction)
        {
        case UP:
            (this->head)->rect.y -= this->block_height;
            break;
        case DOWN:
            (this->head)->rect.y += this->block_height;
            break;
        case LEFT:
            (this->head)->rect.x -= this->block_width;
            break;
        case RIGHT:
            (this->head)->rect.x += this->block_width;
            break;
        }
        if (next == NULL)
            grow_direction = -1 * this->direction;
        while (next)
        {
            if (next->next == NULL)
            {
                if (next->rect.x - previous->rect.x != 0)
                {
                    this->grow_direction = (next->rect.x - previous->rect.x) 
                        / abs(next->rect.x - previous->rect.x);
                }
                else
                {
                    this->grow_direction = 2 * (next->rect.y - previous->rect.y) 
                        / abs(next->rect.y - previous->rect.y);
                }
                previous->next = NULL;
                delete next;
                break;
            }
            previous = next;
            next = next->next;
        }
    }
}


/*************************************************
  Function: draw()      // 函数名称
  Description:画出蛇的所有方块    // 函数功能、性能等的描述
  Input: // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
void Snake::draw()
{
    SNAKEBLOCK *temp = head;
    while (temp)
    {
        SDL_SetRenderDrawColor(this->renderer, temp->rect_color.r, temp->rect_color.g,
                               temp->rect_color.b, temp->rect_color.a);
        SDL_RenderFillRect(this->renderer, &temp->rect);
        SDL_SetRenderDrawColor(this->renderer, 200, 200, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(this->renderer, &temp->rect);
        temp = temp->next;
    }
}
/*************************************************
  Function: check_self_collide()      // 函数名称
  Description:检测头是否与蛇身碰撞    // 函数功能、性能等的描述
  Input:void// 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否碰撞的真假值       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
bool Snake::check_self_collide()
{
    SNAKEBLOCK *temp = this->head->next;
    for (int i = 2; i <= this->length; i++)
    {
        if (temp)
        {
            if (i > 3)
            {
                if (collide(&head->rect, &temp->rect))
                {
                    return true;
                }
            }
            temp = temp->next;
        }
    }
    return false;
}

/*************************************************
  Function: check_head_collide()      // 函数名称
  Description:检测头是否与外部矩形碰撞    // 函数功能、性能等的描述
  Input:外部矩形的结构体指针// 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否碰撞的真假值       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
bool Snake::check_head_collide(SDL_Rect *detecting_rect)
{
    if (collide(detecting_rect, &this->head->rect))
    {
        return true;
    }
    return false;
}

/*************************************************
  Function: check_collides()      // 函数名称
  Description:检测蛇的所有方块是否与外部矩形碰撞    // 函数功能、性能等的描述
  Input:外部矩形的结构体指针// 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否碰撞的真假值       // 函数返回值的说明
  Others:重载        // 其它说明
*************************************************/
bool Snake::check_collides(SDL_Rect *detecting_rect)
{
    SNAKEBLOCK *temp = this->head;

    while (temp)
    {
        if (collide(&temp->rect, detecting_rect))
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/*************************************************
  Function: change_color()      // 函数名称
  Description:改变颜色    // 函数功能、性能等的描述
  Input:void// 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
void Snake::change_color()
{
    
    this->head->rect_color.r = rand() % 205 + 50;
    this->head->rect_color.g = rand() % 205 + 50;
    this->head->rect_color.b = rand() % 205 + 50;
    
}

/*************************************************
  Function: check_collides()      // 函数名称
  Description:检测蛇的所有方块是否与外部一堆矩形碰撞    // 函数功能、性能等的描述
  Input:外部一堆矩形的vector// 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:发生碰撞的外部矩形的副本       // 函数返回值的说明
  Others:重载        // 其它说明
*************************************************/
std::vector<SDL_Rect *> Snake::check_collides(std::vector<SDL_Rect *>& detecting_rects)
{
    std::vector<SDL_Rect *> hit_rects;

    SNAKEBLOCK *temp = this->head;

    while (temp)
    {
        for (auto &&rect : detecting_rects)
        {
            if (collide(&temp->rect, rect))
            {
                remove(detecting_rects.begin(), detecting_rects.end(), rect);
                detecting_rects.erase(detecting_rects.end() - 1);
                hit_rects.push_back(rect);
            }
        }
        temp = temp->next;
    }
    return hit_rects;
}

/*************************************************
  Function: grow()      // 函数名称
  Description:使蛇生长    // 函数功能、性能等的描述
  Input:生长的长度和方向// 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:生长是否成功       // 函数返回值的说明
  Others:需要初始化，蛇动后之后会忽略第二个参数        // 其它说明
*************************************************/
bool Snake::grow(int length, int direction)
{
    SDL_Rect temp_rect;
    SNAKEBLOCK *temp = this->head;

    if (length < 0)
    {
        return false;
    }
    if (this->grow_direction == DIRECTIONLESS && direction == DIRECTIONLESS)
    {
        return false;
    }
    else if (this->grow_direction == DIRECTIONLESS)
    {
        this->grow_direction = direction % 3;
    }
    this->length += length;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp_rect = temp->rect;

    for (int i = 0; i < length; i++)
    {
        switch (this->grow_direction)
        {
        case UP:
            temp_rect.y -= this->block_height;
            break;
        case DOWN:
            temp_rect.y += this->block_height;
            break;
        case RIGHT:
            temp_rect.x += this->block_width;
            break;
        case LEFT:
            temp_rect.x -= this->block_width;
            break;
        }
        temp->next = (SNAKEBLOCK *)malloc(sizeof(SNAKEBLOCK));
        temp = temp->next;
        temp->rect = temp_rect;
        temp->rect_color = {50, 50, 50, 255};
    }

    temp->next = NULL;

    return true;
}

/*************************************************
  Function: 析构函数      // 函数名称
  Description:删除实例时调用的函数    // 函数功能、性能等的描述
  Input:void// 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:会释放所有空间        // 其它说明
*************************************************/
Snake::~Snake()
{
    SNAKEBLOCK *prev = this->head, *next;
    while (prev)
    {
        next = prev->next;
        free(prev);
        prev = next;
    }
    
}