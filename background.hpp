#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

// Background functions for different stage types
void createMountainBackground(sf::Texture& texture);
void createIceCaveBackground(sf::Texture& texture);
void createSnowPeakBackground(sf::Texture& texture);
void createGlacierBackground(sf::Texture& texture);
void createBonusBackground(sf::Texture& texture);

#endif