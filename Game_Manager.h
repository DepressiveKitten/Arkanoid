#pragma once
#include "My_Exeptions.h"
#include <iostream>
#include "Bonus.h"
#include "particles.h"
#include "Rectangle_Block.h"
#include "Round_Block.h"
#include "Ball.h"
#include "Paddle.h"
#include <fstream>

extern const int win_y, win_x,framerate;
extern std::map<std::ifstream*, std::string> stream_file_table;

class Game_Manager
{
private:
	Font font;
	int game_state;            //2-���� �� ������, 1 - ���� ������, 0 - ���� ���������
	Texture *common_textures;  //0 - background, 1 - paddle, 2-4 - ball, 5 - ���� ������, 6 spark, 7+ ������(background ����������� �� ������� �����)
	Texture *textures;         //�����
	std::list<Blocks*> blocks; //������ ������
	std::list<Ball> balls;     //������ �������
	Paddle *paddle;            //�����
	RenderWindow *app;         //���� ������
	Sprite background;         //���
	std::list<Bonus> bonuses;
	std::list<Particles> particles;   //�������
    void activate_bonus(bonus_name name);
	void Endgame(bool);
	bool isAnyKeyPressed();
public:
	//�������
	void Play();               //������� ����� �������� ���� �������� ����� �����������
	//�����������,����������
	Game_Manager(std::ifstream &data, RenderWindow *app); //data - ���� � ������������� ������
	~Game_Manager();
};


