#ifndef FILE_IO_H
#define FILE_IO_H
 
#include <fstream>
#include <iostream>
#include "common.hpp"

using namespace std;

// Function declarations
void saveHighScores(int highScores[]);
void loadHighScores(int highScores[]);

void saveGame(float playerX, float playerY, float velX, float velY, int lives,
    int score, int level, float cameraOffsetY,
    float platformX[], float platformY[], int platformType[],
    bool platformActive[], int platformCount,
    float enemyX[], float enemyY[], float enemyVelX[],
    bool enemyActive[], int enemyCount,
    float collectX[], float collectY[], bool collectActive[], int collectCount);

bool loadGame(float& playerX, float& playerY, float& velX, float& velY, int& lives,
    int& score, int& level, float& cameraOffsetY,
    float platformX[], float platformY[], int platformType[],
    bool platformActive[], int& platformCount,
    float enemyX[], float enemyY[], float enemyVelX[],
    bool enemyActive[], int& enemyCount,
    float collectX[], float collectY[], bool collectActive[], int& collectCount);

#endif