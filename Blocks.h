#pragma once
#include "Game_objects.h"
extern const int win_y, win_x, framerate;
using namespace sf;
class Blocks : public Game_object
{
private:
	int durability;    //��������� �����, �� ���������� 0 ���� �����������, ������ �������� ������ 5 ��. �����
	bool is_bonus;
	int spark_cooldown;
protected:
	float fade_time;   //������� ������������ ��� ����������� ��� �������� "��������� �����"
public:
	//----------�������
	virtual float* Get_Next_Position(int wight) { std::printf("Bruh"); float* info = new float[2]; info[0] = 0; info[1] = 0; return info; } //��������, ������������� � ��������
	void hurt(int damage);  //������� ��������� �����, ������� ��� ����� ����� �����
	int update(RenderWindow& app);   //�������, ���������� ������ �����; ��������� ���������� � ������� �� �����
	virtual float* Check_Collision(int ball_x, int ball_y, int ball_Radius){ std::printf("Bruh"); float* info = new float[2]; info[0] = 0; info[1] = 0; return info;}//��������, ������������� � ��������
	virtual int get_x_size() { std::printf("Bruh"); return 0;};//��������, ������������� � ��������
	virtual int get_y_size() { std::printf("Bruh"); return 0;};//��������, ������������� � ��������
	//----------������������
	Blocks(float x, float y, float scale, float wight, int durability,const Texture& texture);  //����������� � �������� ���� �����
};

