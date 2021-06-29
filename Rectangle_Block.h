#pragma once
#include "Blocks.h"
class Rectangle_Block : public Blocks
{
private:
	int size_x, size_y;
public:
	//----------функции
	virtual int get_x_size()override { return size_x; };
	virtual int get_y_size()override { return size_y; };
	float* Get_Next_Position(int wight) override;  //использовать вкупе с конструктором, возвращает позицию следующего блока в ряду
	float* Check_Collision(int ball_x, int ball_y, int ball_Radius) override; //получает информацию о шаре, возвращает sin и cos плоскости при сторкновении или 2 2 при отсутствии столкновения
	//----------конструкторы
	Rectangle_Block(float x, float y, const Texture& texture, float scale, float wight, int durability);  //конструктор с указанием всех полей
	Rectangle_Block(float* info, const Texture& texture, float scale, float wight, int durability);  //конструктор используемый вкупе с методом Get_Next_Position Для выставления блоков в ряд
	Rectangle_Block(float x, float y, const Texture& texture);                    //конструктор стандартного блока
};
