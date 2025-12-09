#include "game_logic.hpp"
#include <fstream>

using namespace std;

// Game board
char board[BOARD_HEIGHT][BOARD_WIDTH];

// Floor data
int floorY[FLOORS];
int holeX[FLOORS];
int floorOffsetX[FLOORS];

// Breakable blocks
int breakX[FLOORS];
bool breakActive[FLOORS];
int breakX2[FLOORS];
bool breakActive2[FLOORS];

// Enemy data
int enemyX[ENEMIES];
int enemyY[ENEMIES];
int enemyDir[ENEMIES];

// Player data
int playerX, playerY;
int velocityY = 0;
bool isJumping = false;
bool gameOver = false;
int lives = MAX_LIVES;
int score = 0;
int highScore = 0;

// FILE HANDLING
void loadHighScore() {
    ifstream file("high_score.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
        cout << "High score loaded: " << highScore << endl;
    }
    else {
        highScore = 0;
    }
}

void saveHighScore() {
    ofstream file("high_score.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
        cout << "High score saved: " << highScore << endl;
    }
}

// BOARD MANAGEMENT

void clearBoard() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
        }
    }
}

void drawBorder() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        board[0][i] = '#';
        board[BOARD_HEIGHT - 1][i] = '#';
    }
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        board[i][0] = '#';
        board[i][BOARD_WIDTH - 1] = '#';
    }
}

void drawFloors() {
    for (int i = 0; i < FLOORS; i++) {
        int y = floorY[i];

        // Ground floor (solid)
        if (i == 0) {
            for (int x = 1; x < BOARD_WIDTH - 1; x++) {
                board[y][x] = '=';
            }
            continue;
        }

        int offset = floorOffsetX[i];

        // Clear floor line
        for (int x = 1; x < BOARD_WIDTH - 1; x++) {
            board[y][x] = ' ';
        }

        // Platform 1
        int p1_start = 1 + offset;
        int p1_end = 25 + offset;
        for (int x = p1_start; x < p1_end && x < BOARD_WIDTH - 1; x++) {
            board[y][x] = '=';
        }

        // Platform 2
        int p2_start = 30 + offset;
        int p2_end = 56 + offset;
        for (int x = p2_start; x < p2_end && x < BOARD_WIDTH - 1; x++) {
            board[y][x] = '=';
        }

        // Platform 3
        int p3_start = 60 + offset;
        int p3_end = BOARD_WIDTH - 1;
        for (int x = p3_start; x < p3_end && x < BOARD_WIDTH - 1; x++) {
            board[y][x] = '=';
        }

        // Breakable block 1
        if (breakActive[i]) {
            for (int b = 0; b < 3; b++) {
                board[y][breakX[i] + b] = 'X';
            }
        }
        else {
            for (int b = 0; b < 3; b++) {
                board[y][breakX[i] + b] = ' ';
            }
        }

        // Breakable block 2
        if (breakActive2[i]) {
            for (int b = 0; b < 3; b++) {
                board[y][breakX2[i] + b] = 'X';
            }
        }
        else {
            for (int b = 0; b < 3; b++) {
                board[y][breakX2[i] + b] = ' ';
            }
        }

        // Hole
        for (int h = 0; h < 6; h++) {
            board[y][holeX[i] + h] = ' ';
        }
    }
}

void drawEnemies() {
    for (int i = 0; i < ENEMIES; i++) {
        board[enemyY[i]][enemyX[i]] = 'E';
    }
}

void drawPlayer() {
    board[playerY][playerX] = 'P';
}

// GAME INITIALIZATION

void initializeGame() {
    playerX = 15;
    playerY = BOARD_HEIGHT - 3;
    /*score = 0;*/
    lives = MAX_LIVES;
    gameOver = false;
    isJumping = false;
    velocityY = 0;

    // Initialize floors
    for (int i = 0; i < FLOORS; i++) {
        floorY[i] = BOARD_HEIGHT - 2 - (i * 3);
        int offset = (i % 3) * 10;
        floorOffsetX[i] = offset;

        if (i > 0) {
            breakX[i] = 10 + offset;
            breakActive[i] = true;
            breakX2[i] = 45 + offset;
            breakActive2[i] = true;
            holeX[i] = 22 + offset;
        }
        else {
            holeX[i] = -10;
            breakActive[i] = false;
            breakActive2[i] = false;
            floorOffsetX[i] = 0;
        }
    }

    // Initialize enemies
    int enemyFloors[ENEMIES] = { 0, 2, 4, 6, 7 };
    for (int i = 0; i < ENEMIES; i++) {
        int floorIndex = enemyFloors[i];
        enemyY[i] = floorY[floorIndex] - 1;
        enemyX[i] = (i * 11) % (BOARD_WIDTH - 5) + 3;
        enemyDir[i] = (i % 2 == 0) ? 1 : -1;
    }

    cout << "Game initialized" << endl;
}

// PLAYER MOVEMENT

void movePlayerInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerX > 1) {
        playerX--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerX < BOARD_WIDTH - 2) {
        playerX++;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
        isJumping = true;
        velocityY = JUMP_VELOCITY;
    }
}

// PHYSICS

bool onPlatform() {
    for (int i = 0; i < FLOORS; i++) {
        int fy = floorY[i];
        if (playerY + 1 == fy) {
            char tile = board[fy][playerX];
            if (tile == '=' || tile == 'X') {
                return true;
            }
        }
    }
    return false;
}

void respawn() {
    lives--;
    if (lives <= 0) {
        gameOver = true;
        return;
    }
    playerX = 15;
    playerY = BOARD_HEIGHT - 3;
    isJumping = false;
    velocityY = 0;
}

void platformPhysics() {
    int nextY = playerY + velocityY;

    // Check ceiling collision
    if (isJumping && velocityY < 0) {
        for (int i = 0; i < FLOORS; i++) {
            int fy = floorY[i];
            if (nextY <= fy && playerY > fy) {
                // Check breakable block 1
                bool isUnderBreakable1 = (playerX >= breakX[i] && playerX <= breakX[i] + 2);
                if (breakActive[i] && isUnderBreakable1) {
                    breakActive[i] = false;
                    score += BREAK_BLOCK_POINTS;
                    velocityY = 1;
                    playerY = fy + 1;
                    playerX = breakX[i] + 1;
                    return;
                }

                // Check breakable block 2
                bool isUnderBreakable2 = (playerX >= breakX2[i] && playerX <= breakX2[i] + 2);
                if (breakActive2[i] && isUnderBreakable2) {
                    breakActive2[i] = false;
                    score += BREAK_BLOCK_POINTS;
                    velocityY = 1;
                    playerY = fy + 1;
                    playerX = breakX2[i] + 1;
                    return;
                }

                // Solid ceiling
                char ceilingTile = board[fy][playerX];
                if (ceilingTile == '=') {
                    velocityY = 1;
                    playerY = fy + 1;
                    return;
                }
            }
        }
    }

    // Apply movement
    if (isJumping) {
        playerY = nextY;
        velocityY++;
        if (velocityY > MAX_FALL_VELOCITY) {
            velocityY = MAX_FALL_VELOCITY;
        }
    }

    // Check landing
    if (isJumping && velocityY > 0) {
        for (int i = 0; i < FLOORS; i++) {
            int fy = floorY[i];
            if (playerY + 1 >= fy) {
                if (onPlatform()) {
                    isJumping = false;
                    velocityY = 0;
                    playerY = fy - 1;
                    return;
                }
            }
        }
    }

    // Continuous falling
    if (!isJumping && !onPlatform()) {
        playerY++;
    }

    // Death boundary
    if (playerY >= BOARD_HEIGHT - 1) {
        respawn();
    }
}

void checkClimb() {
    if (playerY < 1) {
        score += WIN_POINTS;
        gameOver = true;
    }
}
// ENEMY LOGIC

void moveEnemies() {
    for (int i = 0; i < ENEMIES; i++) {
        enemyX[i] += enemyDir[i];

        if (enemyX[i] <= 1) {
            enemyX[i] = 2;
            enemyDir[i] = 1;
        }
        if (enemyX[i] >= BOARD_WIDTH - 2) {
            enemyX[i] = BOARD_WIDTH - 3;
            enemyDir[i] = -1;
        }
    }
}

void checkEnemyCollision() {
    for (int i = 0; i < ENEMIES; i++) {
        if (playerX == enemyX[i] && playerY == enemyY[i]) {
            respawn();
            return;
        }
    }
}
// GAME UPDATE

void updateGame() {
    clearBoard();
    drawBorder();
    drawFloors();

    movePlayerInput();
    moveEnemies();
    platformPhysics();
    checkClimb();
    checkEnemyCollision();

    drawEnemies();
    drawPlayer();

    // Update high score
    if (gameOver && score > highScore) {
        highScore = score;
        saveHighScore();
    }
}