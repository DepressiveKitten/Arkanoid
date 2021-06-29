#include "Bonus.h"
bonus_name Bonus::update(RenderWindow& app, Paddle& paddle)
{
	move(0, (float)300 / framerate*0.75);
	animation_utility--;
	if (animation_utility <= 0)
	{
		animation_utility = framerate / 16;
		Next_Sprite();
	}
	show(app);
	if (gety()<win_y-40-radius*0.5&&gety() > win_y - 40-radius*2&&getx()+2*radius>paddle.getx()&& getx()<paddle.getx()+paddle.get_size())
	{
		return bonus_type;
	}
	if (gety() > win_y)
		return dead;
	return fly;
}
Bonus::Bonus(int x, int y, Texture* common_textures, bonus_name bonus_type) :Game_object(x, y, 1, common_textures[(int)bonus_type + 7].getSize().y, common_textures[(int)bonus_type + 7])
{
	radius = common_textures[(int)bonus_type + 2].getSize().y / 2;
	animation_utility = framerate / 16;
	this->bonus_type = bonus_type;
}