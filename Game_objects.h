#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

typedef enum bonus_name { eightball, triball, threeball, slowball, fastball, smallball, normalball, expandboard, shrinkboard, win,fly,dead };

class Game_object
{
private:
	int cur_frame, texture_wight; //информация о текстуре обьекта
	float pos_x, pos_y;           //позиция обьекта
	Sprite image;
public:
	//----------функции
	void show(RenderWindow& app); //отрисовывает обьект
	virtual int update() { return 0; }   //функция вызываемая каждый фрейм
	void Next_Sprite();           //переход на следующую текстуру
	void move(float x,float y);   //перемещение обьекта
	void fading(float visibility)       //задане прозрачности
	{
		image.setColor(Color(255, 255, 255, (int)((float)255 * visibility)));
	}
	void set_scale(float scalex,float scaley)    //растяжение спрайта в scalex и scaley раз
	{
		image.setScale(image.getScale().x*scalex, image.getScale().y*scaley);
	}
	//get-теры позиции
	float getx()
	{
		return pos_x;
	}
	float gety()
	{
		return pos_y;
	}
	//----------конструкторы
	Game_object(float x, float y,float scale, int texture_wight, const Texture &texture);
};