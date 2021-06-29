#include "Rectangle_Block.h"

//������
float* Rectangle_Block::Get_Next_Position(int wight)
{
	float* info = new float[2];
	if (getx() + size_x + 1 + wight < win_x)  //���� ������ �� ����� ��� ���� �����, ���������� ������� ��� ��������� ����� � ���� ���
	{
		info[0] = getx() + size_x + 1;
		info[1] = gety();
	}
	else                                      //���� ���� ���, ���������� ������ ���������� ����
	{
		info[0] = 0;
		info[1] = gety() + size_y + 1;
	}
	return info;
}

float* Rectangle_Block::Check_Collision(int ball_x, int ball_y, int ball_Radius)//�������� ���������� � ����, ���������� sin � cos ��������� ��� ������������ ��� 2 ��� ���������� ������������
{
	float* angle = new float[2];   //sin � cos ��������� �������
	angle[0] = 2;
	angle[1] = 2;
	if (fade_time < 1)             //���� fade_time<1 �� ���� ��������� � �������� ���������� � ���������� � ��� ������
	{
		return angle;
	}
	int x = getx();  //�������� ������� �����
	int y = gety();
	if (ball_x + ball_Radius<x || ball_x - ball_Radius>x + size_x || ball_y + ball_Radius<y || ball_y - ball_Radius>y + size_y)//��������� �� ����������� ������������
	{
		return angle;
	}


	if (ball_x  > x && ball_x < x + size_x)//��������� �� ������������ �� ��������� �����
	{
		angle[0] = 0;
		if (ball_y < y)        //����
		{
			angle[1] = 1;
			return angle;
		}
		else                   //���
		{
			angle[1] = -1;
			return angle;
		}
	}
	if (ball_y > y && ball_y < y + size_y)
	{
		angle[1] = 0;
		if (ball_x < x)        //����
		{
			angle[0] = 1;
			return angle;
		}
		else                   //�����
		{
			angle[0] = -1;
			return angle;
		}
	}
	                                                                   //��������� ������������ � ������ �����
	if (pow(x - ball_x, 2) + pow(y - ball_y, 2) <= pow(ball_Radius, 2))//����-����
	{
		angle[1] = (float)(y - ball_y) / (float)ball_Radius;
		angle[0] = (float)(x - ball_x) / (float)ball_Radius;
		return angle;
	}
	if (pow(ball_x - (x + size_x), 2) + pow(y - ball_y, 2) <= pow(ball_Radius, 2)) //�����-����
	{
		angle[1] = (float)(y - ball_y) / (float)ball_Radius;
		angle[0] = (float)-(ball_x - (x + size_x)) / (float)ball_Radius;
		return angle;
	}
	if (pow(x - ball_x, 2) + pow(ball_y - (y + size_y), 2) <= pow(ball_Radius, 2))// ����-���
	{
		angle[1] = (float)-(ball_y - (y + size_y)) / (float)ball_Radius;
		angle[0] = (float)(x - ball_x) / (float)ball_Radius;
		return angle;
	}
	if (pow(ball_x - (x + size_x), 2) + pow(ball_y - (y + size_y), 2) <= pow(ball_Radius, 2))//�����-���
	{
		angle[1] = (float)-(ball_y - (y + size_y)) / (float)ball_Radius;
		angle[0] = (float)-(ball_x - (x + size_x)) / (float)ball_Radius;
		return angle;
	}

	angle[0] = 2;
	angle[1] = 2;
	return angle;
}

//������������

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