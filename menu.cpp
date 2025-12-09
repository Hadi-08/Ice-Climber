#include "menu.hpp"
#include "string_utils.hpp"
#include "game_logic.hpp"
#include "camera.hpp"
#include "stages.hpp"

// MAIN MENU

void drawMainMenu(sf::RenderWindow& window, sf::Font& font, int selectedOption) {
    // Title with Ice Climber style
    sf::Text title;
    title.setFont(font);
    title.setString("The Icy Ascent");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color(82, 163, 255)); // Ice Climber blue
    title.setOutlineThickness(4);
    title.setOutlineColor(sf::Color::White);
    title.setPosition(WINDOW_WIDTH / 2 - 280, 80);
    window.draw(title);

    // Subtitle
    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString(" ");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(sf::Color::White);
    subtitle.setPosition(WINDOW_WIDTH / 2 - 100, 180);
    window.draw(subtitle);

    // Menu options
    const char* menuItems[5] = {
        "1. Start New Game",
        "2. High Score",
        "3. How To Play",
        "4. Settings",
        "5. Exit"
    };

    for (int i = 0; i < 5; i++) {
        sf::Text menuText;
        menuText.setFont(font);
        menuText.setString(menuItems[i]);
        menuText.setCharacterSize(32);
        menuText.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);

        // Add selection indicator
        if (i == selectedOption) {
            menuText.setOutlineThickness(2);
            menuText.setOutlineColor(sf::Color(255, 200, 0));
        }

        menuText.setPosition(WINDOW_WIDTH / 2 - 140, 280 + i * 60);
        window.draw(menuText);
    }

    // Instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString(" ");
    instructions.setCharacterSize(18);
    instructions.setFillColor(sf::Color(180, 180, 180));
    instructions.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT - 60);
    window.draw(instructions);
}

void handleMainMenuInput(sf::Keyboard::Key key, int& selectedOption, int& gameState) {
    if (key == sf::Keyboard::Up) {
        selectedOption--;
        if (selectedOption < 0) selectedOption = 4;
    }
    else if (key == sf::Keyboard::Down) {
        selectedOption++;
        if (selectedOption > 4) selectedOption = 0;
    }
    else if (key == sf::Keyboard::Enter) {
        if (selectedOption == 0) { // Start New Game
            initializeGame();
            resetCamera();
            currentStage = 1;
            gameState = STATE_PLAYING;
        }
        else if (selectedOption == 1) { // High Score
            gameState = STATE_HIGH_SCORE;
        }
        else if (selectedOption == 2) { // How To Play
            gameState = STATE_HOW_TO_PLAY;
        }
        else if (selectedOption == 3) { // Settings
            gameState = STATE_SETTINGS;
        }
        else if (selectedOption == 4) { // Exit
            // Window will close in main
        }
    }
}

// HIGH SCORE SCREEN
void drawHighScore(sf::RenderWindow& window, sf::Font& font) {
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("HIGH SCORE");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(255, 215, 0)); // Gold
    title.setOutlineThickness(3);
    title.setOutlineColor(sf::Color(200, 170, 0));
    /*Centre Align HIGHSCORE!!!*/
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
        titleBounds.top + titleBounds.height / 2.0f);
    title.setPosition(WINDOW_WIDTH / 2.0f, 150);
    window.draw(title);

    // High score display
    char scoreText[50];
    intToCharArray(highScore, scoreText);

    sf::Text scoreDisplay;
    scoreDisplay.setFont(font);
    scoreDisplay.setString(scoreText);
    scoreDisplay.setCharacterSize(100);
    scoreDisplay.setFillColor(sf::Color::Yellow);
    scoreDisplay.setOutlineThickness(3);
    scoreDisplay.setOutlineColor(sf::Color(255, 200, 0));
    // Center align score
    sf::FloatRect scoreBounds = scoreDisplay.getLocalBounds();
    scoreDisplay.setOrigin(scoreBounds.left + scoreBounds.width / 2.0f,
        scoreBounds.top + scoreBounds.height / 2.0f);
    scoreDisplay.setPosition(WINDOW_WIDTH / 2.0f, 310);
    window.draw(scoreDisplay);;

    // Label
    sf::Text label;
    label.setFont(font);
    label.setString("points");
    label.setCharacterSize(30);
    label.setFillColor(sf::Color::White);
    // Center align label
    sf::FloatRect labelBounds = label.getLocalBounds();
    label.setOrigin(labelBounds.left + labelBounds.width / 2.0f,
        labelBounds.top + labelBounds.height / 2.0f);
    label.setPosition(WINDOW_WIDTH / 2.0f, 450);
    window.draw(label);

    // Back instruction
    sf::Text backText;
    backText.setFont(font);
    backText.setString("Press ESC to return to menu");
    backText.setCharacterSize(22);
    backText.setFillColor(sf::Color(180, 180, 180));
    backText.setPosition(WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT - 80);
    // Center align back text
    sf::FloatRect backBounds = backText.getLocalBounds();
    backText.setOrigin(backBounds.left + backBounds.width / 2.0f,
        backBounds.top + backBounds.height / 2.0f);
    backText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 80);
    window.draw(backText);
}

// How to Play Screen

void drawHowToPlay(sf::RenderWindow& window, sf::Font& font) {
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("HOW TO PLAY");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition(WINDOW_WIDTH / 2 - 160, 60);
    window.draw(title);

    // Instructions
    const char* instructions[] = {
        "OBJECTIVE:",
        "  Climb to the top of each stage!",
        "  Avoid enemies.",
        "",
        "CONTROLS:",
        "  A = Move Left",
        "  D = Move Right",
        "  W = Jump (break blocks from below)",
        "  ESC = Pause/Menu",
        "",
        "GAME ELEMENTS:",
        "  Popo (Blue) = You!",
        "  Topi (White Seal) = Enemy - Avoid!",
        "  X = Breakable Block (+10 points)",
        "",
        "STAGES:",
        "  8 stages with increasing difficulty",
        "  Each 2 stages = new background theme",
        "  Complete all 8 for BONUS STAGE!",
        "",
        "SCORING:",
        "  Break Block: +10 ",
        "  Stage Clear: +1000"
    };

    for (int i = 0; i < 23; i++) {
        sf::Text line;
        line.setFont(font);
        line.setString(instructions[i]);
        line.setCharacterSize(18);
        line.setFillColor(sf::Color::White);
        line.setPosition(150, 140 + i * 24);
        window.draw(line);
    }

    // Back
    sf::Text backText;
    backText.setFont(font);
    backText.setString("Press ESC to return");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::Yellow);
    backText.setPosition(WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT - 50);
    window.draw(backText);
}

// PAUSE MENU

void drawPauseMenu(sf::RenderWindow& window, sf::Font& font, int selectedOption) {
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("PAUSED");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::Yellow);
    title.setOutlineThickness(3);
    title.setOutlineColor(sf::Color(200, 200, 0));
    title.setPosition(WINDOW_WIDTH / 2 - 150, 180);
    window.draw(title);

    // Menu options
    const char* menuItems[3] = {
        "Resume",
        "Settings",
        "Quit to Menu"
    };

    for (int i = 0; i < 3; i++) {
        sf::Text menuText;
        menuText.setFont(font);
        menuText.setString(menuItems[i]);
        menuText.setCharacterSize(36);
        menuText.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        menuText.setPosition(WINDOW_WIDTH / 2 - 100, 320 + i * 70);
        window.draw(menuText);
    }
}

void handlePauseMenuInput(sf::Keyboard::Key key, int& selectedOption, int& gameState) {
    if (key == sf::Keyboard::Up) {
        selectedOption--;
        if (selectedOption < 0) selectedOption = 2;
    }
    else if (key == sf::Keyboard::Down) {
        selectedOption++;
        if (selectedOption > 2) selectedOption = 0;
    }
    else if (key == sf::Keyboard::Enter) {
        if (selectedOption == 0) { // Resume
            gameState = STATE_PLAYING;
        }
        else if (selectedOption == 1) { // Settings
            gameState = STATE_SETTINGS;
        }
        else if (selectedOption == 2) { // Quit to Menu
            gameState = STATE_MAIN_MENU;
        }
    }
    else if (key == sf::Keyboard::Escape) {
        gameState = STATE_PLAYING; // Quick resume
    }
}

// Game Over Screen

void drawGameOver(sf::RenderWindow& window, sf::Font& font) {
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
    window.draw(overlay);

    // Game Over text
    sf::Text title;
    title.setFont(font);
    title.setString("GAME OVER");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Red);
    title.setOutlineThickness(4);
    title.setOutlineColor(sf::Color(150, 0, 0));
    title.setPosition(WINDOW_WIDTH / 2 - 260, 150);
    window.draw(title);

    // Final score
    char finalScoreText[100];
    copyString(finalScoreText, "Final Score: ");
    char scoreNum[20];
    intToCharArray(score, scoreNum);
    concatString(finalScoreText, scoreNum);

    sf::Text scoreDisplay;
    scoreDisplay.setFont(font);
    scoreDisplay.setString(finalScoreText);
    scoreDisplay.setCharacterSize(40);
    scoreDisplay.setFillColor(sf::Color::White);
    scoreDisplay.setPosition(WINDOW_WIDTH / 2 - 200, 300);
    window.draw(scoreDisplay);

    // Stage reached
    char stageText[100];
    copyString(stageText, "Stage Reached: ");
    char stageNum[20];
    intToCharArray(currentStage, stageNum);
    concatString(stageText, stageNum);

    sf::Text stageDisplay;
    stageDisplay.setFont(font);
    stageDisplay.setString(stageText);
    stageDisplay.setCharacterSize(30);
    stageDisplay.setFillColor(sf::Color::Cyan);
    stageDisplay.setPosition(WINDOW_WIDTH / 2 - 180, 370);
    window.draw(stageDisplay);

    // High score
    char highScoreText[100];
    copyString(highScoreText, "High Score: ");
    char highScoreNum[20];
    intToCharArray(highScore, highScoreNum);
    concatString(highScoreText, highScoreNum);

    sf::Text highScoreDisplay;
    highScoreDisplay.setFont(font);
    highScoreDisplay.setString(highScoreText);
    highScoreDisplay.setCharacterSize(30);
    highScoreDisplay.setFillColor(sf::Color::Yellow);
    highScoreDisplay.setPosition(WINDOW_WIDTH / 2 - 150, 430);
    window.draw(highScoreDisplay);

    // Continue
    sf::Text continueText;
    continueText.setFont(font);
    continueText.setString("Press ESC to return to menu");
    continueText.setCharacterSize(24);
    continueText.setFillColor(sf::Color(200, 200, 200));
    continueText.setPosition(WINDOW_WIDTH / 2 - 200, 540);
    window.draw(continueText);
}