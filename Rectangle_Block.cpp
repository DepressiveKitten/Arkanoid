#include "Rectangle_Block.h"

//методы
float* Rectangle_Block::Get_Next_Position(int wight)
{
	float* info = new float[2];
	if (getx() + size_x + 1 + wight < win_x)  //если справа от блока еще есть место, возвращает позицию для установки блока в один ряд
	{
		info[0] = getx() + size_x + 1;
		info[1] = gety();
	}
	else                                      //если мета нет, возвращает начало следующего ряда
	{
		info[0] = 0;
		info[1] = gety() + size_y + 1;
	}
	return info;
}

float* Rectangle_Block::Check_Collision(int ball_x, int ball_y, int ball_Radius)//получает информацию о шаре, возвращает sin и cos плоскости при сторкновении или 2 при отсутствии столкновения
{
	float* angle = new float[2];   //sin и cos плоскости падения
	angle[0] = 2;
	angle[1] = 2;
	if (fade_time < 1)             //если fade_time<1 то блок находится в процессе уичтожения и столкнутся с ним нельзя
	{
		return angle;
	}
	int x = getx();  //получаем позицию блока
	int y = gety();
	if (ball_x + ball_Radius<x || ball_x - ball_Radius>x + size_x || ball_y + ball_Radius<y || ball_y - ball_Radius>y + size_y)//проверяем на возможность столкновения
	{
		return angle;
	}


	if (ball_x  > x && ball_x < x + size_x)//проверяем на столкновение со сторонами блока
	{
		angle[0] = 0;
		if (ball_y < y)        //верх
		{
			angle[1] = 1;
			return angle;
		}
		else                   //низ
		{
			angle[1] = -1;
			return angle;
		}
	}
	if (ball_y > y && ball_y < y + size_y)
	{
		angle[1] = 0;
		if (ball_x < x)        //лево
		{
			angle[0] = 1;
			return angle;
		}
		else                   //право
		{
			angle[0] = -1;
			return angle;
		}
	}
	                                                                   //проверяем столкновение с углами блока
	if (pow(x - ball_x, 2) + pow(y - ball_y, 2) <= pow(ball_Radius, 2))//лево-верх
	{
		angle[1] = (float)(y - ball_y) / (float)ball_Radius;
		angle[0] = (float)(x - ball_x) / (float)ball_Radius;
		return angle;
	}
	if (pow(ball_x - (x + size_x), 2) + pow(y - ball_y, 2) <= pow(ball_Radius, 2)) //право-верх
	{
		angle[1] = (float)(y - ball_y) / (float)ball_Radius;
		angle[0] = (float)-(ball_x - (x + size_x)) / (float)ball_Radius;
		return angle;
	}
	if (pow(x - ball_x, 2) + pow(ball_y - (y + size_y), 2) <= pow(ball_Radius, 2))// лево-низ
	{
		angle[1] = (float)-(ball_y - (y + size_y)) / (float)ball_Radius;
		angle[0] = (float)(x - ball_x) / (float)ball_Radius;
		return angle;
	}
	if (pow(ball_x - (x + size_x), 2) + pow(ball_y - (y + size_y), 2) <= pow(ball_Radius, 2))//право-низ
	{
		angle[1] = (float)-(ball_y - (y + size_y)) / (float)ball_Radius;
		angle[0] = (float)-(ball_x - (x + size_x)) / (float)ball_Radius;
		return angle;
	}

	angle[0] = 2;
	angle[1] = 2;
	return angle;
}

//конструкторы

Rectangle_Block::Rectangle_Block(float x, float y, const Texture& texture,float scale,float wight, int durability) :Blocks(x, y, scale, wight,durability, texture)
{
	size_x = wight*scale;
	size_y = texture.getSize().y*scale;
}
Rectangle_Block::Rectangle_Block(float* info, const Texture& texture, float scale, float wight, int durability) :Blocks(info[0], info[1], scale, wight,durability, texture)
{
	delete[] info;
	size_x = wight * scale;
	size_y = texture.getSize().y * scale;
}
Rectangle_Block::Rectangle_Block(float x, float y, const Texture& texture) :Blocks(x, y, 1.4, 50,4, texture)
{
	size_x = 70;
	size_y = 35;
}