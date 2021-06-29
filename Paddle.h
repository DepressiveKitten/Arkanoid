#pragma once
#include "Game_objects.h"
extern const int win_y, win_x, framerate;
class Paddle :
    public Game_object
{
private:
    static bool is_mouse_control;
    int size_x;
    float speed;
public:
    static void switch_control() { if (is_mouse_control)is_mouse_control = false; else is_mouse_control = true; };
    int update(RenderWindow& app);
    int Check_Collision(int ball_x, int ball_y, int ball_Radius); //получает информацию о шаре, возвращает угол его отражения или 0 если нет пересечения
    int get_size() { return size_x; };
    void size_up() ;
    void size_down() ;

    Paddle(const Texture& texture);
};