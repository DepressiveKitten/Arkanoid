#include "Round_Block.h"

//������
float* Round_Block::Get_Next_Position(int wight)
{
	float* info = new float[2];
	if (getx() + radius*2 + 2 + wight < win_x)  //���� ������ �� ����� ��� ���� �����, ���������� ������� ��� ��������� ����� � ���� ���
	{
		info[0] = getx() + radius * 2 + 2;
		info[1] = gety();
	}
	else
	{ 
		info[0] = 0;                            //���� ���� ���, ���������� ������ ���������� ����
		info[1] = gety() + radius * 2 + 2;
	}
	return info;
}

float* Round_Block::Check_Collision(int ball_x, int ball_y, int ball_Radius)//�������� ���������� � ����, ���������� sin � cos ��������� ��� ������������ ��� 2 ��� ���������� ������������
{
	float* angle = new float[2];   //sin � cos ��������� �������
	angle[0] = 2;
	angle[1] = 2;
	if (fade_time < 1)             //���� fade_time<1 �� ���� ��������� � �������� ���������� � ���������� � ��� ������
	{
		return angle;
	}
	int x = getx()+radius;  //�������� ������� ����� � ������������� x � y � ��� �����
	int y = gety()+radius;
	if (ball_x + ball_Radius<x-radius || ball_x - ball_Radius>x + radius || ball_y + ball_Radius<y-radius || ball_y - ball_Radius>y + radius)//��������� �� ����������� ������������
	{
		
		return angle;
	}
	if (std::pow(ball_x - x, 2) + std::pow(ball_y - y, 2) > std::pow(radius + ball_Radius,2))
	{
		return angle;
	}
	//��������� ������������ � ������ �����
	if (pow(x - ball_x, 2) + pow(y - ball_y, 2) <= pow(ball_Radius+radius, 2))//����-����
	{
		angle[1] = (float)(y - ball_y) / (float)(ball_Radius+radius);
		angle[0] = (float)(x - ball_x) / (float)(ball_Radius + radius);
		return angle;
	}
	if (pow(ball_x - x , 2) + pow(y - ball_y, 2) <= pow(ball_Radius + radius, 2)) //�����-����
	{
		angle[1] = (float)(y - ball_y) / (float)(ball_Radius + radius);
		angle[0] = (float)-(ball_x - x ) / (float)(ball_Radius + radius);
		return angle;
	}
	if (pow(x - ball_x, 2) + pow(ball_y - y , 2) <= pow(ball_Radius + radius, 2))// ����-���
	{
		angle[1] = (float)-(ball_y - y) / (float)(ball_Radius + radius);
		angle[0] = (float)(x - ball_x) / (float)(ball_Radius + radius);
		return angle;
	}
	if (pow(ball_x - x , 2) + pow(ball_y - y , 2) <= pow(ball_Radius + radius, 2))//�����-���
	{
		angle[1] = (float)-(ball_y - y ) / (float)(ball_Radius + radius);
		angle[0] = (float)-(ball_x - x ) / (float)(ball_Radius + radius);
		return angle;
	}
	return angle;
}

//������������

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