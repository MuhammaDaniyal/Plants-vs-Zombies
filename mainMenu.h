#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.h"
#include <string>

using namespace sf;
using namespace std;

class mainMenu : public inheritMenu
{
	int length;						//extra

	Sprite startSprite;
	Texture startText;

	Sprite moreSprite;
	Texture moreText;

	sf::Texture backgroundTextureMain;
	sf::Sprite backgroundSpriteMain;

	Text highScoreText;

public:

	//Normal menu with single column of options
	mainMenu(Music& menuMusic, bool gap, int posX, int posY, int size, int len)
		:inheritMenu(Color::Red, menuMusic, 5, 0, size, 0)
	{
		backgroundTextureMain.loadFromFile("images/bk2.jpeg");
		backgroundSpriteMain.setTexture(backgroundTextureMain);
		backgroundSpriteMain.setColor(sf::Color(255, 255, 255, 255 * 0.9)); // Reduces Opacity of the background

		length = 3;
		current = 0;

		highScoreText.setFont(font);
		highScoreText.setCharacterSize(36);
		highScoreText.setFillColor(Color::Black);
		highScoreText.setString("HighScores");
		highScoreText.setPosition(410, 450);


		startText.loadFromFile("images/start.png");
		startSprite.setTexture(startText);
		startSprite.setTextureRect(IntRect(0, 0, 112, 82));
		startSprite.setScale(3.8, 3);
		startSprite.setPosition(640, 130);

		moreText.loadFromFile("images/more.png");
		moreSprite.setTexture(moreText);
		moreSprite.setTextureRect(IntRect(0, 0, 93, 71));
		moreSprite.setScale(3.5, 3.5);
		moreSprite.setPosition(660, 300);
	
	}


	

	int loop(RenderWindow& window)
	{
		int Switch = -1;

		while (window.isOpen())
		{


			window.draw(backgroundSpriteMain);
			sf::Event M;
		
			window.draw(startSprite);
			window.draw(moreSprite);
			window.draw(highScoreText);

			int X = Mouse::getPosition(window).x,
				Y = Mouse::getPosition(window).y;



			while (window.pollEvent(M))
			{
				if (closeWindow(M, window))			return -1;

				int X = Mouse::getPosition(window).x,
					Y = Mouse::getPosition(window).y;

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && X > 673 && X < 998 && Y > 215 && Y < 333)			return 1;	// end
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && X > 666 && X < 942 && Y > 360 && Y < 482)		return 4;	// setting
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && X > 438 && X < 540 && Y > 377 && Y < 562)		return 3;	// highscore
			}
		
			window.display();
			window.clear();
		}
		
	}


};



