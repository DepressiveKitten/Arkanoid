#pragma once
#include "Game_objects.h"
#include "Paddle.h"
class Bonus :public Game_object
{
private:
	int radius;
	int animation_utility;
	bonus_name bonus_type;
public:
	bonus_name update(RenderWindow& app, Paddle& paddle);   //вызывать каждый фрейм для обновления информации и отрисовки шарика
	Bonus(int x, int y, Texture* common_textures, bonus_name bonus_type);
};

