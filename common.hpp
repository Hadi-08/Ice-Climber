#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

// Window settings
#define WINDOW_WIDTH 1120
#define WINDOW_HEIGHT 800
#define TILE_SIZE 16

// Game board 
#define BOARD_WIDTH 70
#define BOARD_HEIGHT 50

// Game states
#define STATE_MAIN_MENU 0
#define STATE_PLAYING 1
#define STATE_PAUSE 2
#define STATE_SETTINGS 3
#define STATE_GAME_OVER 4
#define STATE_HOW_TO_PLAY 5
#define STATE_HIGH_SCORE 6
#define STATE_STAGE_COMPLETE 7
#define STATE_BONUS_STAGE 8

// Player settings
#define MAX_LIVES 3
#define JUMP_VELOCITY -2
#define MAX_FALL_VELOCITY 2

// Level settings
#define FLOORS 8
#define ENEMIES 5
#define MAX_STAGES 8
#define COLLECTIBLES 10

// Stage types
#define STAGE_MOUNTAIN 0
#define STAGE_ICE_CAVE 1
#define STAGE_SNOW_PEAK 2
#define STAGE_GLACIER 3
#define STAGE_BONUS 4

// Scoring
#define BREAK_BLOCK_POINTS 10
#define COLLECTIBLE_POINTS 100
#define STAGE_COMPLETE_POINTS 1000
#define BONUS_STAGE_POINTS 5000
#define WIN_POINTS 2000

// Pixel sizes
#define PLAYER_WIDTH 32.0f
#define PLAYER_HEIGHT 40.0f
#define ENEMY_SIZE 32.0f
#define BLOCK_WIDTH 16.0f
#define BLOCK_HEIGHT 16.0f
#define VEGETABLE_SIZE 24.0f

// Camera settings
#define CAMERA_FOLLOW_SPEED 0.1f
#define CAMERA_THRESHOLD 300.0f // Start scrolling when player is 300px from top

// Difficulty settings
#define DIFFICULTY_EASY 0
#define DIFFICULTY_NORMAL 1
#define DIFFICULTY_HARD 2

// String buffer
#define MAX_STRING_LENGTH 256
#define MAX_HIGH_SCORES 10000

#endif