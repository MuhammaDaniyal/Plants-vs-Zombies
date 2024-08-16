#pragma once
#include<iostream>
#include<ctime>
#include <SFML/Graphics.hpp>
#include "Zombie.h"
#include "spriteAnimation.h"
#include "rect.h"

using namespace sf;
using namespace std;

class Levels {

protected:
	Texture selectTextureNormal;
	Sprite selectionNormal;

	Texture mapTexture;
	Sprite s_map;

	Texture sunBoardTexture;
	Sprite sunBoardSprite;

	Font font;								//Initializing font
	
	Text textSun;							//Text for score
	Text lev, scor;
	
	plant* arr[45];
	gridRect rect;

	sun Sun;

	Clock clk, selectClk;

	int posX, posY, gap,		// For normal pea selections
		sunNo,					// For sun Numbers
		lawnPosX, lawnPosY;		// lawnmower positions
	const int ROWS, COLS;

	char FIELD_GAME_STATUS[5][9];

	Texture lawnText;
	Sprite lawnMowerSprite[5];

public:
	ZombieFactory* zom;
	Clock WaveClock;
	double waveCheck[15];
	virtual void drawZombie(RenderWindow& window) = 0;

	Levels() : posX(20), posY(100), gap(70), ROWS(5), COLS(9)
	{
		font.loadFromFile("Fonts/Amatic-Bold.ttf");
		sunNo = 200;
		textSun.setFont(font);
		textSun.setCharacterSize(36);
		textSun.setFillColor(Color::Black);
		textSun.setString("Suns " + to_string(sunNo));
		textSun.setPosition(30, 20);
	
		lev.setFont(font);
		lev.setCharacterSize(60);
		lev.setFillColor(Color::Red);
		lev.Bold;
		lev.setLetterSpacing(5);
		lev.setOutlineThickness(5);
		lev.setPosition(450, 0);
		
		scor.setFont(font);
		scor.setCharacterSize(50);
		scor.setFillColor(Color::Green);
		scor.Bold;
		scor.setLetterSpacing(4);
		scor.setOutlineThickness(3);
		scor.setPosition(1170, 0);

		lawnPosX = 190;		lawnPosY = 110;
		lawnText.loadFromFile("Sprites_update/Plants/lawnMower.png");
		for (int i = 0; i < 5; ++i)
		{
			lawnMowerSprite[i].setTexture(lawnText);
			lawnMowerSprite[i].setTextureRect(IntRect(0, 0, 244, 207));
			lawnMowerSprite[i].setPosition(lawnPosX, lawnPosY);
			lawnMowerSprite[i].setScale(0.3, 0.3);
			lawnPosY += 96;
		}


		for (int i = 0; i < 45; ++i)
			arr[i] = nullptr;

		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++)
				FIELD_GAME_STATUS[i][j] = ' ';

		selectTextureNormal.loadFromFile("Sprites_update/Plants/selectNormal.png");
		selectionNormal.setTexture(selectTextureNormal);
		selectionNormal.setTextureRect(IntRect(0, 0, 25, 26));
		selectionNormal.setPosition(posX, posY);
		selectionNormal.setScale(3, 2.5);
	}

	virtual int gameloop(RenderWindow& window, int& score) = 0;
	void printGrid(char array1[5][9], const int ROWS, const int COLS)
	{
		cout << "-------------------------------------------------\n    ";

		for (int i = 0; i < COLS; ++i)
			cout << i + 1 << " ";
		cout << endl;
		for (int row = 0; row < ROWS; ++row)
		{
			cout << row + 1 << " | ";
			for (int col = 0; col < COLS; ++col)
				cout << array1[row][col] << " ";
			cout << endl;
		}
		cout << "\n------------------------------------------------------\n";
	}

};