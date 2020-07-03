#include "Data.h"


/**
*@File: Data.cpp
*@Description: 存放查找模块的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
extern bool logged;
extern Player *logged_player;


/* ************************************************
  Function:init_textures()     // 函数名称
  Description:读取图片后，转化为surface,再转化为texture    // 函数功能、性能等的描述
  Input:void // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void        // 函数返回值的说明
  Others:         // 其它说明
************************************************ */
void init_textures(SDL_Renderer *renderer, std::vector<SDL_Texture *>& 
    exit_button_textures)
{
    SDL_Surface *button_surface;
    const std::string exit_button_images[2] = {
        {"sources\\exit_button_up.png"},
        {"sources\\exit_button_down.png"},
    };

    for (int i = 0; i < 2; i++)
    {
        button_surface = IMG_Load(exit_button_images[i].c_str());
        exit_button_textures.push_back(SDL_CreateTextureFromSurface(renderer, 
            button_surface));
        SDL_FreeSurface(button_surface);
    }
}

/*************************************************
  Function:search_data()     // 函数名称
  Description:查找用户的信息，并渲染在渲染器上    // 函数功能、性能等的描述
  Input:渲染器，DataBase的类指针，Settings的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否登录        // 函数返回值的说明
  Others:void         // 其它说明
*************************************************/
int search_data(SDL_Renderer *renderer, DataBase *players, Settings *setting)
{
    bool active = true;
    SDL_Event event;
    std::vector<int> in_msgs, external_msgs;
    SDL_Color button_text_color = {250, 250, 250};
    Button *exit_button;
    SDL_Rect button_rect{setting->window_width - 300, 30, 100, 100};
    SDL_Rect text_rect;
    std::vector<SDL_Texture *> exit_button_textures;
    init_textures(renderer, exit_button_textures);
    exit_button = new Button(&button_rect, renderer, exit_button_textures);
    PLAYER *head;
    int ranking;

    if (!logged)
    {
        return 1;
    }
    head = players->sort(ACCORDING_HIGHEST_SCORE, false);
    for (ranking = 1; head; ranking++)
    {
        if (head == logged_player)
        {
            break;
        }
        head = head->next;
    }
    std::string texts[5] = {"name:   ",
                            "number:   " + std::to_string(logged_player->number),
                            "time:   " + std::to_string(logged_player->time),
                            "high_score:   " + std::to_string(logged_player->high_score),
                            "ranking:   " + std::to_string(ranking)};
    texts[0] = texts[0] + logged_player->account.name;
    Text *Texts[5];
    for (int i = 0; i < 5; i++)
    {
        Texts[i] = new Text(renderer, texts[i], button_text_color);
    }
    while (active)
    {
        if (SDL_PollEvent(&event))
        {
            exit_button->update(&event, external_msgs);
            in_msgs = exit_button->get_msgs();
            {
                for (auto &&msg : in_msgs)
                {
                    if (msg == Button_activated)
                    {
                        active = false;
                    }
                }
            }
        }
        text_rect = {300, 300, 200, 100};
        for (int i = 0; i < 5; i++)
        {
            Texts[i]->draw(&text_rect);
            text_rect.y += 80;
        }
        exit_button->draw();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        SDL_RenderClear(renderer);
    }
    for (int i = 0; i < 5; i++) 
    {
        delete Texts[i];
    }
    delete exit_button;
    return 0;
}
