#include "stages.hpp"
#include "background.hpp"

// Global stage variables
int currentStage = 1;
int stageType = 0;
bool isBonusStage = false;

// Get stage type based on stage number
int getStageType(int stageNum) {
    if (stageNum <= 2) return 0;
    if (stageNum <= 4) return 1;
    if (stageNum <= 6) return 2;
    return 3;
}
// Load appropriate background for stage
void loadStageBackground(sf::Texture& texture, int stageNum) {
    int type = getStageType(stageNum);
    if (type == 0) {
        createMountainBackground(texture);
    }
    else if (type == 1) {
        createIceCaveBackground(texture);
    }
    else if (type == 2) {
        createSnowPeakBackground(texture);
    }
    else if (type == 3) {
        createGlacierBackground(texture);
    }
}
// Load bonus stage background
void loadBonusBackground(sf::Texture& texture) {
    createBonusBackground(texture);
}

// Advance to next stage
void advanceStage() {
    currentStage++;
    if (currentStage > MAX_STAGES) {
        currentStage = 1; // Loop back to start
    }
    stageType = getStageType(currentStage);
}

// Start bonus stage
void startBonusStage() {
    isBonusStage = true;
}

// End bonus stage
void endBonusStage() {
    isBonusStage = false;
}