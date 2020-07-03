#include "register.h"
#include "Button.h"
#include "Text.h"

/**
*@File: register.cpp
*@Description: 用于存放登录和注册模块的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
/*代表是否登录，值只能为真假*/
bool logged = false;
/*登录的玩家信息的类指针，需先登录后才赋有效的值*/
PLAYER *logged_player;

void manage_account(SDL_Renderer *renderer)
{
}

/*************************************************
  Function: check_password()      // 函数名称
  Description:检测登录时，如果有账号，密码的正确性    // 函数功能、性能等的描述
  Input:名字，密码，DataBase的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否能登录的bool值       // 函数返回值的说明
  Others:账号不存在和密码错误都返回false        // 其它说明
*************************************************/
bool check_password(const std::string &name, const std::string &password, DataBase *players)
{
    int index;
    Player *find_player;

    index = players->find(name, DATA_BEGIN);
    if (index != NOT_FIND)
    {
        find_player = players->get_player(index);
        if (find_player->account.password == password)
        {
            logged_player = find_player;
            logged = true;

            return true;
        }
    }

    return false;
}

/*************************************************
  Function: check_name()      // 函数名称
  Description:检测注册时，是否重名    // 函数功能、性能等的描述
  Input:名字，密码，DataBase的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否能注册的bool值       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
bool check_name(const std::string &name, const std::string &password, DataBase *players)
{
    int index;

    index = players->find(name, DATA_BEGIN);
    if (index == NOT_FIND)
    {
        ACCOUNT new_player;
        strcpy_s(new_player.name, name.c_str());
        strcpy_s(new_player.password, password.c_str());
        players->push_back(&new_player);
        index = players->find(name, DATA_BEGIN);
        logged_player = players->get_player(index);
        logged = true;

        return true;
    }

    return false;
}

/*************************************************
  Function: check_account()      // 函数名称
  Description:处理用户请求    // 函数功能、性能等的描述
  Input:渲染器，Settings的类指针，DataBase的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
void check_account(SDL_Renderer *renderer, Settings *setting, DataBase *players)
{
    bool active = true;
    int flag = -1;
    int command = 2;
    char *composition;

    std::vector<int> external_msgs, in_msgs;
    char temp_account[2][120];
    temp_account[0][0] = '\0';
    temp_account[1][0] = '\0';
    std::string account[2];
    SDL_Event event;
    SDL_Rect rect{400, 400, 200, 30};
    SDL_Rect text_rect;
    SDL_Color log_button_text_color = {250, 250, 250};
    MenuButton *buttons[4];
    Button *exit_button, *enter_button;
    SDL_Texture *background_texture = NULL;
    std::vector<SDL_Texture *> log_button_textures, exit_button_textures, 
        enter_button_textures;
    init_log_textures(renderer, &background_texture, log_button_textures, 
        exit_button_textures, enter_button_textures);
    const std::string text[4] = {"name", "password", "log", "sign"};
    for (int i = 0; i < 2; i++)
    {
        buttons[i] = new MenuButton(&rect, renderer,
                                    text[i], log_button_textures, log_button_text_color);
        rect.y += 60;
        text_rect = rect;
        text_rect.x -= 200;
        text_rect.y -= 80;
        text_rect.w = 100;
        text_rect.h = 50;
        buttons[i]->set_text_rect(&text_rect);
    }
    rect.x = 350;
    rect.y = 320;
    rect.w = 80;
    rect.h = 80;
    text_rect = rect;
    text_rect.w = 50;
    text_rect.h = 50;
    for (int i = 2; i < 4; i++)
    {
        buttons[i] = new MenuButton(&rect, renderer,
                                    text[i], log_button_textures, log_button_text_color);
        buttons[i]->set_text_rect(&text_rect);
        rect.x += 160;
        text_rect.x += 160;
    }

    rect.x = setting->window_width - 300;
    rect.y = 30;
    rect.w = 100;
    rect.h = 100;
    exit_button = new Button(&rect, renderer, exit_button_textures);
    rect.x = setting->window_width - 500;
    rect.y = setting->window_height - 500;
    rect.w = 100;
    rect.h = 100;
    enter_button = new Button(&rect, renderer, enter_button_textures);

    Text *texts[4];
    for (int i = 0; i < 2; i++)
    {
        texts[i] = new Text(renderer, account[i], log_button_text_color);
    }

    while (active)
    {
        if (SDL_PollEvent(&event))
        {
            for (int i = 0; i < 4; i++)
            {
                buttons[i]->update(&event, external_msgs);
            }

            exit_button->update(&event, external_msgs);
            enter_button->update(&event, external_msgs);

            for (int i = 0; i < 2; i++)
            {
                in_msgs = buttons[i]->get_msgs();
                for (auto &&msg : in_msgs)
                {
                    if (msg == Button_mouse_overlap || msg == Button_activated)
                    {
                        SDL_StartTextInput();
                        flag = i;
                    }
                }
            }
            for (int i = 2; i < 4; i++)
            {
                in_msgs = buttons[i]->get_msgs();
                for (auto &&msg : in_msgs)
                {
                    if (msg == Button_activated)
                    {
                        command = i;
                    }
                }
            }

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
            in_msgs = enter_button->get_msgs();
            {
                for (auto &&msg : in_msgs)
                {
                    if (msg == Button_activated)
                    {
                        if (command == 2)
                        {
                            if (check_password(account[0], account[1], players))
                            {
                                active = false;
                            }
                            else
                            {
                                account[0].clear();
                                account[1].clear();
                                temp_account[0][0] = '\0';
                                temp_account[1][0] = '\0';
                            }
                        }
                        else if (command == 3)
                        {
                            if (check_name(account[0], account[1], players))
                            {
                                active = false;
                            }
                            else
                            {
                                account[0].clear();
                                account[1].clear();
                                temp_account[0][0] = '\0';
                                temp_account[1][0] = '\0';
                            }
                        }
                    }
                }
            }

            switch (event.type)
            {

            case SDL_TEXTINPUT:
                composition = event.edit.text;
                strcat(temp_account[flag], composition);
                std::cout << "edit" << composition << std::endl;
                break;
            case SDL_KEYDOWN:

                auto key = event.key.keysym.sym;
                if (key == SDLK_BACKSPACE && strlen(temp_account[flag]))
                {
                    temp_account[flag][strlen(temp_account[flag]) - 1] = '\0';
                }
                else if (key == SDLK_RETURN)
                {
                    SDL_StopTextInput();
                    account[flag] = temp_account[flag];
                }
                break;
            }
        }
        SDL_RenderClear(renderer);
        exit_button->draw();
        enter_button->draw();
        for (int i = 2; i < 4; i++)
        {
            buttons[i]->draw();
        }
        for (int i = 0; i < 2; i++)
        {
            buttons[i]->draw();
            text_rect = buttons[i]->rect;
            if (i != flag || strlen(temp_account[i]) == 0)
            {
                text_rect.w = account[i].size() * 15;
                texts[i]->reset_text(account[i]);
                texts[i]->draw(&text_rect);
            }
            else
            {
                text_rect.w = strlen(temp_account[i]) * 15;
                texts[i]->reset_text(temp_account[i]);
                texts[i]->draw(&text_rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(20.00);
    }
    for (int i = 0; i < 2; i++) 
    {
        delete texts[i];
    }
    for (int i = 0; i < 4; i++) 
    {
        delete buttons[i];
    }
    delete exit_button;
    delete enter_button;
    for (auto &&texture : log_button_textures)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto &&texture : exit_button_textures)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto &&texture : enter_button_textures)
    {
        SDL_DestroyTexture(texture);
    }
    if (background_texture)
    {
        SDL_DestroyTexture(background_texture);
    }
}

/*************************************************
  Function: init_log_textures()      // 函数名称
  Description:初始化纹理    // 函数功能、性能等的描述
  Input:渲染器，背景纹理的地址的地址，登录按钮的所有纹理，退出按钮的所有纹理，确认按钮的所有纹理 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
void init_log_textures(SDL_Renderer *renderer, SDL_Texture **background_texture,
                       std::vector<SDL_Texture *> &log_button_textures,
                       std::vector<SDL_Texture *> &exit_button_textures,
                       std::vector<SDL_Texture *> &enter_button_textures)
{
    SDL_Surface *button_surface;

    const std::string background_image = {"sources\\data_center.png"};
    const std::string log_button_images[2] = {
        {"sources\\log_button_nonactivated.png"},
        {"sources\\log_button_activated.png"},
    };
    const std::string exit_button_images[2] = {
        {"sources\\exit_button_up.png"},
        {"sources\\exit_button_down.png"},
    };
    const std::string enter_button_images[2] = {
        {"sources\\enter_nonactivated.png"},
        {"sources\\enter_activated.png"},
    };
    const std::string choose_button_images[2] = {
        {"sources\\choose_log.png"},
        {"sources\\choose_sign.png"},
    };

    button_surface = IMG_Load(background_image.c_str());
    *background_texture = (SDL_CreateTextureFromSurface(renderer, button_surface));
    SDL_FreeSurface(button_surface);

    for (int i = 0; i < 2; i++)
    {
        button_surface = IMG_Load(log_button_images[i].c_str());
        log_button_textures.push_back(SDL_CreateTextureFromSurface(renderer, button_surface));
        SDL_FreeSurface(button_surface);
        button_surface = IMG_Load(exit_button_images[i].c_str());
        exit_button_textures.push_back(SDL_CreateTextureFromSurface(renderer, button_surface));
        SDL_FreeSurface(button_surface);
        button_surface = IMG_Load(enter_button_images[i].c_str());
        enter_button_textures.push_back(SDL_CreateTextureFromSurface(renderer, button_surface));
        SDL_FreeSurface(button_surface);
    }
}

/*************************************************
  Function: log_in()      // 函数名称
  Description:登录注册的主体部分    // 函数功能、性能等的描述
  Input:渲染器，Settings的类指针，DataBase的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void       // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
void log_in(SDL_Renderer *renderer, Settings *setting, DataBase *players)
{

    if (logged)
    {
        //manage_account(renderer, players);
    }
    else
    {
        check_account(renderer, setting, players);
    }
}
