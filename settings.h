#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.h"
#include <string>

using namespace sf;
using namespace std;
const int X = 220, Y = 250;

class settingMenu : public inheritMenu
{
	int length;	

	Clock timer2;	
	Color darkBlue;

	int volumeSoundEffect;
	int volumeMusic;

	int slider1;
	int slider2;

	Texture backText;
	Sprite backGround;

	Texture sliderLineTexture;
	Sprite sliderLineSprite;
	Sprite sliderLineSprite2;

public:


	//Volume menu
	settingMenu(Music& menuMusic, int Vol, int size):
		inheritMenu(Color::Red, menuMusic, 11, 0, size, 1),
		slider1(750), slider2(750), volumeMusic(50), volumeSoundEffect(47)
	{

		sliderLineTexture.loadFromFile("images/slice.jpg");

		sliderLineSprite.setTexture(sliderLineTexture);
		sliderLineSprite2.setTexture(sliderLineTexture);

		sliderLineSprite.setTextureRect(IntRect(298, 87, 5, 19));
		sliderLineSprite2.setTextureRect(IntRect(298, 87, 5, 19));
		
		sliderLineSprite.setPosition(750, 195);
		sliderLineSprite2.setPosition(750, 247);


		backText.loadFromFile("images/setting.png");
		backGround.setTexture(backText);
		backGround.setTextureRect(IntRect(0, 0, 254, 189));
		backGround.setScale(3, 3);
		backGround.setPosition(300, 40);


		darkBlue = sf::Color(0, 0, 139);
		length = 2;

	}


	void Shift(Event& e)
	{
		if (timer2.getElapsedTime().asSeconds() < delay)	return;
		timer2.restart();

		if (e.type == sf::Event::KeyPressed && (Keyboard::isKeyPressed(Keyboard::Up)))
		{
			if (current == 0)		current = 1;
			else                    current = 0;
			music.stop();          music.play();
			cout << current << endl;
		
			/*
			for (int i = 0; i < length; ++i)
				if (current == i)
				{
					Options[current].setFillColor(Color::White);
					current == 0 ? current = length - 1 : current = i - 1;
					Options[current].setFillColor(color);
					break;
				}
			*/
		}
		else if (e.type == sf::Event::KeyPressed && (Keyboard::isKeyPressed(Keyboard::Down)))
		{
			if (current == 0)		current = 1;
			else                    current = 0;
			music.stop();          music.play();
			cout << current << endl;

			/*
			for (int i = 0; i < length; ++i)
				if (current == i)
				{
					music.stop();          music.play();
					Options[current].setFillColor(Color::White);
					current == length - 1 ? current = 0 : current = i + 1;
					Options[current].setFillColor(color);
					break;
				}
			*/
		}
	}

	void Slider(Event& e, Music& bgMusic , Sprite& sliderIn1, Sprite& sliderIn2)
	{
		if (timer.getElapsedTime().asSeconds() < delay)	return ;
			timer.restart();

		if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)))
		{
			//This area will just toggle the ON and OFF
/*
			if (current == 0)
			{
				if (Options[current].getString() == "ON"){	Options[current].setString("OFF"); 		bgMusic.setVolume(0); 			}
				else {										Options[current].setString("ON"); 		bgMusic.setVolume(volumeMusic); }
			}
			else if (current == 2)
			{
				if (Options[current].getString() == "ON") { Options[current].setString("OFF");		music.setVolume(0); }
				else { Options[current].setString("ON");			music.setVolume(volumeSoundEffect); }
			}
*/
			
			int YUp = 195, Yd = 247;

			//It will slide the slider as pressed
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (current == 0)
				{
					if (volumeMusic > 0)
						sliding(0, volumeMusic, sliderIn1, slider1, YUp, bgMusic);
				}
				else if (current == 1)
				{
					if (volumeSoundEffect > 0)
						sliding(0, volumeSoundEffect, sliderIn2, slider2, Yd, music);
				}
			}

			else if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (current == 0)
				{
					if (volumeMusic < 100)
						sliding(1, volumeMusic, sliderIn1, slider1, YUp, bgMusic);	
				}
				else if (current == 1)
				{
					if (volumeSoundEffect < 100)
						sliding(1, volumeSoundEffect, sliderIn2, slider2, Yd, music);	
				}
			}
		}
	}

	void sliding( int sign, int& vol , Sprite& sprite , int& PosX , int PosY , Music& music)
	{

		if (sign == 1)
		{
			vol++;			music.setVolume(vol);
			PosX += 2;		sprite.setPosition(PosX, PosY);
		}
		else if (sign == 0)
		{
			vol--;			music.setVolume(vol);
			PosX -= 2;		sprite.setPosition(PosX, PosY);
		}
	}
	
	int loop(RenderWindow& window , Music& bgMusic)
	{
		bool Switch = 0;
		while (window.isOpen())
		{
			window.draw(backGround);
	
			sf::Event M1;
			while (window.pollEvent(M1))
				closeWindow(M1, window);
	
			Slider(M1, bgMusic, sliderLineSprite, sliderLineSprite2);
			
			if (Switch)	return 0;

			Shift(M1);
	
			int X = Mouse::getPosition(window).x,
				Y = Mouse::getPosition(window).y;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && X > 474 && X < 877 && Y > 497 && Y < 573)		return 0;


			window.draw(sliderLineSprite);
			window.draw(sliderLineSprite2);
			window.display();
			window.clear(darkBlue);
		}
	
	}

	


};



