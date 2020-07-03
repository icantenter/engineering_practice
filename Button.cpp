#include "Button.h"

/**
*@File: Button.cpp
*@Description: 存放button类的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/

/*************************************************
  Function:访问器       函数名称
  Description:返回外部可以访问的消息     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:存放消息的vector         函数返回值的说明
  Others:void          其它说明
*************************************************/
std::vector<int> Button::get_msgs()
{
    return this->out_msgs;
}


/*************************************************
  Function:更新按钮       函数名称
  Description:检测鼠标点击和重叠     函数功能、性能等的描述
  Input:事件，特定的消息  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
void Button::update(SDL_Event *event, std::vector<int> &external_msgs)
{
    this->in_msgs.clear();
    this->out_msgs.clear();
    int x = event->motion.x;
    int y = event->motion.y;
    if (x > this->rect.x && x < this->rect.x + this->rect.w && y > this->rect.y 
      && y < this->rect.y + this->rect.h)
    {
        if (event->type == SDL_MOUSEBUTTONDOWN)
        {
            out_msgs.push_back(Button_activated);
            in_msgs.push_back(Button_mouse_click);
        }
        else
        {
            out_msgs.push_back(Button_mouse_overlap);
            in_msgs.push_back(Button_mouse_overlap);
        }
    }
}

/*************************************************
  Function:构造函数       函数名称
  Description:创建实例时调用的函数     函数功能、性能等的描述
  Input:按钮的des_rect，渲染器，按钮的所有纹理  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
Button::Button(SDL_Rect *rect, SDL_Renderer *renderer, std::vector<SDL_Texture *> 
  button_textures)
{
    this->rect = *rect;
    this->renderer = renderer;
    this->button_textures = button_textures;
}


/*************************************************
  Function:draw()       函数名称
  Description:在渲染器上画出按钮     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:无意义的整数         函数返回值的说明
  Others:这个东西没有抽象好，不要参考          其它说明
*************************************************/
int Button::draw()
{
    for (auto &&msg : this->in_msgs)
    {
        if (msg > 0 && msg < int(button_textures.size()) && button_textures[msg])
        {
            SDL_RenderCopy(this->renderer, button_textures[msg], NULL, &this->rect);
            return 0;
        }
    }
    SDL_RenderCopy(this->renderer, button_textures[0], NULL, &this->rect);
    return 0;
}


/*************************************************
  Function:析构函数       函数名称
  Description:删除实例时调用的函数     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:          其它说明
*************************************************/
Button::~Button()
{
}

/*************************************************
  Function:构造函数       函数名称
  Description:创建实例时调用的函数     函数功能、性能等的描述
  Input:按钮的des_rect，渲染器，按钮上的文本，按钮的所有纹理，字体颜色  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
MenuButton::MenuButton(SDL_Rect *rect, SDL_Renderer *renderer, const std::string &text,
                        std::vector<SDL_Texture *> button_textures, SDL_Color text_color = {50, 50, 50, 255})
    : Button(rect, renderer, button_textures)
{
    this->text_color = text_color;
    this->text = text;
    TTF_Font *font = TTF_OpenFont(this->typeface.c_str(), 16);
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, this->text.c_str(), 
      this->text_color);
    this->text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    this->text_rect.w = rect->w / 2;
    this->text_rect.h = rect->h - 10;
    this->text_rect.y = rect->y - 20;
    this->text_rect.x = rect->x + 40;
    TTF_CloseFont(font);
    SDL_FreeSurface(text_surface);
}

/*************************************************
  Function:访问器       函数名称
  Description:设置文本的des_rect     函数功能、性能等的描述
  Input:文本的des_rect  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
void MenuButton::set_text_rect(SDL_Rect *text_rect)
{
    this->text_rect = *text_rect;
}

/*************************************************
  Function:reset_text()       函数名称
  Description:重置文本     函数功能、性能等的描述
  Input:重置的文本  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
void MenuButton::reset_text(const std::string &text)
{
    this->text = text;
    TTF_Font *font = TTF_OpenFont(this->typeface.c_str(), 16);
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, 
      this->text.c_str(), this->text_color);
    this->text_texture = SDL_CreateTextureFromSurface(this->renderer, text_surface);
    TTF_CloseFont(font);
    SDL_FreeSurface(text_surface);
}


/*************************************************
  Function:draw()       函数名称
  Description:在渲染器上画出按钮     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:无意义的整数         函数返回值的说明
  Others:这个东西没有抽象好，不要参考          其它说明
*************************************************/
int MenuButton::draw()
{
    for (auto &&msg : this->in_msgs)
    {
        if (msg > 0 && msg < int(button_textures.size()) && button_textures[msg])
        {
            SDL_RenderCopy(this->renderer, button_textures[msg], NULL, &this->rect);
            SDL_RenderCopy(this->renderer, text_texture, NULL, &this->text_rect);
            return 0;
        }
    }
    SDL_RenderCopy(this->renderer, button_textures[0], NULL, &this->rect);
    SDL_RenderCopy(this->renderer, text_texture, NULL, &this->text_rect);
    return 0;
}



/*************************************************
  Function:析构函数       函数名称
  Description:删除实例时调用的函数     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:          其它说明
*************************************************/
MenuButton::~MenuButton()
{
}