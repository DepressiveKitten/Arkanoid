#pragma once
#include "Game_objects.h"
extern const int framerate;
class Particles : public Game_object
{
private:
    //float speed, sin, cos, acceleration;
    float fade_speed, fade_time;
    int animation_utility;
public:
    int update(RenderWindow& app);
    Particles(float x, float y, const Texture& texture, float scale);
    Particles(float x, float y, const Texture& texture, float fade_speed, float fade_time, int animation_utility,float scale);
};

