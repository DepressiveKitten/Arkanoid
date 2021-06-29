#pragma once
#include "Game_objects.h"
extern const int win_y, win_x, framerate;
using namespace sf;
class Blocks : public Game_object
{
private:
	int durability;    //прочность блока, по достижении 0 блок уничтоается, спрайт меняется каждые 5 ед. урона
	bool is_bonus;
	int spark_cooldown;
protected:
	float fade_time;   //счётчик используемый при уничтожении для плавного "затухания блока"
public:
	//----------функции
	virtual float* Get_Next_Position(int wight) { std::printf("Bruh"); float* info = new float[2]; info[0] = 0; info[1] = 0; return info; } //заглушка, перегружается в потомках
	void hurt(int damage);  //функция получения урона, вызвать при ударе блока шаром
	int update(RenderWindow& app);   //функция, вызываемая каждый фрейм; обновляет информацию и выводит на экран
	virtual float* Check_Collision(int ball_x, int ball_y, int ball_Radius){ std::printf("Bruh"); float* info = new float[2]; info[0] = 0; info[1] = 0; return info;}//заглушка, перегружается в потомках
	virtual int get_x_size() { std::printf("Bruh"); return 0;};//заглушка, перегружается в потомках
	virtual int get_y_size() { std::printf("Bruh"); return 0;};//заглушка, перегружается в потомках
	//----------конструкторы
	Blocks(float x, float y, float scale, float wight, int durability,const Texture& texture);  //конструктор с заданием всех полей
};

