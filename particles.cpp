#include "particles.h"

int Particles::update(RenderWindow& app)
{
	if (fade_time <= 0.01 && animation_utility <= 0)
	{
		return 0;
	}
	if (animation_utility == 0)
	{
		fade_time -= fade_speed;
	}
	else
	{
		fade_time += fade_speed;
		if (fade_time >= 0.5)
			animation_utility = 0;
	}
	fading(fade_time);
	show(app);
	return 1;
}

Particles::Particles(float x, float y, const Texture& texture, float scale) :Game_object(x, y, scale, texture.getSize().y, texture)
{
	fade_speed=0.6/framerate;
	fade_time = 0.2;
	animation_utility = 0;
}
Particles::Particles(float x, float y, const Texture& texture, float fade_speed, float fade_time, int animation_utility,float scale) :Game_object(x, y, scale, texture.getSize().y, texture)
{
	this->fade_speed = fade_speed;
	this->fade_time = fade_time;
	this->animation_utility = animation_utility;
}