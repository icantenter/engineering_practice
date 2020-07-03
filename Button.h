#ifndef _Button_h_
#define _Button_h_
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

enum
{
    Button_nonactivated = -1,
    Button_activated = -2,
    Button_mouse_click = 0,
    Button_mouse_overlap = 1,
    Button_locked = 2,
    
};

//基类
class Button
{
protected:
    SDL_Renderer *renderer;
    std::vector<int> in_msgs;
    std::vector<int> out_msgs;
public:
    SDL_Rect rect;
    std::vector<SDL_Texture *> button_textures;
    Button(SDL_Rect *rect, SDL_Renderer *renderer, std::vector<SDL_Texture *> button_textures);
    virtual ~Button();
    virtual int draw();
    virtual void update(SDL_Event *event, std::vector<int> &external_msgs);
    virtual std::vector<int> get_msgs();
};



//派生类
class MenuButton : public Button
{
private:
    SDL_Rect text_rect;
    SDL_Color text_color;
    std::string text;
    std::string typeface = "typeface\\technology.ttf";
    SDL_Texture *text_texture;

public:
    MenuButton(SDL_Rect *rect, SDL_Renderer *renderer, const std::string &text, 
        std::vector<SDL_Texture *> button_textures ,SDL_Color text_color);
    ~MenuButton();
    void set_text_rect(SDL_Rect *text_rect);
    int draw();
    void reset_text(const std::string &text);
};


#endif