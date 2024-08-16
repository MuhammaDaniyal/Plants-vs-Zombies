#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Zombies {
public:
	int health, zomPosX, zomPosY, SpriteCount, EatanimationCount, animationCount, speed, EatSpriteCount;
	bool zombieExist, Plantdetected;
	char type;
	Clock clock;
	Texture ZombTexture;
	Sprite *zomAnimation, *zomEatAnimation;

	Zombies() {
		health = 150;
		zomPosX = 1150;
		zomPosY = (rand() % 5) * 97 + 65;
		zombieExist = Plantdetected = 0;
		EatanimationCount=animationCount = SpriteCount = speed = 0;
		type = ' ';
		zomAnimation = NULL;
	}
	void display(RenderWindow& window, int &l) {
		if (clock.getElapsedTime().asSeconds() < 0.1)
		{
			window.draw(zomAnimation[animationCount]);
			return;
		}
		clock.restart();
		if (animationCount < SpriteCount-1)
			animationCount++;
		else
			animationCount = 0;
		zomAnimation[animationCount].setPosition(zomPosX, zomPosY);
		window.draw(zomAnimation[animationCount]);
		zomPosX -= speed;
		if (zomPosX < 200)
		{
			zomPosX = 1000;
			zomPosY = rand() % 5 * 97 + 65;
			zombieExist = 0;
			l--;
		}
	}

	void Eatdisplay(RenderWindow& window) {

		zomEatAnimation[EatanimationCount].setPosition(zomPosX, zomPosY);
		if (clock.getElapsedTime().asSeconds() < 0.1)
		{
			window.draw(zomEatAnimation[EatanimationCount]);
			return;
		}
		clock.restart();
		if (EatanimationCount < EatSpriteCount - 1)
			EatanimationCount++;
		else
			EatanimationCount = 0;
		zomEatAnimation[EatanimationCount].setPosition(zomPosX, zomPosY);
		window.draw(zomEatAnimation[EatanimationCount]);
		
	}

	bool ZombieWaves(int i, Clock& WaveClock, double waveCheck[]) {
		if (*(waveCheck+i) != 0.0 && WaveClock.getElapsedTime().asSeconds() >= *(waveCheck+i)) {
			zombieExist = 1;
			*(waveCheck+i) = 0.0;
			return 1;
			WaveClock.restart();
		}
		return 0;
	}
};

class SimpleZombies : public Zombies {
public:
	SimpleZombies() {
		ZombTexture.loadFromFile("Sprites_update/Zombies/Zombie3.png");
		SpriteCount = 7;
		EatSpriteCount = 7;
		speed = 3;
		health = 200;
		type = 'S';
		zomAnimation = new Sprite[SpriteCount];
		zomEatAnimation = new Sprite[EatSpriteCount];
		int left = 0;
		for (int i = 0; i < SpriteCount; ++i)
		{
			zomAnimation[i].setTexture(ZombTexture);
			zomAnimation[i].setTextureRect(IntRect(left, 55, 50, 65));
			left += 50;
			zomAnimation[i].setScale(2, 2);
			
		}
		left = 0;
		for (int i = 0; i < EatSpriteCount; ++i)
		{
			zomEatAnimation[i].setTexture(ZombTexture);
			zomEatAnimation[i].setTextureRect(IntRect(left, 217, 45, 65));
			left += 45;
			zomEatAnimation[i].setScale(2, 2);
		}
	}
	~SimpleZombies() {
		delete[]zomAnimation;
		delete[]zomEatAnimation;
	}
};

class Football : public Zombies {
public:
	Football() {
		ZombTexture.loadFromFile("Sprites_update/Zombies/foot.png");
		SpriteCount = 8;
		EatSpriteCount = 6;
		speed = 9;
		type = 'F';
		health = 250;
		zomAnimation = new Sprite[SpriteCount];
		zomEatAnimation = new Sprite[EatSpriteCount];
		int left = 0;
		for (int i = 0; i < SpriteCount; ++i)
		{
			zomAnimation[i].setTexture(ZombTexture);
			zomAnimation[i].setTextureRect(IntRect(left, 77, 64, 72));
			left += 64;
			zomAnimation[i].setScale(2, 2);
		}
		left = 0;
		for (int i = 0; i < EatSpriteCount; ++i)
		{
			zomEatAnimation[i].setTexture(ZombTexture);
			zomEatAnimation[i].setTextureRect(IntRect(left, 485, 65, 72));
			left += 65;
			zomEatAnimation[i].setScale(2, 2);
		}
	}
	~Football() {
		delete[]zomAnimation;
		delete[]zomEatAnimation;
	}
};

class Dance : public Zombies {
public:
	Dance() {
		ZombTexture.loadFromFile("Sprites_update/Zombies/Zombie1.png");
		SpriteCount = 4;
		EatSpriteCount = 6;
		speed = 3;
		health = 300;
		type = 'D';
		zomAnimation = new Sprite[SpriteCount];
		zomEatAnimation = new Sprite[EatSpriteCount];
		int left = 0;
		for (int i = 0; i < SpriteCount; ++i)
		{
			zomAnimation[i].setTexture(ZombTexture);
			zomAnimation[i].setTextureRect(IntRect(left, 0, 50, 75));
			left += 52;
			zomAnimation[i].setScale(1.5, 1.5);
		}
		left = 0;
		for (int i = 0; i < EatSpriteCount; ++i)
		{
			zomEatAnimation[i].setTexture(ZombTexture);
			zomEatAnimation[i].setTextureRect(IntRect(left, 243, 57, 79));
			left += 57;
			zomEatAnimation[i].setScale(1.5, 1.5);
		}
	}
	~Dance() {
		delete[]zomAnimation;
		delete[]zomEatAnimation;
	}
};

class ZombieFactory {
public:
	Zombies* zombie[20];
	virtual void factory(int level) = 0;
};

class DanielsFactory :public ZombieFactory {
public:
	void factory(int level) {
		if (level == 1)
		{
			for (int i = 0; i < 15; i++)
				zombie[i] = new SimpleZombies();
		}
		else if (level == 2) {
			for (int i = 0; i < 15; i++)
			{
				int x = rand() % 2 + 1;
				if (x == 1)
					zombie[i] = new SimpleZombies();
				else
					zombie[i] = new Football();
			}
		}
		else if (level == 3) {
			for (int i = 0; i < 15; i++)
			{
				int x = rand() % 3 + 1;
				if (x == 1)
					zombie[i] = new SimpleZombies();
				else if (x == 3)
					zombie[i] = new Football();
				else
					zombie[i] = new Dance();
			}
		}
	}
};