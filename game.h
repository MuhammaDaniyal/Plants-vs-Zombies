#pragma once

/*
    main = 0
    game = 1
    pause = 2
    highscore = 3
    setting = 4
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ctime>

#include "Level.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

#include "mainMenu.h"
#include "settings.h"
#include "highscore.h"

using namespace sf;

class game {

protected:
    RenderWindow window; 
    Image icon;

    int score;

    Texture unlockText[2],          glowText,           backgroundText[2];
    Sprite  unlockSprite[2],        glowSprite,         backgroundSprite[2]; 

    Clock clk[2];

public:
    game() : window(sf::VideoMode(1366, 601), "Plants Vs Zombies") 
    {
        window.setPosition(sf::Vector2i(0, 0)); // Initialize the window position
        !icon.loadFromFile("Sprites_update/bg/icon.png");
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
   
    
        backgroundText[0].loadFromFile("Sprites_update/bg/level1.png");
        backgroundSprite[0].setTexture(backgroundText[0]);
        backgroundSprite[0].setPosition(0, 0);
        
        backgroundText[1].loadFromFile("Sprites_update/bg/level2.jpg");
        backgroundSprite[1].setTexture(backgroundText[1]);
        backgroundSprite[1].setPosition(0, 0);
        backgroundSprite[1].setScale(1.13, 1.16);

        unlockText[0].loadFromFile("Sprites_update/Plants/selectWallnut.png");
        unlockSprite[0].setTexture(unlockText[0]);
        unlockSprite[0].setTextureRect(IntRect(0, 0, 25, 26));
        unlockSprite[0].setPosition(550, 230);
        unlockSprite[0].setScale(3, 2.5);

        unlockText[1].loadFromFile("Sprites_update/Plants/selectCherry.png");
        unlockSprite[1].setTexture(unlockText[1]);
        unlockSprite[1].setTextureRect(IntRect(0, 0, 25, 26));
        unlockSprite[1].setPosition(550, 230);
        unlockSprite[1].setScale(3, 2.5);

        glowText.loadFromFile("Sprites_update/bg/glow11.png");
        //glowText.loadFromFile("Sprites_update/bg/glowCopy.jpg");
        //glowText.loadFromFile("Sprites_update/bg/w2.png");
        //glowText.loadFromFile("Sprites_update/bg/t1.jpg");
        glowSprite.setTexture(glowText);
        glowSprite.setTextureRect(IntRect(141, 89, 147, 179));
        glowSprite.setPosition(500, 230);
        //glowSprite.setScale(3, 2.5);

        score = 0;
    }

    void transition(Sprite& spritecard, Sprite& backgroundSprite)
    {

        float interval = 0.01, posX = 7 , posY = 5,
            wallX = 3, wallY = 3;

        clk[0].restart();
        while (clk[0].getElapsedTime().asSeconds() < 4)
        {
            if (clk[1].getElapsedTime().asMilliseconds() > 8)
            {
                clk[1].restart();
                glowSprite.setScale(1 + interval, 1 + interval);
                glowSprite.setPosition(500 - posX, 230 - posY);

                spritecard.setScale(3 + interval, 2.5 + interval);
                spritecard.setPosition( 550 - wallX, 230 - wallY);

                posX += 0.52;                posY += 0.52;
                wallX += 0.1;                wallY += 0.1;
                interval += 0.01;

            }

            window.draw(backgroundSprite);
            window.draw(glowSprite);
            window.draw(spritecard);

            window.display();
            window.clear();
        }
        clk[0].restart();
        while (clk[0].getElapsedTime().asSeconds() < 4)
        {
            window.draw(backgroundSprite);
            window.draw(glowSprite);
            window.draw(spritecard);

            window.display();
            window.clear();
        }

    }

    void gameStart() 
    {

        Music menuMusic;
        menuMusic.openFromFile("music/menubutton.wav");

        Music bgMusic;
        bgMusic.openFromFile("music/background/bg5.wav");
        bgMusic.setVolume(50);
        bgMusic.play();

        int size = 50, limit = 3, Switch = 0;
        bool gap = 1;
  
        pauseMenu pause(menuMusic, gap, 100, 200, size, limit);
        settingMenu setting(menuMusic, 50, size);
        mainMenu main(menuMusic, gap, 200, 400, 56, 5);

        while (window.isOpen())
        {
            window.display();
            window.clear();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return;
                }
            }

            if (Switch == 9)     pause.loop(window, score);

            if (Switch == 0)                Switch = main.loop(window);
            //Switch = pause.loop(window, backgroundSpriteMain);
            else if (Switch == 1)
            {
                bgMusic.stop();

                Levels* L = new Level1;
                Switch = L->gameloop(window, score);
                delete L;

                if (Switch == 5)
                {
                    transition(unlockSprite[0], backgroundSprite[0]);

                    L = new Level2;
                    Switch = L->gameloop(window, score);
                    delete L;

                    if (Switch == 5)
                    {
                        transition(unlockSprite[1], backgroundSprite[1]);
    
                        L = new Level3;
                        L->gameloop(window, score);
                        delete L;
                        Switch = pause.loop(window, score);
                    }
                    else
                    {
                        Switch = pause.loop(window, score);
                    }

                }
                else
                {
                    Switch = pause.loop(window,score);
                }



            }
            else if (Switch == 4)           Switch = setting.loop(window, bgMusic);
            else if (Switch == 3)
            {
                Switch = pause.showHighcore(window);
            }

            if (Switch == -1)    return;

        }

    }

};
