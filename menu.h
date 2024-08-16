#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

class inheritMenu {

protected:
	Color color;
	Music& music;
	static float delay;

	int AbsoluteLength;
	int current;

	int charSize;
	Clock timer;

	bool Switch;
	Text* Options;

	Font font;

public:

	inheritMenu(Color aColor, Music& aMusic, int aAbsoluteLength, int aCurrent, int aCharSize, bool aSwitch)
		:music(aMusic)
	{
		font.loadFromFile("Fonts/Grenze-Black.ttf");

		color = aColor;
		AbsoluteLength = aAbsoluteLength;
		current = aCurrent;
		charSize = aCharSize;
		Switch = aSwitch;
	}

	int getCurrent() { return current; }
	void setCurrent(int c) { current = c; }

	bool getSwitch() { return Switch; }
	void setSwitch(bool s) { Switch = s; }
	
	void draw(RenderWindow& window)
	{
		for (int i = 0; i < AbsoluteLength; i++)
			window.draw(Options[i]);

		window.display();
		window.clear();
	}

	bool closeWindow(sf::Event& e, sf::RenderWindow& window)
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
			Switch = 0;
			return 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			Switch = 0;
			return 1;
		}
		return 0;
	}


};

float inheritMenu::delay = 0.17;
