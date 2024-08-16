#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class sun {
	int posX, posY, presentY;
	Texture textSun;

	Clock spawnClk,
		moveClk,
		disappearClk;

	bool exist;

public:
	Sprite sunSprite;

	sun() :posX(-100), posY(-100)
	{
		exist = 1;
		presentY = 0;
		textSun.loadFromFile("Sprites_update/Plants/sun.png");
		sunSprite.setTexture(textSun);
		sunSprite.setTextureRect(IntRect(0, 0, 225, 225));
		sunSprite.setScale(0.4, 0.4);
		sunSprite.setPosition(posX, posY);
	}

	void produceSun()
	{
		// Spawning time check
		if (spawnClk.getElapsedTime().asSeconds() > 7)
		{
			spawnClk.restart();					// Clock restart
			exist = 1;							// Exists 1
			presentY = 0;						// start/present position is 0
			posX = rand() % 750 + 200;			// X random position
			posY = rand() % 500 + 83;			// Y random position
			sunSprite.setPosition(posX, 0);		// Set the sprite
		}
	}

	bool moveSun()
	{
		//move till the sun doesnot reach its end position
		if (presentY <= posY && moveClk.getElapsedTime().asMilliseconds() > 100)
		{
			disappearClk.restart();					// It always restart as we dont want to start the disappear timer here
			moveClk.restart();						// restarts move clk	
			presentY += 7;							// increment Y position
			sunSprite.setPosition(posX, presentY);	// set position
			return 0;								// If it is moving it will return 0
		}
		return 1;									//Else it will return 1
	}

	bool clickSun(RenderWindow& window)
	{
		int X = Mouse::getPosition(window).x,
			Y = Mouse::getPosition(window).y;

		// If the mouse is in the territory of the sun
		if (X >= sunSprite.getPosition().x && X <= sunSprite.getPosition().x + sunSprite.getGlobalBounds().width &&
			Y >= sunSprite.getPosition().y && Y <= sunSprite.getPosition().y + sunSprite.getGlobalBounds().height)
		{
			//exists will be 0 and posotion will be resetted
			exist = 0;
			sunSprite.setPosition(-200, -200);
			return 1;
		}
		return 0;
	}

	void disappearSun()
	{
		// If it exists and dissapear clk ends
		if (exist && disappearClk.getElapsedTime().asSeconds() > 5)
		{
			//exists will be 0 and posotion will be resetted
			exist = 0;
			sunSprite.setPosition(-200, -200);
		}
	}

	bool sunWorking(RenderWindow& window)
	{
		bool Return = 0;

		produceSun();

		window.draw(sunSprite);						// drawing sprites
		if (exist)
		{
			if (moveSun())							// If the sun is moving than 
				disappearSun();						// disappear wont activate
			Return = clickSun(window);						// Click feature, In reality it is hover effect
		}
		return Return;

	}
};

class bullet {

protected:
	Texture bulletText;
	int speed;

public:
	Sprite bulletSprite;
	Clock clk;
	int posX, posY, oldPosX, oldPosY;
	bool exist;

	bullet(int x = -10, int y = -10) :posX(x), posY(y)
	{
		oldPosX = x;
		oldPosY = y;
		bulletText.loadFromFile("Sprites_update/Plants/bulletNormal.png");
		bulletSprite.setTexture(bulletText);
		bulletSprite.setTextureRect(IntRect(0, 0, 12, 16));
		bulletSprite.setScale(2, 2);
		speed = 2;
		exist = 0;
	}

	int getposX() { return posX; }
	int getposY() { return posY; }

	int getOldposX() { return oldPosX; }
	int getOldposY() { return oldPosY; }

	void setposX(int x) { posX = x; }
	void setposY(int y) { posY = y; }

	bool getExist() { return exist; }
	void setExist(bool e) { exist = e; }

	void drawBullet(RenderWindow& window)
	{
		if (clk.getElapsedTime().asMilliseconds() > 10)
		{
			clk.restart();
			posX += speed;
			bulletSprite.setPosition(posX, posY);
		}
		window.draw(bulletSprite);
	}


};

class plant {

protected:
	Texture peatext;
	int size;
	int count;
	Clock clock;
	int health, lane,
		posX, posY;
	//clASS composed in levels
public:
	Sprite* Arr;

	virtual int getHealth() {
		return health;
	}
	virtual void setHealth(int i) {
		health=i;
	}

	plant(int aSize, int startX, int aPosX, int aPosY, int width, int height, int gap)
	{
		health = 1000;
		count = 0;
		size = aSize;
		Arr = new Sprite[size];

		for (int i = 0; i < size; ++i)
		{
			posX = aPosX;
			posY = aPosY;
			lane = -1;
			Arr[i].setTexture(peatext);
			//                                       width, height
			Arr[i].setTextureRect(IntRect(startX - 3, 0, width, height));
			startX += gap;
			Arr[i].setScale(2, 2);
			Arr[i].setPosition(aPosX, aPosY);
		}

	}

	virtual ~plant()
	{
		delete[]Arr;
		Arr = NULL;
	}

	virtual void draw(RenderWindow& window, char Field[][9]) = 0;


	virtual void shoot(RenderWindow& window) {};
	virtual bool sunWorking(RenderWindow& window) { return 1; }		//for sunFlower

	void drawMain(RenderWindow& window, char Field[][9])
	{

		if (clock.getElapsedTime().asMilliseconds() < 200)
		{
			window.draw(Arr[count]);
			return;
		}

		clock.restart();
		if (count < size - 1)			count++;
		else							count = 0;

		window.draw(Arr[count]);
	}

	virtual void setExist(bool e) {}
	virtual bool getExist() { return 0; }

	virtual int getposX() { return posX; }
	virtual int getposY() { return posY; }

	virtual void setposX(int x) { posX = x; }
	virtual void setposY(int y) { posY = y; }

	virtual int getOldposX() { return 1; }
	virtual int getOldposY() { return 1; }


};


class normalPea : public plant {

public:

	bullet bull;
	int Health;

	int getHealth() {
		return Health;
	}
	void setHealth(int i) {
		Health = i;
	}

	normalPea(int posX = -10, int posY = -10) :plant(8, 2, posX, posY, 28, 30, 27)
	{
		Health = 1500;
		peatext.loadFromFile("Sprites_update/Plants/Pea_normal.png");
		bull.oldPosX = posX + 20;
		bull.oldPosY = posY;
		bull.setExist(0);
	}

	virtual void draw(RenderWindow& window, char Field[][9])
	{
		plant::drawMain(window, Field);
	}
	virtual bool getExist() { return bull.exist; }

	virtual int getposX() { return bull.posX; }
	virtual int getposY() { return bull.posY; }

	virtual int getOldposX() { return bull.oldPosX; }
	virtual int getOldposY() { return bull.oldPosY; }

	virtual void setExist(bool e) { bull.exist = e; }
	virtual void setposX(int x) { bull.posX = x; }
	virtual void setposY(int y) { bull.posY = y; }

	virtual void shoot(RenderWindow& window)
	{
		if (bull.posX >= 950)
		{
			//bull.exist = 0;
			bull.setposX(bull.getOldposX());
			bull.setposY(bull.getOldposY());
		}

		if (bull.exist == 1)
			bull.drawBullet(window);
	}

};



class stationary :public plant {

protected:


public:

	stationary(int aSize, int startX, int posX, int posY, int width, int height, int gap)
		:plant(aSize, startX, posX, posY, width, height, gap) {}

	//virtual void draw(RenderWindow& window, char Field[][9]) {}

};

class sunFlower : public stationary {

	Clock spawnClk, disappearClk;
	int delay, posX, posY;
	Texture textSun;
	Sprite sunSprite;
	bool exist;

public:
	int Health;
	int getHealth() {
		return Health;
	}
	void setHealth(int i) {
		Health = i;
	}
	sunFlower(int aPosX = -10, int aPosY = -10) :stationary(5, 4, aPosX, aPosY, 31, 31, 30)
	{
		Health = 1000;
		posX = aPosX;			posY = aPosY;
		delay = 5;				exist = 0;
		peatext.loadFromFile("Sprites_update/Plants/flower1.png");
		textSun.loadFromFile("Sprites_update/Plants/sun.png");
		sunSprite.setTexture(textSun);
		sunSprite.setTextureRect(IntRect(0, 0, 225, 225));
		sunSprite.setScale(0.4, 0.4);

	}

	void produceSun()
	{
		// Spawning time check
		if (spawnClk.getElapsedTime().asSeconds() > delay)
		{
			disappearClk.restart();
			spawnClk.restart();						// Clock restart
			exist = 1;
			sunSprite.setPosition(posX, posY - 20);		// Set the sprite same of flower
		}
	}

	bool clickSun(RenderWindow& window)
	{
		int X = Mouse::getPosition(window).x,
			Y = Mouse::getPosition(window).y;

		// If the mouse is in the territory of the sun
		if (X >= sunSprite.getPosition().x && X <= sunSprite.getPosition().x + sunSprite.getGlobalBounds().width &&
			Y >= sunSprite.getPosition().y && Y <= sunSprite.getPosition().y + sunSprite.getGlobalBounds().height)
		{
			//exists will be 0 and position will be reset
			exist = 0;
			sunSprite.setPosition(-200, -200);
			return 1;
		}
		return 0;
	}

	void disappearSun()
	{
		// If it exists and dissapear clk ends
		if (exist && disappearClk.getElapsedTime().asSeconds() > 2)
		{
			disappearClk.restart();
			//exists will be 0 and posotion will be resetted
			exist = 0;
			sunSprite.setPosition(-200, -200);
		}
	}

	virtual bool sunWorking(RenderWindow& window)
	{
		produceSun();
		bool Return = 0;
		if (exist)
		{
			disappearSun();						// disappear wont activate
			Return = clickSun(window);			// Click feature, In reality it is hover effect
		}
		window.draw(sunSprite);					// drawing sprites
		return Return;
	}

	virtual void draw(RenderWindow& window, char Field[][9])
	{
		plant::drawMain(window, Field);
		//sunWorking(window);
	}

};


class wallNut : public stationary {

protected:

public:
	int Health;
	int getHealth() {
		return Health;
	}
	void setHealth(int i) {
		Health = i;
	}
	wallNut(int posX = -10, int posY = -10) :stationary(5, 3, posX, posY, 27, 31, 27.2)
	{
		Health = 10000;
		peatext.loadFromFile("Sprites_update/Plants/wallnut.png");
	}

	virtual void draw(RenderWindow& window, char Field[][9])
	{
		plant::drawMain(window, Field);
	}

};

class cherryBomb : public stationary {

protected:

public:
	bool exist;
	int count;
	cherryBomb(int aposX, int aposY) :stationary(13, 3, aposX, aposY, 27, 31, 27.2)
	{
		//peatext.loadFromFile("Sprites_update/Plants/cherry.png");
		peatext.loadFromFile("Sprites_update/Plants/Cherry1.png");

		int startX = 0, startY = 0,
			width = 34, height = 38,
			gap = 8, inc = 5;
		exist = 1;
		count = 0;

		for (int i = 0; i < size; ++i)
		{
			Arr[i].setTexture(peatext);
			//                                           width, height
			Arr[i].setTextureRect(IntRect(startX, startY, width, height));

			if (i == 0) { startX += 34; width += 2; }			//start 36, width 36
			else if (i == 1) { startX += 36; width += 10; }
			else if (i == 2) { startX += 46; }
			else if (i == 3) { startX += 46; width += 5; }
			else if (i == 4) { startX += 51; }
			else if (i == 5) { startX = 0;   startY = 38; height = 67; width = 68; }
			else if (i == 6) { startX += 68; width = 82; }
			else if (i == 7) { startX += 82; width = 96; }
			else if (i == 8) { startX += 96; width = 93; }
			else if (i == 9) { startX += 93; }
			else if (i == 10) { startX += 93; width = 92; }
			else if (i == 11) { startX += 92; width = 91; }
			else if (i == 12) { startX += 91; width = 88; }

			if (i > 5)		Arr[i].setScale(1.2, 1.2);
			else			Arr[i].setScale(2, 2);

			Arr[i].setPosition(posX, posY);
		}



	}

	virtual void draw(RenderWindow& window, char Field[][9])
	{
		if (exist) {
			plant::drawMain(window, Field);
			count++;
			if (count >= 1000)
			{
				exist = 0;
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 9; j++) {
						if (*(*(Field + i) + j) == 'C')
							*(*(Field +i) + j) = ' ';
					}
				}
			}
		}
	}



};