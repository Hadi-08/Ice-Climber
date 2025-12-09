#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "common.hpp"

using namespace std;

// Function declarations
void drawMainMenu(sf::RenderWindow& window, sf::Font& font, int selectedOption);
void handleMainMenuInput(sf::Keyboard::Key key, int& selectedOption, int& gameState);
void drawHighScore(sf::RenderWindow& window, sf::Font& font);
void drawHowToPlay(sf::RenderWindow& window, sf::Font& font);
void drawPauseMenu(sf::RenderWindow& window, sf::Font& font, int selectedOption);
void handlePauseMenuInput(sf::Keyboard::Key key, int& selectedOption, int& gameState);
void drawGameOver(sf::RenderWindow& window, sf::Font& font);

#endif