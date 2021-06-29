#include "Blocks.h"
void Blocks::hurt(int damage)                   //��������� �����
{
	if (damage >= durability)                   //���� ����� ������ ��� �������� �� ���������� ����
	{
		durability = 0;
		return;
	}
	while (damage > 0)                          //����� ������ ������ �� ��� ������ �������� �������� �� ����� �������� 5
	{
		damage--, durability--;
		if (durability % 5 == 0)
		{
			Next_Sprite();
		}
	}
}

int Blocks::update(RenderWindow& app)
{
	if (durability == 0&& fade_time > 0)//��������� ������������ �����, ���� ��� �������� ����� 0(�� � �������� �����������)
	{
		fade_time -= (float)7/framerate;  //�������� ���� ��������� frameRate
		fading(fade_time);
	}
	if (fade_time > 0)
		show(app);
	else               //���������� 0 ���� ���� ���� � �����
	{
		if (is_bonus)
			return 3;
		return 0;
	}
	if (spark_cooldown == 0)
	{
		spark_cooldown = framerate/(float)3+rand()%framerate*1.5;
		return 2;
	}
	if (is_bonus)
		spark_cooldown--;
	return 1;
	
}

Blocks::Blocks(float x, float y, float scale, float wight, int durability, const Texture& texture) :Game_object(x, y, scale, wight, texture)
{
	if (rand() % 100 < 10 )
		is_bonus = true;
	else
		is_bonus = false;
	spark_cooldown = 1;
	fade_time = 1;
	this->durability = durability;
}