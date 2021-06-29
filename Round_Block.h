#pragma once
#include "Blocks.h"
extern const int win_y, win_x;
class Round_Block : public Blocks
{
private:
	int radius;
public :
	//----------�������
	int get_x_size()override { return radius; };
	int get_y_size()override { return radius; };
	float* Get_Next_Position(int wight) override;   //������������ ����� � �������������, ���������� ������� ���������� ����� � ����
	float* Check_Collision(int ball_x, int ball_y, int ball_Radius) override; //�������� ���������� � ����, ���������� sin � cos ��������� ��� ������������ ��� 2 2 ��� ���������� ������������
	//----------������������
	Round_Block(float x, float y, const Texture& texture, float scale, int durability);  //����������� � ��������� ���� �����
	Round_Block(float* info, const Texture& texture, float scale, int durability);  //����������� ������������ ����� � ������� Get_Next_Position ��� ����������� ������ � ���
	Round_Block(float x, float y, const Texture& texture);                    //����������� ������������ �����

};

