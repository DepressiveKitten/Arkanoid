#pragma once
#include "Ball.h"

//------------������------------

int Ball::update(RenderWindow& app,Paddle &paddle, std::list<Blocks*>& blocks)
{
    move(cos*speed,-sin*speed);    //����������� ������
	collide(paddle, blocks);//�������� ������������ � ������� ������ � ������
	animation_utility++;
	if (animation_utility > framerate/30)    //�������� ���� ��������� frameRate
	{
		Next_Sprite();
		animation_utility = 0;
	}
	show(app);                     //��������� ������
	
	if (gety() > win_y+50)            //���������� 0 ���� ����� ����� ����
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
	while (angle >= 360)//��������� ���� � �������� 0-360
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle < 90)              //� ����������� �� �������� ����, ������ cos � sin �� �����
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
	int x = getx();         //��������� ������� ������
	int y = gety();

	if (x+2*radius >= win_x)//�������� �� ������������ � ��������� ������
		cos = -abs(cos);
	if (x <= 0)
		cos = abs(cos);
	if (y <= 0)
		sin = -abs(sin);

	if (sin < 0)//������������ � ������ ���������� ������ ��� �������� ����
	{
		int angle = paddle.Check_Collision(x + radius, y + radius, radius);//�������� �� ������������ � ������
		if (angle != 0)//���� ������������ ����
		{
			if (angle == 90)            //���� ���� ���������� � ����� ����� �� ��� ����������� �� ��� ��� �� �����
				angle_reflection(0, 1);
			else                        //����� ��� ����������� ��� �����, �� �������, ��� ����� �� � ���� �����
			{
				SetAngle(angle);
			}
			return;
		}
	}


	for (auto i = blocks.begin(); i != blocks.end(); i++)                //�������� ���� ������ �� ������������ � ����
	{
		float* angle = (*i)->Check_Collision(x+radius, y+radius, radius);
		if (angle[0] != 2)                                               //������� ����������� {2,2} ���� ������������ ���
		{
			(*i)->hurt(damage);
			angle_reflection(angle[0], angle[1]);                        //��������� ���� ��� ��������� �� �����
			delete[] angle;
			return;
		}
		delete[] angle;
	}
	return;
}

void Ball::angle_reflection(float reflect_sin, float reflect_cos)
{
	int reflect_angle, fall_angle,cos_angle;//REFLECT - ���� ��������� �� ������� ������ ��� ����� �����, FALL - ���� �������,COS - ���� ��������� �� ������� ������ ��� ����� �������
	int left = 0, right = 91;//��������� �� ���� ��� �������� ������
	for (int i = 0; i < 7; i++)//�������� ������� ������ ���� �������� ������� � �������� ������ ��������� �������
	{
		reflect_angle = left+(right - left) / 2;
		if (abs(reflect_sin) == angles[left+(right - left) / 2])
			break;
		if (abs(reflect_sin) > angles[left+(right - left) / 2])
			left = left+(right - left) / 2;
		else
			right = left+(right - left) / 2;
	}
	left = 0,right = 91;//��������� ����������
	for (int i = 0; i < 7; i++)//�������� ������� ������ ���� �������� ������� � �������� �������� ��������� �������
	{
		cos_angle = left + (right - left) / 2;
		if (abs(reflect_cos) == angles[left + (right - left) / 2])
			break;
		if (abs(reflect_cos) > angles[left + (right - left) / 2])
			left = left + (right - left) / 2;
		else
			right = left + (right - left) / 2;
	}
	cos_angle = 90 - cos_angle;//�������� �������� �������� ��� ��� cos a = (90 - sin a)
	reflect_angle = (cos_angle + reflect_angle) / 2; //��������� ����������� �������� �������� ���� ���������� �� ������ � ��������
	if (reflect_sin < 0 && reflect_cos < 0)      //��������� ���� � �������� �������������� ������ ������ � ��������
		reflect_angle += 180;
	else
	{
		if(reflect_sin < 0)
		    reflect_angle = 360-reflect_angle;
		if(reflect_cos < 0)
			reflect_angle = 180 - reflect_angle;
	}


	left = 0, right = 91;//��������� ����������
	for (int i = 0; i < 7; i++)//�������� ������� ������ ���� �������� ������� � �������� ������ ���� �������
	{
		fall_angle = left + (right - left) / 2;
		if (abs(sin) == angles[left + (right - left) / 2])
			break;
		if (abs(sin) > angles[left + (right - left) / 2])
			left = left + (right - left) / 2;
		else
			right = left + (right - left) / 2;
	}
	if (sin > 0 && cos > 0)    //��������� ���� � �������� �������� ������ ������ � �������� (����� ����������� �������� "�������" � ��������� ����������)
		fall_angle += 180;
	if (sin < 0&&cos>0)
		fall_angle = 180 - fall_angle;
	if (cos < 0&&sin>0)
		fall_angle = 360 - fall_angle;


	reflect_angle = 2*reflect_angle + 180 - fall_angle; //���������� ���� ��������� � reflect_angle(�������: ���� ������� ����� ���� ���������)
	if (reflect_angle % 90 == 0) //������ �� softlock-�, ����� ����� ������ ���� ������������ ������������ ��������
		reflect_angle += 4;
	SetAngle(reflect_angle);
	return;
}

//------------�����������------------

Ball::Ball(float x, float y, const Texture& texture, float sin, float cos):Game_object(x,y,((float)radius*2)/ (float)texture.getSize().y,texture.getSize().y,texture)
{
	animation_utility = 0;
	this->sin = sin;
	this->cos = cos;
}