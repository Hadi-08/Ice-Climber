#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "string_utils.hpp"
#include "sprites.hpp"
#include "background.hpp"
#include "camera.hpp"
#include "settings.hpp"
#include "stages.hpp"
#include "graphics.hpp"
#include "menu.hpp"

using namespace std;

// Game board
extern char board[BOARD_HEIGHT][BOARD_WIDTH];

// Floor data
extern int floorY[FLOORS];
extern int holeX[FLOORS];
extern int floorOffsetX[FLOORS];

// Breakable blocks
extern int breakX[FLOORS];
extern bool breakActive[FLOORS];
extern int breakX2[FLOORS];
extern bool breakActive2[FLOORS];

// Enemy data
extern int enemyX[ENEMIES];
extern int enemyY[ENEMIES];
extern int enemyDir[ENEMIES];

// Player data
extern int playerX, playerY;
extern int velocityY;
extern bool isJumping;
extern bool gameOver;
extern int lives;
extern int score;
extern int highScore;

// Function declarations
void loadHighScore();
void saveHighScore();
void clearBoard();
void drawBorder();
void drawFloors();
void drawEnemies();
void drawPlayer();
void initializeGame();
void movePlayerInput();
bool onPlatform();
void respawn();
void platformPhysics();
void checkClimb();
void moveEnemies();
void checkEnemyCollision();
void updateGame();
#endif