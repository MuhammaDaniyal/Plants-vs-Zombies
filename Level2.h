#pragma once
#pragma once

#include "Level.h" 

class Level2 :public Levels {

protected:
	Texture selectTextureFlower;
	Sprite selectionFlower;

	Texture selectTextureWallnut;
	Sprite selectionWallnut;

	//Image map_image;
	Sprite map_image;

	Texture gridText;
	Sprite grid;

	Image npc;
	Texture n;
	Sprite s;
	bool normalS,			flowerS,				wallnutS,
		unselectableNormal, unselectableFlower,		unselectableWallnut,
		releasedNormal,		releasedFlower,			releasedWallnut;
	int deathCounts, lives;
	Clock selector[3];
	//sun Sun;

public:
	Level2() :Levels()
	{
		lives = 5;
		normalS = 0;					flowerS = 0;					wallnutS = 0;
		unselectableNormal = 0;			unselectableFlower = 0;			unselectableWallnut = 0;
		releasedNormal = 0;				releasedFlower = 0;				releasedWallnut = 0;
		deathCounts = 0;
		selectTextureWallnut.loadFromFile("Sprites_update/Plants/selectWallnut.png");
		selectionWallnut.setTexture(selectTextureWallnut);
		selectionWallnut.setTextureRect(IntRect(0, 0, 24, 24));
		selectionWallnut.setPosition(posX, posY + gap * 2);
		selectionWallnut.setScale(3, 2.5);

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
		zom->factory(2);
		for (int i = 0; i < 15; i++) {
			if (i <= 5)				waveCheck[i] = rand() % 50 + 15;   //First Wave
			else if (i <= 10)		waveCheck[i] = rand() % 100 + 65;  //Second Wave
			else					waveCheck[i] = rand() % 130 + 100;  //Third Wave
		}

		npc.loadFromFile("Sprites_update/bg/npc.png");
		n.loadFromImage(npc);
		s.setTexture(n);
		s.setScale(0.2, 0.2);
	
		gridText.loadFromFile("Sprites_update/bg/grid.png");
		grid.setTexture(gridText);
		grid.setPosition(252, 79);
		grid.setScale(0.88, 0.90);

		mapTexture.loadFromFile("Sprites_update/bg/level2.jpg");
		s_map.setTexture(mapTexture);
		s_map.setPosition(0, 0);
		s_map.setScale(1.13, 1.16);
	}

	virtual int gameloop(RenderWindow& window, int& score)
	{
		Music menuMusic;
		menuMusic.openFromFile("music/menubutton.wav");
		settingMenu setting(menuMusic, 50, 50);

		sf::Color color;
		sf::Music bg;
		bg.openFromFile("Sprites_update/bg/ID.ogg");
		bg.play();

		while (window.isOpen())
		{
			if (deathCounts >= 15 || Keyboard::isKeyPressed(Keyboard::A))
				return 5;
			if (lives <= 0)
				return -1;
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
			window.draw(grid);

			int X = Mouse::getPosition(window).x,
				Y = Mouse::getPosition(window).y,
				coll = int((X - 253) / 80),
				roww = int((Y - 83) / 97);


			// This codition is just so that i can squeeze whole if making code better
			if (sunNo >= 0)
			{
				// For sunFlower
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

				// For Pea shooter
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
				// For Wall Nut
				if (sunNo < 50)
				{
					color = selectionWallnut.getColor();					// Gets the color of sprite for opacity
					color.a = 128;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionWallnut.setColor(color);					// Set that opacity color
				}
				else if (sunNo >= 50 && !unselectableWallnut)
				{
					color = selectionWallnut.getColor();					// Gets the color of sprite for opacity
					color.a = 255;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionWallnut.setColor(color);					// Set that opacity color
				}
			}

			// This deals with the selection of the plants
			if (Mouse::isButtonPressed(Mouse::Left) && selectClk.getElapsedTime().asMilliseconds() > 1000)
			{
				selectClk.restart();

				if (!unselectableNormal && !flowerS && !wallnutS && X > posX && X<posX + 67 && Y>posY && Y < posY + 51)
				{
					unselectableNormal = 1;								// Normal pea cannot be selected now
					color = selectionNormal.getColor();					// Gets the color of sprite for opacity
					color.a = 128;		// 50% of 255 (maximum alpha)	   set Opacity 
					selectionNormal.setColor(color);					// Set that opacity color
					normalS = 1;										// normal is selected
				}

				else if (!unselectableFlower && !normalS && !wallnutS && X > posX && X<posX + 67 && Y>posY + gap && Y < posY + gap + 54)
				{
					unselectableFlower = 1;
					color = selectionFlower.getColor();
					color.a = 128;
					selectionFlower.setColor(color);
					flowerS = 1;
				}

				else if (!unselectableWallnut && !normalS && !flowerS && X > posX && X<posX + 67 && Y>posY + gap*2 && Y < posY + gap*2 + 54)
				{
					unselectableWallnut = 1;
					color = selectionWallnut.getColor();
					color.a = 128;
					selectionWallnut.setColor(color);
					wallnutS = 1;
				}

			}


			// This resets / allows the selection after the restricted timer ends
			if (releasedNormal && unselectableNormal && selector[0].getElapsedTime().asSeconds() > 3)
			{
				color = selectionNormal.getColor();					// Gets the color of sprite for opacity
				color.a = 255;										// set Opacity to 0
				selectionNormal.setColor(color);					// Set that opacity color
				releasedNormal = 0;									// Normal is released
				unselectableNormal = 0;								// Now we can select normal Pea
			}
			else if (releasedFlower && unselectableFlower && selector[1].getElapsedTime().asSeconds() > 3)
			{
				color = selectionFlower.getColor();					// Gets the color of sprite for opacity
				color.a = 255;										// set Opacity to 0
				selectionFlower.setColor(color);					// Set that opacity color
				releasedFlower = 0;									// Normal is released
				unselectableFlower = 0;								// Now we can select normal Pea
			}
			else if (releasedWallnut && unselectableWallnut && selector[2].getElapsedTime().asSeconds() > 6)
			{
				color = selectionWallnut.getColor();					// Gets the color of sprite for opacity
				color.a = 255;										// set Opacity to 0
				selectionWallnut.setColor(color);					// Set that opacity color
				releasedWallnut = 0;									// Normal is released
				unselectableWallnut = 0;								// Now we can select normal Pea
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
					else if (wallnutS)
					{
						selector[2].restart();
						releasedWallnut = 1;
						FIELD_GAME_STATUS[roww][coll] = 'W';
						arr[roww * COLS + coll] = new wallNut(253 + 80 * coll, 83 + 97 * roww);
						wallnutS = 0;
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
							{
								arr[row * COLS + column]->shoot(window);
							}
							else if (FIELD_GAME_STATUS[row][column] == 'F')
							{
								if (arr[row * COLS + column]->sunWorking(window))
									sunNo += 25;
							}
						}
					}
				}
			}

			textSun.setString("Score: " + to_string(sunNo));
			lev.setFillColor(Color::White);
			lev.setString("KILL 15 ZoMbIeS!!!!");
			scor.setString("SCORE: " + to_string(score));

			window.draw(selectionNormal);					// Print selections icon
			window.draw(selectionFlower);					// Print selections icon
			window.draw(selectionWallnut);
			window.draw(lev);
			window.draw(sunBoardSprite);					// Print sun number board
			window.draw(textSun);							// Print the text sun number

			for (int i = 0; i < 5; ++i)
				window.draw(lawnMowerSprite[i]);

			if (Keyboard::isKeyPressed(Keyboard::G))
				Levels::printGrid(FIELD_GAME_STATUS, ROWS, COLS);		// For printing grid

			drawZombie(window);
			CollisionCheck(ROWS, COLS);
			BulletCollision(score);

			rect.checkPos(window);						// grid rectangle position

			// Extra zombies for aesthetics
			int row1 = 0, col1 = 995;
			for (int i = 0; i < 5; i++) {
				s.setPosition(col1, row1);
				row1 += 110;
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
			{
				zom->zombie[i]->Eatdisplay(window);

			}
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
						if ((FIELD_GAME_STATUS[l][j] == 'N' || FIELD_GAME_STATUS[l][j] == 'F' || FIELD_GAME_STATUS[l][j] == 'W') && l == y && j == x + 1) {
							if (arr[l * 9 + j]->getHealth() <= 0) {
								zom->zombie[i]->Plantdetected = 0;
								FIELD_GAME_STATUS[l][j] = ' ';
								delete arr[l * 9 + j];
								arr[l * 9 + j] = nullptr;
							}
							else if (FIELD_GAME_STATUS[l][j] == 'N' || FIELD_GAME_STATUS[l][j] == 'F' || FIELD_GAME_STATUS[l][j] == 'W' && arr[l * 9 + j]->getHealth() > 0) {
								arr[l * 9 + j]->setHealth(arr[l * 9 + j]->getHealth() - 1);
							}
							zom->zombie[i]->Plantdetected = 1;
						}

						else if (FIELD_GAME_STATUS[l][j] == ' ' && l == y && j == x + 1) {
							zom->zombie[i]->Plantdetected = 0;
						}

						else if ((FIELD_GAME_STATUS[l][j] == 'N' || FIELD_GAME_STATUS[l][j] == 'F' || FIELD_GAME_STATUS[l][j] == 'W') && l == y && j == x + 1)
							zom->zombie[i]->Plantdetected = 1;

					}
				}
			}
		}
	}

	void BulletCollision(int & score) {  //Bullet And Zombie
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
								deathCounts++;
								if (zom->zombie[i]->type == 'S')
									score += 20;
								else if (zom->zombie[i]->type == 'F')
									score += 30;
								zom->zombie[i]->zombieExist = 0;
								zom->zombie[i]->health = 100;
								zom->zombie[i]->zomPosX = (rand() % 5) * 97 + 65;
								zom->zombie[i]->zomPosY = 0;
							}
						}
						if (zom->zombie[i]->zombieExist && (arr[j * 9 + l]->getposY() - 83) / 97 == (zom->zombie[i]->zomPosY) / 97)
							arr[j * 9 + l]->setExist(1);
					}
				}
			}
		}
	}

	~Level2() {
		for (int i = 0; i < 15; i++) {
			delete zom->zombie[i];
		}
		delete zom;
	}
};