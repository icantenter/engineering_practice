#include "menu.h"
#include "Button.h"
#include "Arrow.h"
//#include "Egg.cpp"
#include "Text.h"
#include "animation.h"

/**
*@File: menu.cpp
*@Description: 存放菜单模块的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
int arrow_points = PLAY;
extern bool logged;
/*************************************************
  Function:init_menu_property()      // 函数名称
  Description:初始化按钮，按钮的所有纹理，初始化箭头    // 函数功能、性能等的描述
  Input:渲染器，按钮的类指针数组，按钮纹理的vector, 箭头的类指针，Settings的类指针，箭头的运功范围 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void        // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
void init_menu_property(SDL_Renderer *renderer, MenuButton *menu_buttons[],
                        std::vector<SDL_Texture *> button_textures,
                        Arrow *left_arrow, Settings *setting, SDL_Point points[])
{
    SDL_Surface *button_surface;
    SDL_Rect rect;
    SDL_Color menu_button_text_color = {250, 250, 250};
    std::string menu_button_images[4] = {{"sources\\menu_button_nonactivated.png"},
                                         {"sources\\menu_button_activated.png"},
                                         {"sources\\menu_button_overlap.png"},
                                         {"sources\\menu_button_locked.png"}};
    for (int i = 0; i < 4; i++)
    {
        button_surface = IMG_Load(menu_button_images[i].c_str());
        button_textures.push_back(SDL_CreateTextureFromSurface(renderer, button_surface));
    }
    SDL_FreeSurface(button_surface);

    rect.y = setting->window_height / 2;
    rect.w = 140;
    rect.h = 140;
    for (int i = PLAY; i < button_count; i++)
    {
        rect.x = i * 230 + 155;
        MenuButton *new_button = new MenuButton(&rect, renderer, button_text[i], button_textures, menu_button_text_color);
        menu_buttons[i] = new_button;
    }

    left_arrow->arrow_rect.w = 30;
    left_arrow->arrow_rect.h = 30;
}

/*************************************************
  Function:update_arrow()      // 函数名称
  Description:变更箭头的指向    // 函数功能、性能等的描述
  Input:按钮的类指针数组, 箭头的类指针，箭头的运功范围，箭头变更指向时切换的幅度 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void        // 函数返回值的说明
  Others:会更新箭头运动范围        // 其它说明
*************************************************/
void update_arrow(MenuButton *menu_buttons[], Arrow *left_arrow, SDL_Point points[],
                  int move_scale)
{
    arrow_points += move_scale;
    for (int i = 1; i >= 0; i--)
    {
        points[i] = {menu_buttons[arrow_points]->rect.x - i * 25 - left_arrow->arrow_rect.w - 10,
                     menu_buttons[arrow_points]->rect.y + menu_buttons[arrow_points]->rect.h / 2};
    }
    left_arrow->arrow_rect.x = points[0].x;
    left_arrow->arrow_rect.y = points[0].y;
    left_arrow->x = points[0].x;
    left_arrow->y = points[0].y;
}

/*************************************************
  Function:draw_menu()      // 函数名称
  Description:画出菜单上的所有物体    // 函数功能、性能等的描述
  Input:渲染器，按钮的类指针数组, Settings的类指针，箭头的运功范围，箭头的类指针
    ，背景的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void        // 函数返回值的说明
  Others:背景也是一个按钮        // 其它说明
*************************************************/
void draw_menu(SDL_Renderer *renderer, MenuButton *menu_buttons[],
               Settings *setting, SDL_Point points[3], Arrow *left_arrow, Button *background)
{
    Text title{renderer, "Greedy Snake", {150, 150, 150}};
    SDL_Rect title_rect{setting->window_width / 2 - 250,
                        setting->window_height / 2 - 300, 500, 200};

    SDL_RenderClear(renderer);
    background->draw();
    title.draw(&title_rect);
    for (int i = PLAY; i < button_count; i++)
    {
        menu_buttons[i]->draw();
    }
    left_arrow->update(points, 1);
    left_arrow->draw();
}

/*************************************************
  Function:get_player_requests()      // 函数名称
  Description:检测键盘事件，并更新按钮和箭头    // 函数功能、性能等的描述
  Input:渲染器，事件，按钮的类指针数组，箭头的类指针,箭头的运功范围，背景的类指针
    ，背景的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:返回用户请求        // 函数返回值的说明
  Others:背景也是一个按钮        // 其它说明
*************************************************/
int get_player_requests(SDL_Renderer *renderer, SDL_Event *event,
                        MenuButton *menu_buttons[], Arrow *left_arrow, SDL_Point points[],
                        Button *background)
{
    std::vector<int> out_msgs;
    std::vector<int> in_msgs;
    int request = INVALID_REQUEST;
    if (event->type == SDL_QUIT)
    {
        request = QUIT;
    }
    else if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_q:
            request = QUIT;
            break;
        case SDLK_p:
            request = PLAY;
            break;
        case SDLK_LEFT:
            if (arrow_points > 0)
            {
                update_arrow(menu_buttons, left_arrow, points, -1);
            }
            break;
        case SDLK_RIGHT:
            if (arrow_points < button_count - 1)
            {
                update_arrow(menu_buttons, left_arrow, points, 1);
            }
            break;
        case SDLK_RETURN:
            request = arrow_points;
            break;
        }
    }

    for (int i = 0; i < button_count; i++)
    {
        if (logged == false && (i == 0 || i == 2))
        {
            in_msgs.push_back(Button_locked);
        }
        menu_buttons[i]->update(event, in_msgs);
        in_msgs.clear();
        out_msgs = menu_buttons[i]->get_msgs();
        for (auto &&msg : out_msgs)
        {
            if (msg == Button_activated)
            {
                return i;
            }
        }
    }

    return request;
}

/*************************************************
  Function: menu()      // 函数名称
  Description:菜单主体    // 函数功能、性能等的描述
  Input:渲染器，Settings的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:返回用户的有效请求        // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
int menu(SDL_Renderer *renderer, Settings *setting)
{
    std::vector<SDL_Texture *> button_textures;
    std::vector<SDL_Texture *> background_textures;
    MenuButton *menu_buttons[4];
    SDL_Rect rect;

    std::string arrow_image = "sources\\arrow_left.bmp";
    Arrow *left_arrow = new Arrow(&rect, renderer, arrow_image);
    SDL_Point arrow_points[2];

    std::string background_image = "sources\\background.png";
    SDL_Surface *background_surface = IMG_Load(background_image.c_str());
    background_textures.push_back(SDL_CreateTextureFromSurface(renderer, background_surface));
    SDL_FreeSurface(background_surface);
    SDL_Rect background_rect{0, 0, setting->window_width, setting->window_height};

    Button *background = new Button(&background_rect, renderer, background_textures);

    SDL_Event event;
    int request;

    init_menu_property(renderer, menu_buttons, button_textures, left_arrow, 
        setting, arrow_points);
    update_arrow(menu_buttons, left_arrow, arrow_points, 0);

    while (1)
    {
        if (SDL_PollEvent(&event))
        {
            if ((request =
                     get_player_requests(renderer, &event,
                                         menu_buttons, left_arrow,
                                         arrow_points, background)) != INVALID_REQUEST)
            {
                menu_buttons[request]->draw();
                SDL_RenderPresent(renderer);
                fade_out(renderer, setting);
                for (auto &&texture : button_textures)
                {
                    SDL_DestroyTexture(texture);
                }
                for (auto &&texture : background_textures)
                {
                    SDL_DestroyTexture(texture);
                }

                for (int i = 0; i < 4; i++)
                {
                    delete menu_buttons[i];
                }

                delete left_arrow;
                delete background;
                return request;
            }
        }
        draw_menu(renderer, menu_buttons, setting, arrow_points, left_arrow, background);
        SDL_RenderPresent(renderer);
        SDL_Delay(80.00);
    }
}
