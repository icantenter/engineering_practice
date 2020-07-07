#include "simple_game.h"
/**
*@File: game.cpp
*@Description: 存放游戏模块的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/

/*代表游戏是否结束，取值只能为真假*/
bool game_active;

extern bool program_active;
extern Player *logged_player;
extern bool logged;

/*************************************************
  Function:draw_map()      // 函数名称
  Description:画出地图    // 函数功能、性能等的描述
  Input:渲染器 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:void        // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
void draw_map(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
    SDL_Point vertice[5] = {
        {map_left - 1, map_top - 1},
        {map_left + map_size + 1, map_top - 1},
        {map_left + map_size + 1, map_size + map_top + 1},
        {map_left - 1, map_size + map_top + 1},
        {map_left - 1, map_top - 1}};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawLines(renderer, vertice, 5);
}

/*************************************************
  Function:check_collides()      // 函数名称
  Description:检测蛇与其它物体的碰撞    // 函数功能、性能等的描述
  Input:蛇的类指针，苹果的类指针，分数，收益幅度 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否碰撞的bool值        // 函数返回值的说明
  Others:还会更新苹果        // 其它说明
*************************************************/
bool check_collides(Snake *player, Apple *apple, int *score, int score_scale)
{
    SDL_Rect temp_rect = apple->get_rect();
    if ((player->head->rect).y < map_top ||
        (player->head->rect).y > map_size + map_top - snake_block_height || //Check whether the snake
        (player->head->rect).x < map_left ||
        (player->head->rect).x > map_size + map_left - snake_block_width) //collides with the wall
    {
        game_active = false;
        return true;
    }
    else if (player->check_self_collide())
    {
        game_active = false;
        return true;
    }
    else if (player->check_head_collide(&temp_rect)) //detect whether the apple is eaten
    {
        player->grow(1);
        *score += score_scale;
        do
        {
            apple->reset_apple();
            temp_rect = apple->get_rect();
        } while (player->check_collides(&temp_rect) == true);
    }

    return false;
}

/*************************************************
  Function:check_keyboard_events()      // 函数名称
  Description:检测键盘事件，并更新蛇    // 函数功能、性能等的描述
  Input:蛇的类指针，苹果的类指针，分数，收益幅度 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:是否碰撞的bool值        // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
int check_keyboard_events(int *speed, int speed_scale, Snake *player)
{
    int command_direction = DIRECTIONLESS;

    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game_active = false;
            program_active = false;
            return 1;
        }
        switch (event.key.keysym.sym)
        {
        case SDLK_q:
            game_active = false;
            return 0;
            break;
        case SDLK_UP:
        case SDLK_w:
            command_direction = UP;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            command_direction = DOWN;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            command_direction = LEFT;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            command_direction = RIGHT;
            break;
        case SDLK_RETURN:
            *speed = std::min(*speed + speed_scale, 40);
            break;
        }
        while (SDL_PollEvent(&event))
        {
            continue;
        }
    }
    player->update(command_direction);
    player->change_color();
    return 0;
}

void draw_snakes_apple(Snake *player, Apple *apple, SDL_Rect text_rects[],
                       Text *texts[], std::string score_board_texts[], int values[])
{
    player->draw();
    apple->draw();
    for (int i = 0; i < 2; i++)
    {
        texts[i]->reset_text(score_board_texts[i] + std::to_string(values[i]));
        texts[i]->draw(text_rects + i);
    }
}

/*初始化动态属性*/
void init_dynamic_property(int *speed, int *score, Snake *player,
                           Apple *apple)
{
    player->grow(3, RIGHT);
    game_active = true;
    *speed = 2;
    *score = 0;
}

/*************************************************
  Function:game()      // 函数名称
  Description:游戏主体和更新用户信息    // 函数功能、性能等的描述
  Input:渲染器，Settings的类指针 // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Return:无意义的整数        // 函数返回值的说明
  Others:void        // 其它说明
*************************************************/
int game(SDL_Renderer *renderer, Settings *settings)
{
    Apple *apple;
    Snake *player;
    int alpha = 255;
    int speed = 2, score = 0, level = 1; //, highest_score;
    int speed_scale = 4, score_scale = 4;
    clock_t start, end;
    SDL_Rect player_rect{snake_block_width * 7 + map_left, 
        snake_block_height * 7 + map_top, snake_block_width, snake_block_height};
    SDL_Rect apple_rect{snake_block_width * 4 + map_left, 
        snake_block_height * 4 + map_top, snake_block_width, snake_block_height};
    SDL_Rect score_board_rect[2] = {{score_board_left, map_top,
                                     score_board_size, score_board_size},
                                    {score_board_left, map_top + score_board_size,
                                     score_board_size, score_board_size}};
    SDL_Rect curtain_rect{0, 0, settings->window_width, settings->window_height};
    std::string score_board_texts[2] = {{"score: "}, {"level: "}};
    SDL_Color text_color{20, 20, 20, 255};
    Text *texts[2];
    int values[2]{score, level};
    for (int i = 0; i < 2; i++)
    {
        texts[i] = new Text(renderer, score_board_texts[i], text_color);
    }

    if (logged == false)
    {
        return 1;
    }

    Curtain *curtain = new Curtain(renderer, &curtain_rect);
    curtain->set_alpha(0);
    while (alpha < 255)
    {
        curtain->draw();
        alpha += 75;
    }

    //highest_score = get_highest_score();
    game_active = 0;
    try
    {
        apple = new Apple(renderer, &apple_rect);
        player = new Snake(renderer, &player_rect);
        if (apple == NULL || player == NULL)
        {
            throw error_msgs[ERROR_ARGUMENT];
        }
    }
    catch (const std::string msg)
    {
        std::cerr << "simple game :" << msg << '\n';
    }

    init_dynamic_property(&speed, &score, player, apple);

    curtain->set_alpha(255);
    while (alpha > 0)
    {
        draw_map(renderer);
        draw_snakes_apple(player, apple, score_board_rect, 
            texts, score_board_texts, values);
        alpha -= 75;
    }
    delete curtain;
    while (game_active)
    {
        start = clock();
        check_keyboard_events(&speed, speed_scale, player);
        check_collides(player, apple, &score, score_scale);
        if (game_active)
        {
            SDL_RenderClear(renderer);
            draw_map(renderer);
            values[0] = score;
            level = (speed * 10 + score) / 50;
            values[1] = level;
            draw_snakes_apple(player, apple, score_board_rect, texts, 
                score_board_texts, values);
            SDL_RenderPresent(renderer);
        }
        end = clock();
        if ((100.00 - (end - start) - speed) > 0)
        {
            SDL_Delay(100.00 - (end - start) - speed);
        }
        logged_player->time += end - start;
    }
    Text *dead_msg = new Text{renderer, "You are dead", text_color};
    SDL_Rect dead_msg_rect{map_left - 100, map_top - 100, 600, 600};
    dead_msg->draw(&dead_msg_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000.00);
    for (int i = 0; i < 2; i++)
    {
        delete texts[i];
    }

    delete dead_msg;
    delete apple;
    delete player;
    logged_player->high_score = std::max(logged_player->high_score, score);
    logged_player->number++;
    return 0;
}
