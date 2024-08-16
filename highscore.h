#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "menu.h"
#include <fstream>

using namespace sf;
using namespace std;

class pauseMenu : public inheritMenu
{
	Clock timer2;			
	Font font;

	string name[3];

	char lettername[15],
		letter;

	fstream highscoreFile;
	Text namesArray,		highscoresIntArray,
			 Entering,		text,		HighscoreText;
	
	string TempText;

	Sprite backgrd;
	Texture backgrdText;

	int Switch,		max,
		score,		i,
		highscore[3];

	bool Name_NotEntered;


public:

	//Normal menu with single column of options
	pauseMenu(Music& menuMusic, bool gap, int posX, int posY, int size, int len)
		:inheritMenu(Color::Red, menuMusic, len, 0, size, 1)
	{
		backgrdText.loadFromFile("images/highScore.png");
		backgrd.setTexture(backgrdText);
		backgrd.setTextureRect(IntRect(0, 0, 254, 189));
		backgrd.setScale(3, 3);
		backgrd.setPosition(300, 30);

		max = 3;				Switch = -1;
		letter = ' ';			i = 0;
		Name_NotEntered = 1;	score = 100;

		for (int i = 0; i < 15; ++i)
			lettername[i] = '\0';

		for (int i = 0; i < max; ++i)
		{
			name[i] = "";
			highscore[i] = 0;
		}

		//font.loadFromFile("Fonts/Amatic-Bold.ttf");
		//font.loadFromFile("Fonts/Roboto-Light.ttf");
		//font.loadFromFile("Fonts/blockletter.regular.otf");
		//font.loadFromFile("Fonts/Poppins-Black.ttf");
		
		font.loadFromFile("Fonts/Grenze-Black.ttf");
		//font.loadFromFile("Fonts/RcRocketRegular-0WVW9.otf");
/*
*/
		HighscoreText.setFont(font);
		HighscoreText.setCharacterSize(66);
		HighscoreText.setFillColor(Color::White);
		HighscoreText.setString("High Score");
		HighscoreText.setPosition(520, 175);

		text.setFont(font);
		text.setCharacterSize(36);
		text.setFillColor(Color::White);
		text.setString("Enter Your Name : ");
		text.setPosition(480, 160);

		Entering.setFont(font);
		Entering.setPosition(500, 200);
		Entering.setCharacterSize(65);
		Entering.setFillColor(sf::Color(167, 231, 200));

		namesArray.setFont(font);
		namesArray.setPosition(650, 280);
		namesArray.setCharacterSize(35);
		namesArray.setFillColor(sf::Color::White);

		highscoresIntArray.setFont(font);
		highscoresIntArray.setPosition(550, 280);
		highscoresIntArray.setCharacterSize(35);
		highscoresIntArray.setFillColor(sf::Color::White);
	}

	int loop( RenderWindow& window , int& Score)
	{
			// File initialization 

			//highscoreFile.open("highscores.txt");
		
		score = Score;

		
		highscoreFile.open("highscores.txt", std::ios::in);

			if (!highscoreFile.is_open())	cout << "Failed to open the file." << std::endl;
			else							cout << "File opened successfully." << std::endl;

			for (int i = 0; i < max; i++) {
				highscoreFile >> name[i];
				highscoreFile >> highscore[i];
			}

			highscoreFile.close();
			TempText = "";
			for (int i = 0; i < max; i++) { //Saving Names from file
				TempText += name[i];
				TempText += '\n';
			}
			namesArray.setString(TempText);

			TempText = "";
			for (int i = 0; i < max; i++) { //Saving Highscores from file
				TempText += std::to_string(highscore[i]);
				TempText += '\n';
			}
			highscoresIntArray.setString(TempText);





			while (Name_NotEntered) 
			{

				window.display();
				window.clear(Color(0, 0, 139));
				window.draw(backgrd);
				Entering.setString(lettername);
				window.draw(namesArray);
				window.draw(highscoresIntArray);
				window.draw(Entering);
				window.draw(text);

				Event E1;

				while (window.pollEvent(E1)) 
				{
					if (E1.type == sf::Event::Closed) 					return -1;
					
					if (E1.type == sf::Event::TextEntered)
					{
						letter = E1.text.unicode;
						if (letter == 13 || i == 10) {
							Name_NotEntered = false; //13 ASCII Value is To Handle 'Enter' 
						}
						if (letter == 8)
						{  //To handle backspace
							if (i > 0) { i--;	lettername[i] = '\0'; }
						}
						else if (letter == ' ')
						{
							lettername[i] = '_';		i++;
						}

						else if (letter != '\n')
						{
							lettername[i] = letter;	i++;
						}
					}
					if (E1.type == sf::Event::KeyPressed && E1.key.code == sf::Keyboard::Left) {
						i--;
					}
				}
			
			
			}

			std::string addInFile, temp;
			for (int i = 0; i < 13; ++i)
			{
				if (lettername[i] != '\0')
					addInFile.push_back(lettername[i]);
			}


	
			for (int j = 0; j < max; j++) {
				if (score > highscore[j]) {
					for (int k = max - 1; k > j; k--) {
						highscore[k] = highscore[k - 1];
						name[k] = name[k - 1];
					}
					highscore[j] = score;
					name[j] = lettername;
					break;
				}
			}

			addInFile = "";
			for (int j = 0; j < max; j++) {
				addInFile += name[j];
				addInFile += " ";
				addInFile += std::to_string(highscore[j]);
				addInFile += "\n";
			}



			highscoreFile.open("highscores.txt");
			highscoreFile << addInFile;
			highscoreFile.close();

			window.display();
			window.clear();

			for (int i = 0; i < max; i++) {
				name[i] = '\0';
				highscore[i] = '\0';
			}
			for (int i = 0; i < 15; ++i)
			{
				lettername[i] = '\0';
			}
			i = 0;
			Name_NotEntered = 1;

			return 0;
		}


	int showHighcore(RenderWindow& window)
	{
		highscoreFile.open("highscores.txt", std::ios::in);

		if (!highscoreFile.is_open())	cout << "Failed to open the file." << std::endl;
		else							cout << "File opened successfully." << std::endl;

		for (int i = 0; i < max; i++) {
			highscoreFile >> name[i];
			highscoreFile >> highscore[i];
		}

		highscoreFile.close();
		TempText = "";
		for (int i = 0; i < max; i++) { //Saving Names from file
			TempText += name[i];
			TempText += '\n';
		}
		namesArray.setString(TempText);

		TempText = "";
		for (int i = 0; i < max; i++) { //Saving Highscores from file
			TempText += std::to_string(highscore[i]);
			TempText += '\n';
		}
		highscoresIntArray.setString(TempText);

		while (window.isOpen())
		{
			window.display();
			window.clear(Color(0, 0, 139));
			window.draw(backgrd);	
			window.draw(highscoresIntArray);
			window.draw(HighscoreText);
			window.draw(namesArray);

			int X = Mouse::getPosition(window).x,
				Y = Mouse::getPosition(window).y;

			Event E1;
			while (window.pollEvent(E1)) {
				if (E1.type == sf::Event::Closed) 					
					return -1;
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && X > 478 && X < 877 && Y > 486 && Y < 560)
					return 0;
			}
		
		}

	}

};



