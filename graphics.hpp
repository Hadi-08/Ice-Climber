#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "common.hpp"

using namespace std;

extern sf::Sprite player;
// Function declarations
bool loadResources(sf::Texture& playerTex, sf::Texture& enemyTex,
    sf::Texture& eggplantTex, sf::Texture& carrotTex, sf::Texture& cabbageTex,
    sf::Texture& bgTex, sf::Font& font,
    sf::SoundBuffer& jumpBuf, sf::SoundBuffer& breakBuf,
    sf::SoundBuffer& hitBuf, sf::SoundBuffer& collectBuf);

void renderGame(sf::RenderWindow& window, sf::Texture& bgTex, sf::Texture& playerTex,
    sf::Texture& enemyTex, sf::Texture& eggplantTex, sf::Font& font);

void drawStageComplete(sf::RenderWindow& window, sf::Font& font);

#endif