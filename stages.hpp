#ifndef STAGES_HPP
#define STAGES_HPP

#include <SFML/Graphics.hpp>
#include "common.hpp"

// Current stage info
extern int currentStage;
extern int stageType;
extern bool isBonusStage;

// Function declarations
int getStageType(int stageNum);
void loadStageBackground(sf::Texture& texture, int stageNum);
void loadBonusBackground(sf::Texture& texture);
void advanceStage();
void startBonusStage();
void endBonusStage();

#endif