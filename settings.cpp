#include "settings.hpp"
#include "string_utils.hpp"

// Global settings variables
float musicVolume = 50.0f;
float sfxVolume = 70.0f;
int difficulty = DIFFICULTY_NORMAL;

// Draw settings page
void drawSettings(sf::RenderWindow& window, sf::Font& font, int selectedOption) {
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("SETTINGS");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition(WINDOW_WIDTH / 2 - 150, 100);
    window.draw(title);

    // Music Volume
    char musicText[100];
    copyString(musicText, "Music Volume: ");
    char volNum[10];
    intToCharArray((int)musicVolume, volNum);
    concatString(musicText, volNum);
    concatString(musicText, "%");

    sf::Text musicDisplay;
    musicDisplay.setFont(font);
    musicDisplay.setString(musicText);
    musicDisplay.setCharacterSize(32);
    musicDisplay.setFillColor(selectedOption == 0 ? sf::Color::Yellow : sf::Color::White);
    musicDisplay.setPosition(300, 250);
    window.draw(musicDisplay);

    // SFX Volume
    char sfxText[100];
    copyString(sfxText, "SFX Volume: ");
    char sfxNum[10];
    intToCharArray((int)sfxVolume, sfxNum);
    concatString(sfxText, sfxNum);
    concatString(sfxText, "%");

    sf::Text sfxDisplay;
    sfxDisplay.setFont(font);
    sfxDisplay.setString(sfxText);
    sfxDisplay.setCharacterSize(32);
    sfxDisplay.setFillColor(selectedOption == 1 ? sf::Color::Yellow : sf::Color::White);
    sfxDisplay.setPosition(300, 320);
    window.draw(sfxDisplay);

    // Difficulty
    const char* diffNames[] = { "Easy", "Normal", "Hard" };
    char diffText[100];
    copyString(diffText, "Difficulty: ");
    concatString(diffText, diffNames[difficulty]);

    sf::Text diffDisplay;
    diffDisplay.setFont(font);
    diffDisplay.setString(diffText);
    diffDisplay.setCharacterSize(32);
    diffDisplay.setFillColor(selectedOption == 2 ? sf::Color::Yellow : sf::Color::White);
    diffDisplay.setPosition(300, 390);
    window.draw(diffDisplay);

    // Back
    sf::Text backText;
    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(32);
    backText.setFillColor(selectedOption == 3 ? sf::Color::Yellow : sf::Color::White);
    backText.setPosition(300, 500);
    window.draw(backText);

    // Instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Use LEFT/RIGHT to adjust | UP/DOWN to navigate | ENTER to confirm");
    instructions.setCharacterSize(18);
    instructions.setFillColor(sf::Color(200, 200, 200));
    instructions.setPosition(200, WINDOW_HEIGHT - 80);
    window.draw(instructions);
}

// Handle settings input
void handleSettingsInput(sf::Keyboard::Key key, int& selectedOption, int& gameState,
    sf::Music& musc) {
    if (key == sf::Keyboard::Up) {
        selectedOption--;
        if (selectedOption < 0) selectedOption = 3;
    }
    else if (key == sf::Keyboard::Down) {
        selectedOption++;
        if (selectedOption > 3) selectedOption = 0;
    }
    else if (key == sf::Keyboard::Left) {
        if (selectedOption == 0 && musicVolume > 0) {
            musicVolume -= 10;
            if (musicVolume < 0) musicVolume = 0;
            musc.setVolume(musicVolume);
        }
        else if (selectedOption == 1 && sfxVolume > 0) {
            sfxVolume -= 10;
            if (sfxVolume < 0) sfxVolume = 0;
        }
        else if (selectedOption == 2) {
            difficulty--;
            if (difficulty < DIFFICULTY_EASY) difficulty = DIFFICULTY_HARD;
        }
    }
    else if (key == sf::Keyboard::Right) {
        if (selectedOption == 0 && musicVolume < 100) {
            musicVolume += 10;
            if (musicVolume > 100) musicVolume = 100;
            musc.setVolume(musicVolume);
        }
        else if (selectedOption == 1 && sfxVolume < 100) {
            sfxVolume += 10;
            if (sfxVolume > 100) sfxVolume = 100;
        }
        else if (selectedOption == 2) {
            difficulty++;
            if (difficulty > DIFFICULTY_HARD) difficulty = DIFFICULTY_EASY;
        }
    }
    else if (key == sf::Keyboard::Enter || key == sf::Keyboard::Escape) {
        if (selectedOption == 3 || key == sf::Keyboard::Escape) {
            gameState = STATE_MAIN_MENU;
        }
    }
}