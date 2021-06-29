#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

typedef enum bonus_name { eightball, triball, threeball, slowball, fastball, smallball, normalball, expandboard, shrinkboard, win,fly,dead };

class Game_object
{
private:
	int cur_frame, texture_wight; //���������� � �������� �������
	float pos_x, pos_y;           //������� �������
	Sprite image;
public:
	//----------�������
	void show(RenderWindow& app); //������������ ������
	virtual int update() { return 0; }   //������� ���������� ������ �����
	void Next_Sprite();           //������� �� ��������� ��������
	void move(float x,float y);   //����������� �������
	void fading(float visibility)       //������ ������������
	{
		image.setColor(Color(255, 255, 255, (int)((float)255 * visibility)));
	}
	void set_scale(float scalex,float scaley)    //���������� ������� � scalex � scaley ���
	{
		image.setScale(image.getScale().x*scalex, image.getScale().y*scaley);
	}
	//get-���� �������
	float getx()
	{
		return pos_x;
	}
	float gety()
	{
		return pos_y;
	}
	//----------������������
	Game_object(float x, float y,float scale, int texture_wight, const Texture &texture);
};