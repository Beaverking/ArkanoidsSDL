#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>

#include "leveleditor.h"
#include "brick.h"
#include "game.h"

//Generates level with given pointer of the first pointer of a char array
void LevelEditor::GenerateLevel(const char* lvl, int rows, int cols)
{
	const char* ptr = lvl;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++, ++ptr)
		{
			if (*ptr != '#')
				continue;

			Brick* brick = new Brick();
			printf("brick");
			float wdth = 800 / cols;
			float hgth = 600 / rows;
			

			brick->alive = true;
			brick->x = x * wdth;
			brick->y = y * hgth;
			brick->w = wdth;
			brick->h = hgth;

			bricks[y * cols + x] = brick;
		}
	}
}



//Saves an empty file
void LevelEditor::SaveLevel()
{
	std::string level;

	for (size_t i = 0; i < 256; i++)
	{
		char c = '0';
		level.push_back(c);
	}

	std::ofstream myfile;
	myfile.open("levels/levelEditor.txt", std::ofstream::out | std::ofstream::trunc);

	myfile << level;
	myfile.close();
}

Level LevelEditor::LoadLevel(std::string str)
{
	Level newLevel;

	std::ifstream load(str, std::ifstream::in); //Open file for reading

	std::string newStr;
	std::string tmpStr;

	//Parse first 2 lines to define width and height of level
	std::getline(load, tmpStr);
	newLevel.columns = std::stoi(tmpStr);
	std::cout << newLevel.columns << std::endl;

	std::getline(load, tmpStr);
	newLevel.rows = std::stoi(tmpStr);
	std::cout << newLevel.rows << std::endl;

	//Loop through all the lines after the width and height definition and make it into a string
	for (int i = 0; i < newLevel.columns; i++)
	{
		std::getline(load, tmpStr);
		newStr.append(tmpStr);
	}
	newLevel.levelString = newStr;

	return newLevel;

}

//Returns the entire string from a given file directory
std::string LevelEditor::LoadLevelString(const std::string str)
{
	std::ifstream load(str, std::ifstream::in); //Open file for reading
	
	std::string newStr;
	std::string tmpStr;

	for (int i = 0; i < MAP_COLS; i++)
	{
		std::getline(load, tmpStr);
		newStr.append(tmpStr);
	}

	
	
	return newStr;
	
	
}