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
	int game_state;            //2-игра не начата, 1 - игра начата, 0 - игра закончена
	Texture *common_textures;  //0 - background, 1 - paddle, 2-4 - ball, 5 - след шарика, 6 spark, 7+ бонусы(background загружаетс€ из другого файла)
	Texture *textures;         //блоки
	std::list<Blocks*> blocks; //список блоков
	std::list<Ball> balls;     //список м€чиков
	Paddle *paddle;            //доска
	RenderWindow *app;         //окно вывода
	Sprite background;         //фон
	std::list<Bonus> bonuses;
	std::list<Particles> particles;   //частицы
    void activate_bonus(bonus_name name);
	void Endgame(bool);
	bool isAnyKeyPressed();
public:
	//функции
	void Play();               //вызвать чтобы провести игру заданную через конструктор
	//конструктор,деструктор
	Game_Manager(std::ifstream &data, RenderWindow *app); //data - файл с конфигурацией уровн€
	~Game_Manager();
};


