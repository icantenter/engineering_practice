#include "Arrow.h"

/**
*@File: Arrow.cpp
*@Description: 存放Arrow类的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
/*************************************************
  Function:构造函数       函数名称
  Description:创建实例时调用的函数     函数功能、性能等的描述
  Input:箭头的init_rect，渲染器，箭头的图片的路径  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
Arrow::Arrow(SDL_Rect *arrow_rect, SDL_Renderer *renderer, const std::string image)
{
	SDL_Surface *surface;

	this->arrow_rect = *arrow_rect;
	this->x = arrow_rect->x;
	this->y = arrow_rect->y;
	this->renderer = renderer;

	surface = IMG_Load(image.c_str());
	this->arrow_texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

/*************************************************
  Function:draw()       函数名称
  Description:在渲染器上画出箭头     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:void          其它说明
*************************************************/
void Arrow::draw()
{
	SDL_RenderCopy(this->renderer, this->arrow_texture, NULL, &arrow_rect);
}

/*************************************************
  Function:pass       函数名称
  Description:pass     函数功能、性能等的描述
  Input:pass  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:pass         函数返回值的说明
  Others:pass         其它说明
*************************************************/
void Arrow::set_range(SDL_Point points[], int point_direction)
{
}

/*************************************************
  Function:update()       函数名称
  Description:更新箭头位置     函数功能、性能等的描述
  Input:左右碰撞的边界，指向的方向  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:模拟的加速度恒定，弹性碰撞情况         其它说明
*************************************************/
void Arrow::update(SDL_Point points[], int point_direction)
{
	int x_range = abs(points[0].x - points[1].x);
	int y_range = abs(points[0].y - points[1].y);
	int center_x = (points[0].x + points[1].x) / 2;
	int center_y = (points[0].y + points[1].y) / 2;

	if (abs(arrow_rect.x - center_x) > x_range / 2 ||
		abs(arrow_rect.y - center_y) > y_range / 2)
	{
		direction *= -1;
	}

	this->x += (x_range / 20.0f) * direction * speed;
	this->y += (y_range / 20.0f) * direction * speed;

	this->arrow_rect.x = this->x;
	this->arrow_rect.y = this->y;
	point_direction == direction ? speed++ : speed--;
	speed = std::min(speed, 7);
	speed = std::max(speed, 4);
}

/*************************************************
  Function:析构函数       函数名称
  Description:删除实例时调用的函数     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:Texture是动态分配的，需要释放          其它说明
*************************************************/
Arrow::~Arrow()
{
	SDL_DestroyTexture(arrow_texture);
}