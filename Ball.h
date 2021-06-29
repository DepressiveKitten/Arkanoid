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
	static int radius, damage;    //Радиус, урон и скорость одинаковы для всех шариков и меняются с помощью бонусов(?)  через функции
	static float speed;
	int animation_utility;        //накопительный счетчик для анимации "вращения" шарика
	float sin, cos;               //направления движения шарика
	void angle_reflection(float reflect_sin, float reflect_cos);          //получает sin и cos плоскости и меняет sin и cos шарика (угол падения равен углу отражения)
	void collide(Paddle &paddle,std::list<Blocks*>&);      //проверяет столкновения элементами списка и краями экрана(win_x,win_y), изменение направления движения при необходимости
	void SetAngle(int angle);     //меняет направление полета шарика на переданное в функцию
public:
	//----------функции
	int update(RenderWindow& app,Paddle &paddle, std::list<Blocks*>&);//вызывать каждый фрейм для обновления информации и отрисовки шарика
	static int get_radius() { return radius; };
	static void reset();         //возвращет статические поля шариков к начальным значениям
	static void winning_transition() { speed *= (float)0.99; };
	static void speed_up() { if (speed <= (float)900 / framerate)speed *= 1.1; };    //добавить бонусы
	static void speed_down() { if (speed >= (float)300 / framerate)speed /= 1.1; };
	static void size_up() { if (damage < 9) { std::round(radius = radius * 1.15 + 0.01); damage++; } };
	static void size_down() { if (damage > 3) { std::round(radius = radius / 1.15 + 0.01); damage--; }};
	void texture_size_up() { if (damage < 9) set_scale(1.15, 1.15); };
	void texture_size_down() { if (damage > 3) set_scale(1/1.15, 1/1.15); };
	//конструкторы
	Ball(float x, float y, const Texture& texture, float sin, float cos); //конструктор с обьявлением всех полей вручную
};

