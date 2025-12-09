#ifndef SPRITES_HPP
#define SPRITES_HPP

#include <SFML/Graphics.hpp>

// ============================================================================
// CHARACTER SPRITES
// ============================================================================

// POPO (Blue Ice Climber Character)
void createPopoSprite(sf::Texture& texture);

// TOPI (White Seal Enemy)
void createTopiSprite(sf::Texture& texture);

// ============================================================================
// VEGETABLE SPRITES (Collectibles)
// ============================================================================

void createEggplantSprite(sf::Texture& texture);
void createCarrotSprite(sf::Texture& texture);
void createCabbageSprite(sf::Texture& texture);

#endif // SPRITES_HPP