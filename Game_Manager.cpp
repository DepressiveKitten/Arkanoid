#define _CRT_SECURE_NO_WARNINGS
#include "Game_Manager.h"
//функции
void Game_Manager::Play()
{
	Ball::reset();
	int pull_cooldown = framerate;        //временна€ переменна€, кулдаун ручного растроени€ шарика
	int win_cooldown = framerate;
	int trail = 0;
	float spark_size = 0.5;
	while (app->isOpen())
	{
		Event event;
		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app->close();
		}

		//-------------------------------------------------------------------------------

		if (game_state == 2 &&( sf::Mouse::isButtonPressed(sf::Mouse::Left)|| sf::Keyboard::isKeyPressed(Keyboard::Key::W)))//ƒобавление шарика в начале по клику мышки или W
		{
			game_state = 1;
			balls.push_back(Ball(paddle->getx()+100, paddle->gety()-20, common_textures[2], 0.87, 0.5));
		}

		//-------------------------------------------------------------------------------

		if (pull_cooldown > 0)                                                                            //случайный бонус через enter 
			pull_cooldown--;
		if (sf::Keyboard::isKeyPressed(Keyboard::Key::Enter) && pull_cooldown == 0)
		{
			pull_cooldown = framerate;
				bonuses.push_back(Bonus(rand() % (win_x - 50), rand() % 300, common_textures, static_cast<bonus_name>(rand() % win)));
		}                                                                                                 //
		app->clear();
		app->draw(background);

		//-------------------------------------------------------------------------------

		for (auto i = blocks.begin(); i != blocks.end(); )//обновление блоков, удаление если они уничтожены
		{
			int state = (*i)->update(*app);
			if (state == 0 || state == 3)
			{
				if (state == 3)
				{
					bonuses.push_back(Bonus((*i)->getx()+ (*i)->get_x_size()/2-common_textures[7].getSize().y/2, (*i)->gety(), common_textures, static_cast<bonus_name>(rand() % win)));
				}
				i = blocks.erase(i);
				continue;
			}
			if (state == 2)
			{
				particles.push_back(Particles((*i)->getx()+rand()%(int)((*i)->get_x_size()- common_textures[6].getSize().x* spark_size), (*i)->gety() + rand() % (int)((*i)->get_y_size() - common_textures[6].getSize().y * spark_size), common_textures[6], (float)1/framerate, 0, 1, spark_size));
			}
			i++;
		}
		if (blocks.size() <= 5)
		{
			win_cooldown--;
			if (win_cooldown == 0)
			{
				win_cooldown = 4 * framerate;
				bonuses.push_back(Bonus(rand() % (win_x - 50), rand() % 300, common_textures, win));
			}
		}
		if (blocks.empty())
			Endgame(true);

		//-------------------------------------------------------------------------------

		for (auto i = particles.begin(); i != particles.end(); )//обновление частиц, удаление если они исчезли
		{
			if (!(*i).update(*app))
			{
				i = particles.erase(i);
				continue;
			}
			i++;
		}

		//-------------------------------------------------------------------------------

		trail--;
		for (auto i = balls.begin(); i != balls.end();) //обновление шариков, удаление если они выпали за экран
		{
			if (trail == 0)
				particles.push_back(Particles((*i).getx(), (*i).gety(), common_textures[5], (float)Ball::get_radius() * 2 / common_textures[5].getSize().x));
			if (!(*i).update(*app, *paddle, blocks))
			{
				i = balls.erase(i);
				continue;
			}
			i++;
		}
		if (trail <= 0)
			trail = framerate / 30;
		if (balls.empty() && game_state == 1)
			Endgame(false);
		//-------------------------------------------------------------------------------

		for (auto i = bonuses.begin(); i != bonuses.end(); )
		{
			bonus_name temp = (*i).update(*app, *paddle);
			if (temp!=fly)
			{
				i = bonuses.erase(i);
				if (temp != dead)
				{
					try
					{
						activate_bonus(temp);
					}
					catch (std::runtime_error& exc)
					{
						std::cout << exc.what()<<std::endl;
					}
				}
				continue;
			}
			i++;
		}

		paddle->update(*app);
		if (!game_state)
			return;
		app->display();
	}
}

void Game_Manager::activate_bonus(bonus_name name)
{
	switch (name)
	{
	case eightball:
	{
		if (balls.size() >= 300)
			throw std::runtime_error("Ќевозможно создать больше обьектов");
		if (balls.empty())
			throw std::runtime_error("из-за отсутстви€ шаров невозможен вызов бонуса");
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], 0.7, 0.7));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], 0.7, -0.7));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], -0.7, 0.7));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], -0.7, -0.7));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], 1, 0));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], 0.17, 1));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], -1, 0));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], 0.17, -1));
		break;
	}
	case triball:
	{
		if (balls.empty())
			throw std::runtime_error("из-за отсутстви€ шаров невозможен вызов бонуса");
		int counter=0;
		int size = balls.size();
		for (auto i = balls.begin(); counter<size;i++,counter++) 
		{
			balls.push_back(Ball((*i).getx(), (*i).gety(), common_textures[2], 0.7, 0.7));
			balls.push_back(Ball((*i).getx(), (*i).gety(), common_textures[2], 0.7, -0.7));
			if(balls.size()>=300)
				throw std::runtime_error("Ќевозможно создать больше обьектов");
		}
		break;
	}
	case threeball:
	{

		if (balls.empty())
			throw std::runtime_error("из-за отсутстви€ шаров невозможен вызов бонуса");
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], 0.7, 0.7));
		balls.push_back(Ball(balls.begin()->getx(), balls.begin()->gety(), common_textures[2], 0.7, -0.7));
		break;
	}
	case slowball:
	{
		Ball::speed_down();
		break;
	}
	case fastball:
	{
		Ball::speed_up();
		break;
	}
	case smallball:
	{
		for (auto i = balls.begin(); i != balls.end(); i++)
		{
			(*i).texture_size_down();
		}
		Ball::size_down();
		break;
	}
	case normalball:
	{
		for (auto i = balls.begin(); i != balls.end(); i++)
		{
			(*i).texture_size_up();
		}
		Ball::size_up();
		break;
	}
	case expandboard:
	{
		paddle->size_up();
		break;
	}
	case shrinkboard:
	{
		paddle->size_down();
		break;
	}
	case win:
	{
		Endgame(true);
		break;
	}
	default:
	{
		std::printf("Bug");
		break;
	}
	}
}

void Game_Manager::Endgame(bool is_win)
{
	int fading_speed = 255;
    float text_brightness=0;
	float reminder_brightness = -1275;
	bool text_utility = true;
	game_state = 0;
	int trail = 0;
	float spark_size = 0.5;
	Text text("“ы победил", font, 100);	
	text.setString("“ы победил");
	text.setPosition(230, 150);
	if (!is_win)
	{
		text.setString("“ы проиграл");
		text.setPosition(204, 150);
	}
    text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color(0, 0, 0, 0));
	text.setFillColor(sf::Color(255, 117, 24, 0));

	Text reminder("Ќажми любую кнопку",font,40);
	reminder.setOutlineThickness(1);
	reminder.setOutlineColor(sf::Color(0, 0, 0, 0));
	reminder.setFillColor(sf::Color(235, 176, 40, 0));
	reminder.setPosition(293, 255);
	while (app->isOpen())
	{
		Event event;
		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app->close();
		}
		if (isAnyKeyPressed())
		{
			return;
		}
		app->clear();
		app->draw(background);

		//-------------------------------------------------------------------------------

		for (auto i = blocks.begin(); i != blocks.end(); )//обновление блоков, удаление если они уничтожены
		{
			if ((*i)->update(*app) == 2)
				particles.push_back(Particles((*i)->getx() + rand() % (int)((*i)->get_x_size() - common_textures[6].getSize().x * spark_size), (*i)->gety() + rand() % (int)((*i)->get_y_size() - common_textures[6].getSize().y * spark_size), common_textures[6], (float)1 / framerate, 0, 1, spark_size));
			i++;
		}

		//-------------------------------------------------------------------------------

		for (auto i = particles.begin(); i != particles.end(); )//обновление частиц, удаление если они исчезли
		{
			if (!(*i).update(*app))
			{
				i = particles.erase(i);
				continue;
			}
			i++;
		}

		//-------------------------------------------------------------------------------

		Ball::winning_transition();
		trail--;
		for (auto i = balls.begin(); i != balls.end();) //обновление шариков, удаление если они выпали за экран
		{
			if (trail == 0)
				particles.push_back(Particles((*i).getx(), (*i).gety(), common_textures[5], (float)Ball::get_radius() * 2 / common_textures[5].getSize().x));
			(*i).update(*app, *paddle, blocks);
			i++;
		}
		if (trail <= 0)
			trail = framerate / 30;

		//-------------------------------------------------------------------------------

		for (auto i = bonuses.begin(); i != bonuses.end(); )
		{
			(*i).update(*app, *paddle);
			i++;
		}
		paddle->show(*app);
		if(text_utility)
		    text_brightness += (float)fading_speed / framerate;
		else
			text_brightness -= (float)fading_speed / framerate;
		if (text_brightness >= 230)
		{
			fading_speed = 30;
			text_utility = false;
		}
		if(text_brightness<=180)
			text_utility = true;
		text.setOutlineColor(sf::Color(0, 0, 0, text_brightness));
		text.setFillColor(sf::Color(255, 117, 24, text_brightness));
		app->draw(text);
		if (reminder_brightness < 230)
			reminder_brightness += (float)255 / framerate;
		if (reminder_brightness > 0)
		{
			reminder.setOutlineColor(sf::Color(0, 0, 0, reminder_brightness));
			reminder.setFillColor(sf::Color(235, 176, 40, reminder_brightness));
		}
		app->draw(reminder);
		app->display();
	}
	return;
}

bool Game_Manager::isAnyKeyPressed()
{
	for (int k = 0; k < sf::Keyboard::KeyCount; ++k)
	{
		if (k == 76)
			continue;
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
		{
			return true;
		}
	}
	return false;
}
//конструктор,деструктор
Game_Manager::Game_Manager(std::ifstream& data, RenderWindow* app)
{
	//std::cout << stream_file_table[&data];
	try
	{
		game_state = 2;
		this->app = app;
		int amount;

		//-------------------------------------------------------------------------------

		std::ifstream common("Levels/common.txt");
		common >> amount;                    //считываем кол-во текстур уровн€
		if (common.fail())
			throw Manager_Exeption(0, Corrupted_File("Levels/common.txt", "отсутвует кол-во текстур "));
		common_textures = new Texture[amount+1];
		for (int i = 1; i < amount+1; i++)   //считываем пути к текстурам
		{
			std::string temp;
			common >> temp;
			if (common.fail())
				throw Manager_Exeption(1, Corrupted_File("Levels/common.txt","расхождение в кол-ве текстур "));
			if (!common_textures[i].loadFromFile(temp))
			{
				char* cstr = new char[temp.length() + 1];
				strcpy(cstr, temp.c_str());
				throw Manager_Exeption(1, Missng_Texture(cstr));
			}
		}

		//-------------------------------------------------------------------------------

		data >> amount;                   //считываем кол-во текстур уровн€
		if(data.fail())
			throw Manager_Exeption(1, Corrupted_File(stream_file_table[&data].c_str(), "отсутвует кол-во текстур "));
		

		//-------------------------------------------------------------------------------
        std::string temp;
		data >> temp;
		if (data.fail())
			throw Manager_Exeption(1, Corrupted_File(stream_file_table[&data].c_str(), "расхождение в кол-ве текстур "));
		if (!common_textures[0].loadFromFile(temp))
		{
			char* cstr = new char[temp.length() + 1];
			strcpy(cstr, temp.c_str());
			throw Manager_Exeption(1, Missng_Texture(cstr));
		}

		//-------------------------------------------------------------------------------

		textures = new Texture[amount-1];
		for (int i = 0; i < amount-1; i++)   //считываем пути к текстурам
		{
			std::string temp;
			data >> temp;
			if(data.fail())
				throw Manager_Exeption(2, Corrupted_File(stream_file_table[&data].c_str(), "расхождение в кол-ве текстур "));
			if (!textures[i].loadFromFile(temp))
			{
				char* cstr = new char[temp.length() + 1];
				strcpy(cstr, temp.c_str());
				throw Manager_Exeption(2, Missng_Texture(cstr));
			}
		}

		//-------------------------------------------------------------------------------

		common_textures[0].setRepeated(true);                         //
		background.setTexture(common_textures[0]);                    //устанавливаетс€ фон
		background.setTextureRect(IntRect(0, 0, win_x, win_y));//
		paddle = new Paddle(common_textures[1]);          //добавление доски
		data >> amount;     //считываетс€ кол-во кластеров блоков
		if(data.fail())
			throw Manager_Exeption(3, Corrupted_File(stream_file_table[&data].c_str(), "отсутвует кол-во блоков "));
		for (int i = 0; i < amount; i++)
		{
			int x, y, form, texture_num, wight, durability, row;
			float scale;
			data >> x >> y >> form >> texture_num >> scale >> wight >> durability >> row;  // считывание всей информации о кластере
			if (data.fail())
				throw Manager_Exeption(3, Bad_Data(stream_file_table[&data].c_str()));
			if (form == 0)        //добавление пр€моугольных блоков
			{
				Rectangle_Block* temp = new Rectangle_Block(x, y, textures[texture_num], scale, wight, durability);
				blocks.push_back(temp);
				for (int j = 1; j < row; j++)
				{
					Rectangle_Block* temp = new Rectangle_Block(blocks.back()->Get_Next_Position(wight * scale), textures[texture_num], scale, wight, durability);
					blocks.push_back(temp);
				}
			}
			if (form == 1)        //добавление круглых блоков
			{
				Round_Block* temp = new Round_Block(x, y, textures[texture_num], scale, durability);
				blocks.push_back(temp);
				for (int j = 1; j < row; j++)
				{
					Round_Block* temp = new Round_Block(blocks.back()->Get_Next_Position(wight * scale), textures[texture_num], scale, durability);
					blocks.push_back(temp);
				}
			}
		}
		if(!font.loadFromFile("Data/Fonts/DexterC.TTF"))
			throw Manager_Exeption(3, Corrupted_File("Data/Fonts/DexterC.TTF", "отсутвует шрифт"));
	}
	catch(Manager_Exeption exc)
	{
		if(exc.get_state()<2)
			delete[] common_textures;
		if (exc.get_state() < 3)
			delete[] textures;
		if (exc.get_state() < 4)
		{
			for (auto i = blocks.begin(); i != blocks.end(); i++)
			{
				delete (*i);
			}
			blocks.clear();
			delete paddle;
		}		
		if (exc.get_exc_state() == 1)
			throw exc.get_corrupted_file();
		if (exc.get_exc_state() == 2)
			throw exc.get_missng_texture();
		if (exc.get_exc_state() == 3)
			throw exc.get_bad_data();

	}
	catch (std::exception exc)
	{
		std::cout << "Ќепредвидена€ ошибка: " << exc.what();
		abort();
	}
}

Game_Manager::~Game_Manager()          //очищаем всю пам€ть
{
	delete[] textures;
	delete[] common_textures;
	for (auto i = blocks.begin(); i != blocks.end(); i++)
	{
		delete (*i);
	}
	blocks.clear();
	balls.clear();
	particles.clear();
	bonuses.clear();
	delete paddle;
}
