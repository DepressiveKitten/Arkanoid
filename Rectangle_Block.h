#pragma once
#include "Blocks.h"
class Rectangle_Block : public Blocks
{
private:
	int size_x, size_y;
public:
	//----------�������
	virtual int get_x_size()override { return size_x; };
	virtual int get_y_size()override { return size_y; };
	float* Get_Next_Position(int wight) override;  //������������ ����� � �������������, ���������� ������� ���������� ����� � ����
	float* Check_Collision(int ball_x, int ball_y, int ball_Radius) override; //�������� ���������� � ����, ���������� sin � cos ��������� ��� ������������ ��� 2 2 ��� ���������� ������������
	//----------������������
	Rectangle_Block(float x, float y, const Texture& texture, float scale, float wight, int durability);  //����������� � ��������� ���� �����
	Rectangle_Block(float* info, const Texture& texture, float scale, float wight, int durability);  //����������� ������������ ����� � ������� Get_Next_Position ��� ����������� ������ � ���
	Rectangle_Block(float x, float y, const Texture& texture);                    //����������� ������������ �����
};
