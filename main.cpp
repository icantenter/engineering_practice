#include "menu.h"
#include "simple_game.h"
#include "register.h"
#include "Data.h"
/**
*@File: main.cpp
*@Description: 程序主体
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
/*代表整个程序是否结束，取值只能为真假*/
bool program_active = true;
    
//main函数中的参数不能省略，不然会报错
int main(int args, char *argv[])
{
    int request;
    Settings *setting = new Settings();

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window =
        SDL_CreateWindow("GreedySnake",
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         setting->window_width, setting->window_height,
                         SDL_WINDOW_SHOWN); //SDL_WINDOW_FULLSCREEN
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    const std::string file_path = "text\\players.txt";
    DataBase *players = new DataBase();                 //create new DataBase
    players->append_from_file(file_path);               //从文件中读取玩家信息到Database中
    //SDL_PointInRect();
    if (!window)
        return -1;
    if (!renderer)
        return -2;
    while (program_active)
    {
        request = menu(renderer, setting);      //得到指令
        switch (request)
        {
        case QUIT:
            program_active = false;
            break;
        case PLAY:
            game(renderer, setting);
            break;
        case LOG_IN:
            log_in(renderer, setting, players);
            break;
        case DATA:
            search_data(renderer, players, setting);
            break;
        }
    }

    players->save(file_path);
    delete players;
    delete setting;
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}