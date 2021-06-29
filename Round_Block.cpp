#include "Round_Block.h"

//методы
float* Round_Block::Get_Next_Position(int wight)
{
	float* info = new float[2];
	if (getx() + radius*2 + 2 + wight < win_x)  //если справа от блока еще есть место, возвращает позицию для установки блока в один ряд
	{
		info[0] = getx() + radius * 2 + 2;
		info[1] = gety();
	}
	else
	{ 
		info[0] = 0;                            //если мета нет, возвращает начало следующего ряда
		info[1] = gety() + radius * 2 + 2;
	}
	return info;
}

float* Round_Block::Check_Collision(int ball_x, int ball_y, int ball_Radius)//получает информацию о шаре, возвращает sin и cos плоскости при сторкновении или 2 при отсутствии столкновения
{
	float* angle = new float[2];   //sin и cos плоскости падения
	angle[0] = 2;
	angle[1] = 2;
	if (fade_time < 1)             //если fade_time<1 то блок находится в процессе уичтожения и столкнутся с ним нельзя
	{
		return angle;
	}
	int x = getx()+radius;  //получаем позицию блока и устанавливаем x и y в его центр
	int y = gety()+radius;
	if (ball_x + ball_Radius<x-radius || ball_x - ball_Radius>x + radius || ball_y + ball_Radius<y-radius || ball_y - ball_Radius>y + radius)//проверяем на возможность столкновения
	{
		
		return angle;
	}
	if (std::pow(ball_x - x, 2) + std::pow(ball_y - y, 2) > std::pow(radius + ball_Radius,2))
	{
		return angle;
	}
	//проверяем столкновение с углами блока
	if (pow(x - ball_x, 2) + pow(y - ball_y, 2) <= pow(ball_Radius+radius, 2))//лево-верх
	{
		angle[1] = (float)(y - ball_y) / (float)(ball_Radius+radius);
		angle[0] = (float)(x - ball_x) / (float)(ball_Radius + radius);
		return angle;
	}
	if (pow(ball_x - x , 2) + pow(y - ball_y, 2) <= pow(ball_Radius + radius, 2)) //право-верх
	{
		angle[1] = (float)(y - ball_y) / (float)(ball_Radius + radius);
		angle[0] = (float)-(ball_x - x ) / (float)(ball_Radius + radius);
		return angle;
	}
	if (pow(x - ball_x, 2) + pow(ball_y - y , 2) <= pow(ball_Radius + radius, 2))// лево-низ
	{
		angle[1] = (float)-(ball_y - y) / (float)(ball_Radius + radius);
		angle[0] = (float)(x - ball_x) / (float)(ball_Radius + radius);
		return angle;
	}
	if (pow(ball_x - x , 2) + pow(ball_y - y , 2) <= pow(ball_Radius + radius, 2))//право-низ
	{
		angle[1] = (float)-(ball_y - y ) / (float)(ball_Radius + radius);
		angle[0] = (float)-(ball_x - x ) / (float)(ball_Radius + radius);
		return angle;
	}
	return angle;
}

//конструкторы

Round_Block::Round_Block(float x, float y, const Texture& texture, float scale, int durability) :Blocks(x,y,scale, texture.getSize().y,durability,texture)
{
	radius = texture.getSize().x / 2 * scale;
}
Round_Block::Round_Block(float* info, const Texture& texture, float scale, int durability) : Blocks(info[0], info[1], scale, texture.getSize().y, durability, texture)
{
	radius = texture.getSize().x / 2 * scale;
}
Round_Block::Round_Block(float x, float y, const Texture& texture) : Blocks(x, y, 1, texture.getSize().y, 4, texture)
{
	radius = texture.getSize().x / 2 * 1;
}