#pragma once
#include<SFML/Audio.hpp>
#include "Level.h" 
#include "settings.h" 

using namespace sf;
class Level1 :public Levels {

protected:
	Texture selectTextureFlower;
	Sprite selectionFlower;
	Image map_image;
	Image npc;
	Texture n;
	Sprite s;
	bool normalS, flowerS,
		unselectableNormal, unselectableFlower,
		releasedNormal, releasedFlower;
	int deathCounts, lives;
	Clock selector[2];
	//sun Sun;


public:
	Level1() :Levels()
	{
		lives = 5;
		normalS = 0;					flowerS = 0;
		unselectableNormal = 0;			unselectableFlower = 0;
		releasedNormal = 0;				releasedFlower = 0;
		deathCounts = 0;

		sunBoardTexture.loadFromFile("Sprites_update/bg/plank.png");
		sunBoardSprite.setTexture(sunBoardTexture);
		sunBoardSprite.setTextureRect(IntRect(0, 0, 419, 200));
		sunBoardSprite.setPosition(20, 10);
		sunBoardSprite.setScale(0.3, 0.3);


		selectTextureFlower.loadFromFile("Sprites_update/Plants/selectFlower.png");
		selectionFlower.setTexture(selectTextureFlower);
		selectionFlower.setTextureRect(IntRect(0, 0, 26, 26));
		selectionFlower.setPosition(posX, posY + gap);
		selectionFlower.setScale(3, 2.5);

		zom = new DanielsFactory();
		zom->factory(1);
		for (int i = 0; i < 15; i++) {
			if (i <= 2)
				waveCheck[i] = rand() % 60 + 30;   //First Wave
			else if (i <= 6)
				waveCheck[i] = rand() % 100 + 70;  //Second Wave
			else
				waveCheck[i] = rand() % 150 + 100;  //Third Wave
		}
		npc.loadFromFile("Sprites_update/bg/npc.png");
		n.loadFromImage(npc);
		s.setTexture(n);
		s.setScale(0.2, 0.2);
		mapTexture.loadFromFile("Sprites_update/bg/level1.png");
		s_map.setTexture(mapTexture);
		s_map.setPosition(0, 0);
	}

	virtual int gameloop(RenderWindow& window, int& score)
	{

		Music menuMusic;
		menuMusic.openFromFile("music/menubutton.wav");
		settingMenu setting(menuMusic, 50, 50);



		sf::Color color;
		sf::Music bg;
		bg.openFromFile("music/background/bg5.wav");
		bg.play();
		
		while (window.isOpen())
		{
			if (deathCounts >= 14 || Keyboard::isKeyPressed(Keyboard::A))  // Next Level
				return 5;
			if (lives <= 0)         // Lose
				return 0;
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					for (int i = 0; i < 45; ++i)
						if (arr[i] != nullptr)
						{
							delete arr[i];
							arr[i] = nullptr;
						}
					window.close();
					return -1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					setting.loop(window, menuMusic);
				}
			}
			window.draw(s_map);

			int X = Mouse::getPosition(window).x,
				Y = Mouse::getPosition(window).y,
				coll = int((X - 253) / 80),
				roww = int((Y - 83) / 97);
			// This codition is just so that i can squeeze whole if making code better

			if (sunNo >= 0)
			{
				if (sunNo < 50)
				{
					color = selectionFlower.getColor();					// Gets the color of sprite for opacity
					color.a = 128;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionFlower.setColor(color);					// Set that opacity color
				}
				else if (sunNo >= 50 && !unselectableFlower)
				{
					color = selectionFlower.getColor();					// Gets the color of sprite for opacity
					color.a = 255;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionFlower.setColor(color);					// Set that opacity color
				}
				if (sunNo < 100)
				{
					color = selectionNormal.getColor();					// Gets the color of sprite for opacity
					color.a = 128;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionNormal.setColor(color);					// Set that opacity color
				}
				else if (sunNo >= 50 && !unselectableNormal)
				{
					color = selectionNormal.getColor();					// Gets the color of sprite for opacity
					color.a = 255;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionNormal.setColor(color);					// Set that opacity color
				}
			}

			// This deals with the selection of the plants
			if (Mouse::isButtonPressed(Mouse::Left) && selectClk.getElapsedTime().asMilliseconds() > 1000)
			{
				selectClk.restart();
				//if (sunNo > 100 && !unselectableNormal && !flowerS && X > posX && X<posX + 67 && Y>posY && Y < posY + 51)
				if (!unselectableNormal && !flowerS && X > posX && X<posX + 67 && Y>posY && Y < posY + 51)
				{
					unselectableNormal = 1;								// Normal pea cannot be selected now
					color = selectionNormal.getColor();					// Gets the color of sprite for opacity
					color.a = 128;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionNormal.setColor(color);					// Set that opacity color
					normalS = 1;										// normal is selected
				}
				//else if (sunNo > 50 && !unselectableFlower && !normalS && X > posX && X<posX + 67 && Y>posY + gap && Y < posY + gap + 54)
				else if (!unselectableFlower && !normalS && X > posX && X<posX + 67 && Y>posY + gap && Y < posY + gap + 54)
				{
					unselectableFlower = 1;
					color = selectionFlower.getColor();
					color.a = 128;
					selectionFlower.setColor(color);
					flowerS = 1;
				}
			}

			// This resets / allows the selection after the restricted timer ends
			if (releasedNormal && unselectableNormal && selector[0].getElapsedTime().asSeconds() > 5)
			{
				color = selectionNormal.getColor();					// Gets the color of sprite for opacity
				color.a = 255;										// set Opacity to 0
				selectionNormal.setColor(color);					// Set that opacity color
				releasedNormal = 0;									// Normal is released
				unselectableNormal = 0;								// Now we can select normal Pea
			}
			else if (releasedFlower && unselectableFlower && selector[1].getElapsedTime().asSeconds() > 5)
			{
				color = selectionNormal.getColor();					// Gets the color of sprite for opacity
				color.a = 255;										// set Opacity to 0
				selectionFlower.setColor(color);					// Set that opacity color
				releasedFlower = 0;									// Normal is released
				unselectableFlower = 0;								// Now we can select normal Pea
			}


			// This sets the plants on the grid
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clk.getElapsedTime().asMilliseconds() > 1000 && X > 253 && X < 990 && Y > 73 && Y < 576)
			{
				clk.restart();

				if (FIELD_GAME_STATUS[roww][coll] == ' ')
				{
					if (normalS)
					{
						selector[0].restart();									// clk selector of normal pea is restarted
						releasedNormal = 1;										// Normal pea is released
						FIELD_GAME_STATUS[roww][coll] = 'N';					// Added N at the grid
						arr[roww * COLS + coll] = new normalPea(253 + 80 * coll, 83 + 97 * roww);	//Made a pea dynamically
						arr[roww * COLS + coll]->setExist(1);					// Exist sets the bullet bool to 1
						arr[roww * COLS + coll]->setposX(253 + 80 * coll + 50);	//Both posiitons are for bullet
						arr[roww * COLS + coll]->setposY(83 + 97 * roww);		// THis one too	
						normalS = 0;											// normal select is now again 0
						sunNo -= 100;
					}
					else if (flowerS)
					{
						selector[1].restart();
						releasedFlower = 1;
						FIELD_GAME_STATUS[roww][coll] = 'F';
						arr[roww * COLS + coll] = new sunFlower(253 + 80 * coll, 83 + 97 * roww);
						flowerS = 0;
						sunNo -= 50;
					}
				}
			}

			// Shooting and drawing mechanism
			for (int row = 0; row < 5; ++row)
			{
				for (int column = 0; column < 9; ++column)
				{
					if (FIELD_GAME_STATUS[row][column] != ' ')
					{
						if (arr[row * COLS + column] != nullptr)
						{
							arr[row * COLS + column]->draw(window, FIELD_GAME_STATUS);
							if (FIELD_GAME_STATUS[row][column] == 'N' && arr[row * COLS + column]->getExist())
								arr[row * COLS + column]->shoot(window);
							else if (FIELD_GAME_STATUS[row][column] == 'F')
							{
								if (arr[row * COLS + column]->sunWorking(window))
									sunNo += 25;
							}
						}
					}
				}
			}

			textSun.setString("Suns: " + to_string(sunNo));
			scor.setString("SCORE: " + to_string(score));
			lev.setString("KILL 14 ZoMbIeS!!!!");

			window.draw(selectionNormal);					// Print selections icon
			window.draw(selectionFlower);					// Print selections icon
			window.draw(sunBoardSprite);					// Print sun number board
			window.draw(textSun);	                        // Print the text sun number
			window.draw(lev);

			for (int i = 0; i < 5; ++i)
				window.draw(lawnMowerSprite[i]);

			if (Keyboard::isKeyPressed(Keyboard::G))
				Levels::printGrid(FIELD_GAME_STATUS, ROWS, COLS);		// For printing grid

			drawZombie(window);
			CollisionCheck(ROWS, COLS);
			BulletCollision(score);

			rect.checkPos(window);						// grid rectangle position

			// Extra zombies for aesthetics
			int row1 = 30, col1 = 990;
			for (int i = 0; i < 5; i++) {
				s.setPosition(col1, row1);
				row1 += 120;
				if (col1 == 1040)
				{
					col1 = 1090;
				}
				else
				{
					col1 = 1040;
				}
				window.draw(s);
			}
			window.draw(scor);

			if (Sun.sunWorking(window))					// This does the All working of sun and
				sunNo += 25;							// return 1 if the sun is hovered and sunNo is incremented 

			window.display();
			window.clear();

		}



	}

	void drawZombie(RenderWindow& window) {
		for (int i = 0; i < 15; i++) {
			zom->zombie[i]->ZombieWaves(i, WaveClock, waveCheck);  //Handles Zombie Existence according to Wave Tine

			if (zom->zombie[i]->zombieExist && zom->zombie[i]->Plantdetected)
				zom->zombie[i]->Eatdisplay(window);
			else if (zom->zombie[i]->zombieExist)
				zom->zombie[i]->display(window, lives);
		}
	}
	void CollisionCheck(const int r, const int c) {  //Zombie and Plant
		for (int i = 0; i < 15; i++) {
			if (zom->zombie[i]->zombieExist) {
				int x = (zom->zombie[i]->zomPosX - 315) / 80;
				int y = (zom->zombie[i]->zomPosY) / 97;
				for (int l = 0; l < 5; l++) {
					for (int j = 0; j < 9; j++) {
						if ((FIELD_GAME_STATUS[l][j] == 'N' || FIELD_GAME_STATUS[l][j] == 'F') && l == y && j == x + 1) {
							if (arr[l * 9 + j]->getHealth() <= 0) {
								zom->zombie[i]->Plantdetected = 0;
								FIELD_GAME_STATUS[l][j] = ' ';
								delete arr[l * 9 + j];
								arr[l * 9 + j] = nullptr;
							}
							else if (FIELD_GAME_STATUS[l][j] == 'N' || FIELD_GAME_STATUS[l][j] == 'F' && arr[l * 9 + j]->getHealth() > 0) {
								arr[l * 9 + j]->setHealth(arr[l * 9 + j]->getHealth() - 1);
							}
							zom->zombie[i]->Plantdetected = 1;
						}

						else if (FIELD_GAME_STATUS[l][j] == ' ' && l == y && j == x + 1) {
							zom->zombie[i]->Plantdetected = 0;
						}

						else if ((FIELD_GAME_STATUS[l][j] == 'N' || FIELD_GAME_STATUS[l][j] == 'F') && l == y && j == x + 1)
							zom->zombie[i]->Plantdetected = 1;

					}
				}
			}
		}
	}

	void BulletCollision(int & score) {  //Bullet AAnd Zombie

		for (int j = 0; j < 5; j++) {
			for (int l = 0; l < 9; l++) {
				for (int i = 0; i < 15; i++) {
					if (arr[j * 9 + l] != NULL) {
						if (zom->zombie[i]->zombieExist && (arr[j * 9 + l]->getposX() - 253) / 80 - 1 == (zom->zombie[i]->zomPosX - 253) / 80 && (arr[j * 9 + l]->getposY() - 83) / 97 == (zom->zombie[i]->zomPosY) / 97 && (zom->zombie[i]->zomPosX - 253) / 80 != (arr[j * 9 + l]->getOldposX() - 253) / 80 - 1) {
							cout << (arr[j * 9 + l]->getposY() - 83) / 97 - 1 << "   " << (zom->zombie[i]->zomPosY) / 97 << endl;
							zom->zombie[i]->health -= 20;
							arr[j * 9 + l]->setExist(0);
							arr[j * 9 + l]->setposX(arr[j * 9 + l]->getOldposX());
							arr[j * 9 + l]->setposY(arr[j * 9 + l]->getOldposY());
							if (zom->zombie[i]->health <= 0) {
								zom->zombie[i]->zombieExist = 0;
								deathCounts++;
								score += 20;
								zom->zombie[i]->health = 100;
								zom->zombie[i]->zomPosX = 1150;
								zom->zombie[i]->zomPosY = (rand() % 5) * 97 + 65;
							}
						}
						if (zom->zombie[i]->zombieExist && (arr[j * 9 + l]->getposY() - 83) / 97 == (zom->zombie[i]->zomPosY) / 97)
							arr[j * 9 + l]->setExist(1);
					}
				}
			}
		}
	}

	~Level1() {
		for (int i = 0; i < 15; i++) {
			delete zom->zombie[i];
		}
		delete zom;
	}
};