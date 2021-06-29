#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Blocks.h"
#include "Paddle.h"
#include <list>
extern const int win_y, win_x, framerate;
using namespace sf;
class Ball : public Game_object
{
private:
	static float angles[91];
	static int radius, damage;    //������, ���� � �������� ��������� ��� ���� ������� � �������� � ������� �������(?)  ����� �������
	static float speed;
	int animation_utility;        //������������� ������� ��� �������� "��������" ������
	float sin, cos;               //����������� �������� ������
	void angle_reflection(float reflect_sin, float reflect_cos);          //�������� sin � cos ��������� � ������ sin � cos ������ (���� ������� ����� ���� ���������)
	void collide(Paddle &paddle,std::list<Blocks*>&);      //��������� ������������ ���������� ������ � ������ ������(win_x,win_y), ��������� ����������� �������� ��� �������������
	void SetAngle(int angle);     //������ ����������� ������ ������ �� ���������� � �������
public:
	//----------�������
	int update(RenderWindow& app,Paddle &paddle, std::list<Blocks*>&);//�������� ������ ����� ��� ���������� ���������� � ��������� ������
	static int get_radius() { return radius; };
	static void reset();         //��������� ����������� ���� ������� � ��������� ���������
	static void winning_transition() { speed *= (float)0.99; };
	static void speed_up() { if (speed <= (float)900 / framerate)speed *= 1.1; };    //�������� ������
	static void speed_down() { if (speed >= (float)300 / framerate)speed /= 1.1; };
	static void size_up() { if (damage < 9) { std::round(radius = radius * 1.15 + 0.01); damage++; } };
	static void size_down() { if (damage > 3) { std::round(radius = radius / 1.15 + 0.01); damage--; }};
	void texture_size_up() { if (damage < 9) set_scale(1.15, 1.15); };
	void texture_size_down() { if (damage > 3) set_scale(1/1.15, 1/1.15); };
	//������������
	Ball(float x, float y, const Texture& texture, float sin, float cos); //����������� � ����������� ���� ����� �������
};

