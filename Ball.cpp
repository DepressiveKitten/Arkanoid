#pragma once
#include "Ball.h"

//------------методы------------

int Ball::update(RenderWindow& app,Paddle &paddle, std::list<Blocks*>& blocks)
{
    move(cos*speed,-sin*speed);    //перемещение шарика
	collide(paddle, blocks);//проверка столкновения с списком блоков и доской
	animation_utility++;
	if (animation_utility > framerate/30)    //поменять если изменится frameRate
	{
		Next_Sprite();
		animation_utility = 0;
	}
	show(app);                     //отрисовка шарика
	
	if (gety() > win_y+50)            //возвращает 0 если шарик выпал вниз
		return 0;
	return 1;
}

void Ball::reset()
{
	radius = 18;
	damage = 5;
	speed = (float)600/framerate;
	for (int i = 0; i <= 90; i++)
		angles[i] = std::sin(i * M_PI / 180);
}

void Ball::SetAngle(int angle)
{
	while (angle >= 360)//переводим угол в диапазон 0-360
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle < 90)              //в зависимости от четверти угла, меняем cos и sin на новые
	{
		sin = angles[angle];
		cos = angles[90 - angle];
		return;
	}
	if (angle < 180)
	{
		sin = angles[180 - angle];
		cos = -angles[angle - 90];
		return;
	}
	if (angle < 270)
	{
		sin = -angles[angle - 180];
		cos = -angles[270 - angle];
		return;
	}
	sin = -angles[360 - angle];
	cos = angles[angle - 270];
	return;
}

void Ball::collide(Paddle &paddle,std::list<Blocks*> &blocks)
{
	int x = getx();         //получение позиции шарика
	int y = gety();

	if (x+2*radius >= win_x)//проверка на столкновение с границами экрана
		cos = -abs(cos);
	if (x <= 0)
		cos = abs(cos);
	if (y <= 0)
		sin = -abs(sin);

	if (sin < 0)//столкновение с доской происходит только при движении вниз
	{
		int angle = paddle.Check_Collision(x + radius, y + radius, radius);//проверка на столкновение с доской
		if (angle != 0)//если столкновение было
		{
			if (angle == 90)            //если удар происходит в центр доски то шар отскакивает от нее как от блока
				angle_reflection(0, 1);
			else                        //иначе шар отскакивает под углом, те большим, чем ближе он к краю доски
			{
				SetAngle(angle);
			}
			return;
		}
	}


	for (auto i = blocks.begin(); i != blocks.end(); i++)                //проверка всех блоков на столкновение с ними
	{
		float* angle = (*i)->Check_Collision(x+radius, y+radius, radius);
		if (angle[0] != 2)                                               //Функция возвращаяет {2,2} если столкновения нет
		{
			(*i)->hurt(damage);
			angle_reflection(angle[0], angle[1]);                        //изменение угла при отражении от блока
			delete[] angle;
			return;
		}
		delete[] angle;
	}
	return;
}

void Ball::angle_reflection(float reflect_sin, float reflect_cos)
{
	int reflect_angle, fall_angle,cos_angle;//REFLECT - угол плоскости на которую падает шар через синус, FALL - угол падения,COS - угол плоскости на которую падает шар через косинус
	int left = 0, right = 91;//указатели на края при бинарном поиске
	for (int i = 0; i < 7; i++)//бинарным поиском ищется угол наиболее близкий к значению синуса плоскости падения
	{
		reflect_angle = left+(right - left) / 2;
		if (abs(reflect_sin) == angles[left+(right - left) / 2])
			break;
		if (abs(reflect_sin) > angles[left+(right - left) / 2])
			left = left+(right - left) / 2;
		else
			right = left+(right - left) / 2;
	}
	left = 0,right = 91;//обнуление указателей
	for (int i = 0; i < 7; i++)//бинарным поиском ищется угол наиболее близкий к значению косинуса плоскости падения
	{
		cos_angle = left + (right - left) / 2;
		if (abs(reflect_cos) == angles[left + (right - left) / 2])
			break;
		if (abs(reflect_cos) > angles[left + (right - left) / 2])
			left = left + (right - left) / 2;
		else
			right = left + (right - left) / 2;
	}
	cos_angle = 90 - cos_angle;//меняется значение косинуса так как cos a = (90 - sin a)
	reflect_angle = (cos_angle + reflect_angle) / 2; //уменьшаем погрешность усредняя значения угла полученные из синуса и косинуса
	if (reflect_sin < 0 && reflect_cos < 0)      //переводим угол в четверть соответсвующую знакам синуса и косинуса
		reflect_angle += 180;
	else
	{
		if(reflect_sin < 0)
		    reflect_angle = 360-reflect_angle;
		if(reflect_cos < 0)
			reflect_angle = 180 - reflect_angle;
	}


	left = 0, right = 91;//обнуление указателей
	for (int i = 0; i < 7; i++)//бинарным поиском ищется угол наиболее близкий к значению синуса угла падения
	{
		fall_angle = left + (right - left) / 2;
		if (abs(sin) == angles[left + (right - left) / 2])
			break;
		if (abs(sin) > angles[left + (right - left) / 2])
			left = left + (right - left) / 2;
		else
			right = left + (right - left) / 2;
	}
	if (sin > 0 && cos > 0)    //переводим угол в четверть обратную знакам синуса и косинуса (чтобы направление скорости "входило" в единичную окружность)
		fall_angle += 180;
	if (sin < 0&&cos>0)
		fall_angle = 180 - fall_angle;
	if (cos < 0&&sin>0)
		fall_angle = 360 - fall_angle;


	reflect_angle = 2*reflect_angle + 180 - fall_angle; //записываем угол отражения в reflect_angle(формула: угол падения равен углу отражения)
	if (reflect_angle % 90 == 0) //защита от softlock-а, чтобы шарик всегда имел вертикальную составляющую скорости
		reflect_angle += 4;
	SetAngle(reflect_angle);
	return;
}

//------------конструктор------------

Ball::Ball(float x, float y, const Texture& texture, float sin, float cos):Game_object(x,y,((float)radius*2)/ (float)texture.getSize().y,texture.getSize().y,texture)
{
	animation_utility = 0;
	this->sin = sin;
	this->cos = cos;
}