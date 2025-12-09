#include "graphics.hpp"
#include "sprites.hpp"
#include "stages.hpp"
#include "game_logic.hpp"
#include "camera.hpp"
#include "string_utils.hpp"
#include <cmath>

// LOAD ALL RESOURCES
sf::Sprite player;

bool loadResources(sf::Texture& playerTex, sf::Texture& enemyTex,
    sf::Texture& eggplantTex, sf::Texture& carrotTex, sf::Texture& cabbageTex,
    sf::Texture& bgTex, sf::Font& font,
    sf::SoundBuffer& jumpBuf, sf::SoundBuffer& breakBuf,
    sf::SoundBuffer& hitBuf, sf::SoundBuffer& collectBuf) {

    cout << "Loading Ice Climber resources..." << endl;

    // Create sprites
    createPopoSprite(playerTex);
    createTopiSprite(enemyTex);
    createEggplantSprite(eggplantTex);
    createCarrotSprite(carrotTex);
    createCabbageSprite(cabbageTex);

    // Load initial stage background
    loadStageBackground(bgTex, currentStage);

    // Load font
    if (!font.loadFromFile("C:/Users/Lenovo/source/repos/IceClimber/arial.ttf")) {
        cout << "Warning: Font not found" << endl;
    }

    // Create sounds
    const unsigned int sampleRate = 44100;

    // Jump sound
    const unsigned int jumpSamples = 8000;
    sf::Int16* jumpData = new sf::Int16[jumpSamples];
    for (unsigned int i = 0; i < jumpSamples; i++) {
        jumpData[i] = 10000 * sin(2.0 * 3.14159 * 440.0 * i / sampleRate);
    }
    jumpBuf.loadFromSamples(jumpData, jumpSamples, 1, sampleRate);
    delete[] jumpData;

    // Break sound
    const unsigned int breakSamples = 6000;
    sf::Int16* breakData = new sf::Int16[breakSamples];
    for (unsigned int i = 0; i < breakSamples; i++) {
        breakData[i] = 12000 * sin(2.0 * 3.14159 * 880.0 * i / sampleRate);
    }
    breakBuf.loadFromSamples(breakData, breakSamples, 1, sampleRate);
    delete[] breakData;

    // Hit sound
    const unsigned int hitSamples = 10000;
    sf::Int16* hitData = new sf::Int16[hitSamples];
    for (unsigned int i = 0; i < hitSamples; i++) {
        hitData[i] = 15000 * sin(2.0 * 3.14159 * 220.0 * i / sampleRate);
    }
    hitBuf.loadFromSamples(hitData, hitSamples, 1, sampleRate);
    delete[] hitData;

    sf::SoundBuffer buffer;

    // Load audio file
    if (!buffer.loadFromFile("C:/Users/Lenovo/source/repos/IceClimber/BG.mp3")) {
        std::cerr << "Failed to load sound file!" << std::endl;
        return -1;
    }

    // Collect sound
    const unsigned int collectSamples = 5000;
    sf::Int16* collectData = new sf::Int16[collectSamples];
    for (unsigned int i = 0; i < collectSamples; i++) {
        collectData[i] = 9000 * sin(2.0 * 3.14159 * 1320.0 * i / sampleRate);
    }
    collectBuf.loadFromSamples(collectData, collectSamples, 1, sampleRate);
    delete[] collectData;

    cout << "Resources loaded successfully!" << endl;
    return true;
}

// RENDER GAME WITH CAMERA SCROLLING

void renderGame(sf::RenderWindow& window, sf::Texture& bgTex, sf::Texture& playerTex,
    sf::Texture& enemyTex, sf::Texture& eggplantTex, sf::Font& font) {

    float cameraOffset = getCameraOffset();

    // Draw background (scrolls with camera)
    sf::Sprite bg(bgTex);
    bg.setPosition(0, -cameraOffset * 0.5f); // Parallax effect
    window.draw(bg);

    // Draw board elements with camera offset
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            char tile = board[y][x];
            float pixelX = x * TILE_SIZE;
            float pixelY = y * TILE_SIZE - cameraOffset;

            // Only draw if visible on screen
            if (pixelY < -TILE_SIZE || pixelY > WINDOW_HEIGHT) {
                continue;
            }

            if (tile == '#') {
                // Border
                sf::RectangleShape border(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                border.setPosition(pixelX, pixelY);
                border.setFillColor(sf::Color(80, 80, 80));
                border.setOutlineThickness(1);
                border.setOutlineColor(sf::Color(120, 120, 120));
                window.draw(border);
            }
            else if (tile == '=') {
                // Ice platform
                sf::RectangleShape platform(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                platform.setPosition(pixelX, pixelY);
                platform.setFillColor(sf::Color(200, 230, 255));
                platform.setOutlineThickness(1);
                platform.setOutlineColor(sf::Color(150, 200, 255));
                window.draw(platform);

                // Ice shine effect
                sf::RectangleShape shine(sf::Vector2f(TILE_SIZE - 4, 3));
                shine.setPosition(pixelX + 2, pixelY + 2);
                shine.setFillColor(sf::Color(220, 240, 255, 150));
                window.draw(shine);
            }
            else if (tile == 'X') {
                // Breakable block
                sf::RectangleShape breakBlock(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                breakBlock.setPosition(pixelX, pixelY);
                breakBlock.setFillColor(sf::Color(180, 150, 120));
                breakBlock.setOutlineThickness(1);
                breakBlock.setOutlineColor(sf::Color(140, 110, 80));
                window.draw(breakBlock);

                // Crack pattern
                sf::RectangleShape crack1(sf::Vector2f(TILE_SIZE - 6, 1));
                crack1.setPosition(pixelX + 3, pixelY + 5);
                crack1.setFillColor(sf::Color(100, 70, 40));
                window.draw(crack1);

                sf::RectangleShape crack2(sf::Vector2f(TILE_SIZE - 6, 1));
                crack2.setPosition(pixelX + 3, pixelY + 10);
                crack2.setFillColor(sf::Color(100, 70, 40));
                window.draw(crack2);
            }
            else if (tile == 'P') {
                // Player (Popo)
                player.setTexture(playerTex);
                player.setPosition(pixelX - 8, pixelY - 16);
                window.draw(player);
            }
            else if (tile == 'E') {
                // Enemy (Topi)
                sf::Sprite enemy(enemyTex);
                enemy.setPosition(pixelX - 8, pixelY - 8);
                window.draw(enemy);
            }
            else if (tile == 'V') {
                // Vegetable (Eggplant)
                sf::Sprite veggie(eggplantTex);
                veggie.setPosition(pixelX - 4, pixelY - 4);
                window.draw(veggie);
            }
        }
    }

    // Draw HUD 
    sf::RectangleShape hudBg(sf::Vector2f(WINDOW_WIDTH, 70));
    hudBg.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(hudBg);

    // Lives
    char livesText[50];
    copyString(livesText, "Lives: ");
    char livesNum[10];
    intToCharArray(lives, livesNum);
    concatString(livesText, livesNum);

    sf::Text livesDisplay;
    livesDisplay.setFont(font);
    livesDisplay.setString(livesText);
    livesDisplay.setCharacterSize(22);
    livesDisplay.setFillColor(sf::Color::White);
    livesDisplay.setPosition(10, 10);
    window.draw(livesDisplay);

    // Score
    char scoreText[50];
    copyString(scoreText, "Score: ");
    char scoreNum[10];
    intToCharArray(score, scoreNum);
    concatString(scoreText, scoreNum);

    sf::Text scoreDisplay;
    scoreDisplay.setFont(font);
    scoreDisplay.setString(scoreText);
    scoreDisplay.setCharacterSize(22);
    scoreDisplay.setFillColor(sf::Color::Yellow);
    scoreDisplay.setPosition(10, 38);
    window.draw(scoreDisplay);

    // Stage
    char stageText[50];
    copyString(stageText, "Stage: ");
    char stageNum[10];
    intToCharArray(currentStage, stageNum);
    concatString(stageText, stageNum);

    sf::Text stageDisplay;
    stageDisplay.setFont(font);
    stageDisplay.setString(stageText);
    stageDisplay.setCharacterSize(22);
    stageDisplay.setFillColor(sf::Color::Cyan);
    stageDisplay.setPosition(WINDOW_WIDTH - 120, 10);
    window.draw(stageDisplay);

    // High Score
    char highScoreText[50];
    copyString(highScoreText, "High: ");
    char highScoreNum[10];
    intToCharArray(highScore, highScoreNum);
    concatString(highScoreText, highScoreNum);

    sf::Text highScoreDisplay;
    highScoreDisplay.setFont(font);
    highScoreDisplay.setString(highScoreText);
    highScoreDisplay.setCharacterSize(22);
    highScoreDisplay.setFillColor(sf::Color(255, 215, 0));
    highScoreDisplay.setPosition(WINDOW_WIDTH - 120, 38);
    window.draw(highScoreDisplay);

    // Controls hint
    sf::Text controls;
    controls.setFont(font);
    controls.setString("A/D:Move W:Jump ESC:Menu");
    controls.setCharacterSize(16);
    controls.setFillColor(sf::Color(180, 180, 180));
    controls.setPosition(WINDOW_WIDTH / 2 - 130, 10);
    window.draw(controls);
}

// Draw stage complete screen
void drawStageComplete(sf::RenderWindow& window, sf::Font& font) {
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    // Stage Complete text
    sf::Text title;
    title.setFont(font);
    title.setString("STAGE COMPLETE!");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Green);
    title.setOutlineThickness(3);
    title.setOutlineColor(sf::Color(0, 150, 0));
    title.setPosition(WINDOW_WIDTH / 2 - 250, 200);
    window.draw(title);

    // Stage number
    char stageText[100];
    copyString(stageText, "Stage ");
    char stageNum[10];
    intToCharArray(currentStage, stageNum);
    concatString(stageText, stageNum);
    concatString(stageText, " Cleared!");

    sf::Text stageDisplay;
    stageDisplay.setFont(font);
    stageDisplay.setString(stageText);
    stageDisplay.setCharacterSize(40);
    stageDisplay.setFillColor(sf::Color::White);
    stageDisplay.setPosition(WINDOW_WIDTH / 2 - 180, 300);
    window.draw(stageDisplay);

    // Bonus
    sf::Text bonusText;
    bonusText.setFont(font);
    bonusText.setString("+1000 Stage Bonus!");
    bonusText.setCharacterSize(30);
    bonusText.setFillColor(sf::Color::Yellow);
    bonusText.setPosition(WINDOW_WIDTH / 2 - 160, 370);
    window.draw(bonusText);

    // Continue
    sf::Text continueText;
    continueText.setFont(font);
    continueText.setString("Press ENTER to continue");
    continueText.setCharacterSize(24);
    continueText.setFillColor(sf::Color(200, 200, 200));
    continueText.setPosition(WINDOW_WIDTH / 2 - 180, 480);
    window.draw(continueText);
}