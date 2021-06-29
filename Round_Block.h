#pragma once
#include "Blocks.h"
extern const int win_y, win_x;
class Round_Block : public Blocks
{
private:
	int radius;
public :
	//----------функции
	int get_x_size()override { return radius; };
	int get_y_size()override { return radius; };
	float* Get_Next_Position(int wight) override;   //использовать вкупе с конструктором, возвращает позицию следующего блока в ряду
	float* Check_Collision(int ball_x, int ball_y, int ball_Radius) override; //получает информацию о шаре, возвращает sin и cos плоскости при сторкновении или 2 2 при отсутствии столкновения
	//----------конструкторы
	Round_Block(float x, float y, const Texture& texture, float scale, int durability);  //конструктор с указанием всех полей
	Round_Block(float* info, const Texture& texture, float scale, int durability);  //конструктор используемый вкупе с методом Get_Next_Position Для выставления блоков в ряд
	Round_Block(float x, float y, const Texture& texture);                    //конструктор стандартного блока

};

