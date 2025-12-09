#include "file_io.hpp"
#include "file_io.hpp"

// Save high scores
void saveHighScores(int highScores[]) {
    ofstream file("highscores.dat");
    if (file.is_open()) {
        for (int i = 0; i < MAX_HIGH_SCORES; i++) {
            file << highScores[i] << endl;
        }
        file.close();
        cout << "High scores saved!" << endl;
    }
}

// Load high scores
void loadHighScores(int highScores[]) {
    ifstream file("highscores.dat");
    if (file.is_open()) {
        for (int i = 0; i < MAX_HIGH_SCORES; i++) {
            file >> highScores[i];
        }
        file.close();
        cout << "High scores loaded!" << endl;
    }
    else {
        for (int i = 0; i < MAX_HIGH_SCORES; i++) {
            highScores[i] = 0;
        }
    }
}

// Save game
void saveGame(float playerX, float playerY, float velX, float velY, int lives,
    int score, int level, float cameraOffsetY,
    float platformX[], float platformY[], int platformType[],
    bool platformActive[], int platformCount,
    float enemyX[], float enemyY[], float enemyVelX[],
    bool enemyActive[], int enemyCount,
    float collectX[], float collectY[], bool collectActive[], int collectCount) {

    ofstream file("savegame.dat");
    if (file.is_open()) {
        file << playerX << " " << playerY << " " << velX << " " << velY << endl;
        file << lives << " " << score << " " << level << " " << cameraOffsetY << endl;

        file << platformCount << endl;
        for (int i = 0; i < platformCount; i++) {
            file << platformX[i] << " " << platformY[i] << " "
                << platformType[i] << " " << platformActive[i] << endl;
        }

        file << enemyCount << endl;
        for (int i = 0; i < enemyCount; i++) {
            file << enemyX[i] << " " << enemyY[i] << " "
                << enemyVelX[i] << " " << enemyActive[i] << endl;
        }

        file << collectCount << endl;
        for (int i = 0; i < collectCount; i++) {
            file << collectX[i] << " " << collectY[i] << " "
                << collectActive[i] << endl;
        }

        file.close();
        cout << "Game saved!" << endl;
    }
}

// Load game
bool loadGame(float& playerX, float& playerY, float& velX, float& velY, int& lives,
    int& score, int& level, float& cameraOffsetY,
    float platformX[], float platformY[], int platformType[],
    bool platformActive[], int& platformCount,
    float enemyX[], float enemyY[], float enemyVelX[],
    bool enemyActive[], int& enemyCount,
    float collectX[], float collectY[], bool collectActive[], int& collectCount) {

    ifstream file("savegame.dat");
    if (file.is_open()) {
        file >> playerX >> playerY >> velX >> velY;
        file >> lives >> score >> level >> cameraOffsetY;

        file >> platformCount;
        for (int i = 0; i < platformCount; i++) {
            int active;
            file >> platformX[i] >> platformY[i] >> platformType[i] >> active;
            platformActive[i] = (active == 1);
        }

        file >> enemyCount;
        for (int i = 0; i < enemyCount; i++) {
            int active;
            file >> enemyX[i] >> enemyY[i] >> enemyVelX[i] >> active;
            enemyActive[i] = (active == 1);
        }

        file >> collectCount;
        for (int i = 0; i < collectCount; i++) {
            int active;
            file >> collectX[i] >> collectY[i] >> active;
            collectActive[i] = (active == 1);
        }

        file.close();
        cout << "Game loaded!" << endl;
        return true;
    }
    else {
        cout << "No save game found!" << endl;
        return false;
    }
}