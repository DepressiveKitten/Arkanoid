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
	bonus_name update(RenderWindow& app, Paddle& paddle);   //�������� ������ ����� ��� ���������� ���������� � ��������� ������
	Bonus(int x, int y, Texture* common_textures, bonus_name bonus_type);
};

