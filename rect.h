#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class gridRect {

	sf::RectangleShape rect;
	sf::Color color;
	int height;
	int width;

public:

	gridRect()
	{
		width = 90 - 8;
		height = 125 - 28;
		color = sf::Color(192, 192, 192, 127);
		rect.setSize(sf::Vector2f(width, height));
		rect.setFillColor(color);
	}

	void checkPos(RenderWindow& window)
	{
		int X = Mouse::getPosition(window).x,
			Y = Mouse::getPosition(window).y;

		rect.setPosition(253 + 80 * ((X - 253) / 80), 83 + 97 * ((Y - 83) / 97));
		if (X > 253 && X < 990 && Y > 73 && Y < 576)
			window.draw(rect);

		//std::cout << (X - 253)/80 << "\t" << (Y - 83)/97
		//	<< std::endl;

		//rect.setPosition( X, Y);
		//rect.setPosition((Mouse::getPosition(window).x - 290)/90 , (Mouse::getPosition(window).y - 380)/125);

	}



};