#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "common.hpp"

// Settings values
extern float musicVolume;
extern float sfxVolume;
extern int difficulty;

// Function declarations
void drawSettings(sf::RenderWindow& window, sf::Font& font, int selectedOption);
void handleSettingsInput(sf::Keyboard::Key key, int& selectedOption, int& gameState, sf::Music& bgMusic);

#endif