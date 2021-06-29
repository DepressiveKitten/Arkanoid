#pragma once
#include <iostream>
#include <exception>
class Corrupted_File:public std::exception
{
private:
	char const* path;
public:
	Corrupted_File()
	{
		path = "unknown file";
	}
	Corrupted_File(char const* path)
	{
		this->path = path;
	}
	Corrupted_File(char const* path, char const* message):exception(message)
	{
		this->path = path;
	}
	char const* get_path()
	{
		return path;
	}
};

class Missng_Texture :public Corrupted_File
{
public:
	Missng_Texture() :Corrupted_File("unknown file", "missing texture") {};
	Missng_Texture(char const* path) :Corrupted_File(path, "missing texture") {};
	Missng_Texture(char const* path, char const* message) :Corrupted_File(path, message) {};
};

class Bad_Data :public Corrupted_File
{
public:
	Bad_Data() :Corrupted_File("unknown file", "bad data") {};
	Bad_Data(char const* path) :Corrupted_File(path, "bad data") {};
	Bad_Data(char const* path, char const* message) :Corrupted_File(path, message) {};
	char const* structure()
	{
		return "Please use following structure: позиция по x; позиция по y; квадрат/круг(0/1); номер текстуры; масштаб; ширина спрайта; прочость; кол-во блоков в ряд;";
	}
};

class Manager_Exeption
{
private:
	int exc_state;
	int memory_state;
	Corrupted_File corrupted_file;
	Missng_Texture missng_texture;
	Bad_Data bad_data;
public:
	Manager_Exeption(int memory_state, Corrupted_File data)
	{
		this->memory_state = memory_state;
		corrupted_file = data;
		exc_state = 1;
	}
	Manager_Exeption(int memory_state, Missng_Texture data)
	{
		this->memory_state = memory_state;
		missng_texture = data;
		exc_state = 2;
	}
	Manager_Exeption(int memory_state, Bad_Data data)
	{
		this->memory_state = memory_state;
		bad_data = data;
		exc_state = 3;
	}
	int get_state() { return memory_state; };
	int get_exc_state() { return exc_state; };
	Corrupted_File& get_corrupted_file() { return corrupted_file; };
	Missng_Texture& get_missng_texture() { return missng_texture; };
	Bad_Data& get_bad_data() { return bad_data; };

};