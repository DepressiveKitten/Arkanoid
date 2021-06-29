//структура файла: 
//1)кол-во подгружаемых текстур
//2)пути до текстур
//3)кол-во блоков
//4)блоки построчто
//запись блока:
//позиция по x;1   позиция по y;   квадрат/круг(0/1);   текстура(номер из тех которые загрузили);   масштаб;   ширина спрайта;   прочость;    кол-во этих блоков в ряд
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game_Manager.h"
#include <fstream>
#include <exception>

const int win_y = 810,win_x=1080,framerate=150;
std::map<std::ifstream*, std::string> stream_file_table;

using namespace sf;
using namespace std;
bool Paddle::is_mouse_control = true;
int Ball::radius;
int Ball::damage;
float Ball::speed;
float Ball::angles[91];

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    Ball::reset();
    ifstream Level_list("Levels/List.txt");
    int amount;
    Level_list >> amount;
    std::list<string> names;
    std::list<string> path;
    string controller = "mouse";
    for (int i = 0; i < amount; i++)
    {
        string temp;
        Level_list >> temp;
        path.push_back(temp);
        getline(Level_list, temp);
        names.push_back(temp);
    }
    for (bool ingame = true; ingame;)
    {
        cout << "List of levels:" << endl;
        auto n = names.begin();
        for (int i = 0; i < amount; i++,n++)
            cout << i + 1 << "." << *n << endl;
        cout << endl<<"Press:"<<endl<<"1. Choose level" << endl << "2. Change control(current - "<<controller<<")" << endl << "3. Exit"<<endl;
        int checker;
        cin >> checker;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (checker)
        {
        case 1:
        {
            cout << "Choose level - ";
            int temp;
            cin >> temp;
            if (temp<=amount&&temp>0)
            {
                try
                {
                    auto path_handler = path.begin();
                    for (int i = 1; i < temp; i++, path_handler++);
                    ifstream Level(*path_handler);
                    stream_file_table[&Level] = *path_handler;
                    sf::RenderWindow app(VideoMode(win_x, win_y), "Arkanoid!");
                    app.setFramerateLimit(framerate);
                    Game_Manager check = Game_Manager(Level, &app);
                    check.Play();
                }
                catch (Missng_Texture& exc)
                {
                    system("CLS");
                    cout << exc.get_path() << endl << exc.what();
                    std::cout << endl << endl;
                    continue;
                }
                catch (Bad_Data& exc)
                {
                    system("CLS");
                    cout << exc.get_path() << endl << exc.what() << endl << exc.structure();
                    std::cout << endl << endl;
                    continue;
                }
                catch (Corrupted_File& exc)
                {
                    system("CLS");
                    cout << exc.get_path() << endl << exc.what();
                    std::cout << endl << endl;
                    continue;
                }
                catch (std::exception& exc)
                {
                    system("CLS");
                    std::cout << "Непредвиденая ошибка: " << exc.what();
                    abort();
                }
            }
            system("CLS");
            break;
        }
        case 2:
        {
            if (controller == "mouse")
                controller = "keyboard";
            else
                controller = "mouse";
            Paddle::switch_control();
            system("CLS");
            break;
        }
        case 3:
        {
            system("CLS");
            cout << endl << "See you soon" << endl;
            ingame = false;
            break;
        }
        default:
        {
            system("CLS");
            break;
        }
        }
    }
    return 0;
}