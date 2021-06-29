#include "Paddle.h"

int Paddle::update(RenderWindow& app)
{
	if (!is_mouse_control)
	{
		if (sf::Keyboard::isKeyPressed(Keyboard::Key::A) && getx() > 0)               //передвижение влево
		{
			move(-speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::Key::D) && getx() + size_x < win_x)    //передвижение вправо
		{
			move(speed, 0);
		}
	}
	else
	{
		move((sf::Mouse::getPosition(app).x - (getx() + size_x/2))*0.4, 0);
		if (getx() < 0)
			move(-getx(), 0);
		if (getx() + size_x > win_x)
			move(win_x - (getx() + size_x),0);
		if (sf::Mouse::getPosition(app).x < 0)
			sf::Mouse::setPosition(Vector2i(0, sf::Mouse::getPosition(app).y), app);
		if (sf::Mouse::getPosition(app).x > win_x)
			sf::Mouse::setPosition(Vector2i(win_x, sf::Mouse::getPosition(app).y), app);
	}
	show(app);
	return 1;
}

int Paddle::Check_Collision(int ball_x, int ball_y, int ball_Radius)
{
	int angle=0;

	if (gety()-ball_y <= ball_Radius && ball_y <= gety()) //проверка на соприкосновение по вертикали
	{
		int x = getx();
		if (ball_x > x && ball_x < x + size_x)            //проверка на соприкосновение по горозантали
		{
			if ((float)(ball_x - x) / (float)size_x < 0.58 && (float)(ball_x - x) / (float)size_x>0.42) //если шар ударился о центр доски, то он отскочит как от горизонтальной поверхности
				angle = 90;
			if ((float)(ball_x - x) / (float)size_x < 0.42)                                             //если шар ударился о левую часть доски, то он отскочит влево
			{
				angle = 178 * (float)(ball_x - x) / (float)size_x+15;
				angle = 178 - angle;
			}
			if ((float)(ball_x - x) / (float)size_x > 0.58)                                             //если шар ударился о правую часть доски, то он отскочит вправо
			{
				angle = 178 * ((float)1-(float)(ball_x - x) / (float)size_x) + 15;
		    }
		}
	}
	return angle;
}

void Paddle::size_up()
{
	if (size_x >= 250)
		return;
	set_scale((float)(size_x + 20) / size_x, 1);
	size_x += 20;
	return;
}

void Paddle::size_down()
{
	if (size_x <= 150)
		return;
	set_scale((float)size_x / (size_x + 20), 1);
	size_x -= 20;
	return;
}

Paddle::Paddle(const Texture& texture) :Game_object(300,win_y-40,1,200,texture)
{
 	speed = (float)900/framerate;           //поменять если изменится framerate
	size_x = 200;
}