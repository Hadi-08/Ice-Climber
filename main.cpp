#include "common.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "string_utils.hpp"
#include "sprites.hpp"
#include "background.hpp"
#include "camera.hpp"
#include "settings.hpp" 
#include "stages.hpp"
#include "game_logic.hpp"
#include "graphics.hpp"
#include "menu.hpp"


using namespace std;

int main() {

    cout << "\n========================================" << endl;
    cout << "          THE ICY ASCENT         " << endl;
    cout << "   With Camera, Stages, Settings" << endl;
    cout << "========================================\n" << endl;

    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Icy Ascent");
    window.setFramerateLimit(120);

    sf::Music musc;
    musc.openFromFile("C:/Users/Lenovo/source/repos/IceClimber/BG.mp3");
    musc.play();
    musc.setLoop(true);

    sf::View og = window.getView();
    // Load resources
    sf::Texture playerTex, enemyTex, eggplantTex, carrotTex, cabbageTex, bgTex;
    sf::Font font;
    sf::SoundBuffer jumpBuf, breakBuf, hitBuf, collectBuf;
    sf::Sound jumpSound, breakSound, hitSound, collectSound;

    // Load all resources
    if (!loadResources(playerTex, enemyTex, eggplantTex, carrotTex, cabbageTex,
        bgTex, font, jumpBuf, breakBuf, hitBuf, collectBuf)) {
        cout << "Error loading resources!" << endl;
        return -1;
    }

    // Set up sounds
    jumpSound.setBuffer(jumpBuf);
    breakSound.setBuffer(breakBuf);
    hitSound.setBuffer(hitBuf);
    collectSound.setBuffer(collectBuf);
    musc.play();
    musc.setLoop(true);
    // Load high score
    loadHighScore();

    // Game state
    int gameState = STATE_MAIN_MENU;
    int menuSelection = 0;
    int pauseSelection = 0;
    int settingsSelection = 0;

    // Game timing
    sf::Clock gameClock;
    float gameSpeed = 0.09f; // Matches original Sleep(90)

    // Track previous values for sound triggers
    int prevLives = lives;
    int prevScore = score;
    bool prevJumping = false;

    sf::View view(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));

    cout << "\n=== GAME READY ===" << endl;
    cout << "Controls:" << endl;
    cout << "  Menu: UP/DOWN/ENTER" << endl;
    cout << "  Game: A/D=Move, W=Jump, ESC=Menu\n" << endl;

    // Main game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                // Keep the same view size as the window
                view.setSize(event.size.width, event.size.height);
                view.setCenter(event.size.width / 2.f, event.size.height / 2.f);
                window.setView(view);
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (gameState == STATE_MAIN_MENU) {
                    handleMainMenuInput(event.key.code, menuSelection, gameState);
                    if (menuSelection == 4 && event.key.code == sf::Keyboard::Enter) {
                        window.close(); // Exit option
                    }
                }
                else if (gameState == STATE_SETTINGS) {
                    handleSettingsInput(event.key.code, settingsSelection, gameState, musc);
                }
                else if (gameState == STATE_PAUSE) {
                    handlePauseMenuInput(event.key.code, pauseSelection, gameState);
                }
                else if (gameState == STATE_HIGH_SCORE || gameState == STATE_HOW_TO_PLAY) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        gameState = STATE_MAIN_MENU;
                        menuSelection = 0;
                    }
                }
                else if (gameState == STATE_GAME_OVER) {
                    view = og;
                    if (event.key.code == sf::Keyboard::Escape) {
                        gameState = STATE_MAIN_MENU;
                        menuSelection = 0;
                    }
                }
                else if (gameState == STATE_PLAYING) {
                    view = og;
                    if (event.key.code == sf::Keyboard::Escape) {
                        gameState = STATE_PAUSE;
                        pauseSelection = 0;
                    }
                }
                else if (gameState == STATE_STAGE_COMPLETE) {
                    view = og;
                    if (event.key.code == sf::Keyboard::Enter) {
                        // Add stage complete bonus
                        score += STAGE_COMPLETE_POINTS;

                        if (score > highScore) {
                            highScore = score;
                            saveHighScore();
                        }

                        // Advance to next stage
                        advanceStage();
                        loadStageBackground(bgTex, currentStage);

                        // Reset game for new stage
                        initializeGame();
                        resetCamera();

                        gameState = STATE_PLAYING;
                    }
                }
            }
        }

        // Update game logic
        if (gameState == STATE_PLAYING && !gameOver) {
            view.setCenter(player.getPosition());
            if (gameClock.getElapsedTime().asSeconds() >= gameSpeed) {
                // Store previous values
                prevLives = lives;
                prevScore = score;
                prevJumping = isJumping;

                // Update Game
                updateGame();

                // Update camera to follow player
                updateCamera(playerY * TILE_SIZE);

                // Play sounds based on changes
                if (isJumping && !prevJumping) {
                    jumpSound.setVolume(sfxVolume);
                    jumpSound.play();
                }
                if (score > prevScore) {
                    int scoreDiff = score - prevScore;
                    if (scoreDiff == BREAK_BLOCK_POINTS) {
                        breakSound.setVolume(sfxVolume);
                        breakSound.play();
                    }
                    else if (scoreDiff == COLLECTIBLE_POINTS) {
                        collectSound.setVolume(sfxVolume);
                        collectSound.play();
                    }
                }
                if (lives < prevLives) {
                    hitSound.setVolume(sfxVolume);
                    hitSound.play();
                }

                // Check game over
                if (gameOver) {
                    gameState = STATE_GAME_OVER;
                }

                // Check stage complete (reached top)
                if (playerY < 25) {
                    gameState = STATE_STAGE_COMPLETE;
                }

                gameClock.restart();
            }
        }

        // Render
        window.clear(sf::Color(40, 60, 120));

        if (gameState == STATE_MAIN_MENU) {
            view = og;
            // Drawn simple gradient background for menu
            sf::VertexArray gradient(sf::Quads, 4);
            gradient[0].position = sf::Vector2f(0, 0);
            gradient[0].color = sf::Color(20, 40, 80);
            gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
            gradient[1].color = sf::Color(20, 40, 80);
            gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
            gradient[2].color = sf::Color(50, 80, 140);
            gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT);
            gradient[3].color = sf::Color(50, 80, 140);
            window.draw(gradient);

            drawMainMenu(window, font, menuSelection);
        }
        else if (gameState == STATE_SETTINGS) {
            // Simple gradient for settings
            sf::VertexArray gradient(sf::Quads, 4);
            gradient[0].position = sf::Vector2f(0, 0);
            gradient[0].color = sf::Color(20, 40, 80);
            gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
            gradient[1].color = sf::Color(20, 40, 80);
            gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
            gradient[2].color = sf::Color(50, 80, 140);
            gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT);
            gradient[3].color = sf::Color(50, 80, 140);
            window.draw(gradient);

            drawSettings(window, font, settingsSelection);
        }
        else if (gameState == STATE_HIGH_SCORE) {
            // Simple gradient for high score
            sf::VertexArray gradient(sf::Quads, 4);
            gradient[0].position = sf::Vector2f(0, 0);
            gradient[0].color = sf::Color(20, 20, 40);
            gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
            gradient[1].color = sf::Color(20, 20, 40);
            gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
            gradient[2].color = sf::Color(60, 40, 20);
            gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT);
            gradient[3].color = sf::Color(60, 40, 20);
            window.draw(gradient);

            drawHighScore(window, font);
        }
        else if (gameState == STATE_HOW_TO_PLAY) {
            // Simple gradient for how to play
            sf::VertexArray gradient(sf::Quads, 4);
            gradient[0].position = sf::Vector2f(0, 0);
            gradient[0].color = sf::Color(10, 30, 50);
            gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
            gradient[1].color = sf::Color(10, 30, 50);
            gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
            gradient[2].color = sf::Color(30, 60, 90);
            gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT);
            gradient[3].color = sf::Color(30, 60, 90);
            window.draw(gradient);

            drawHowToPlay(window, font);
        }
        else if (gameState == STATE_PLAYING) {
            renderGame(window, bgTex, playerTex, enemyTex, eggplantTex, font);
        }
        else if (gameState == STATE_PAUSE) {
            view = og;
            // Draw game in background
            renderGame(window, bgTex, playerTex, enemyTex, eggplantTex, font);
            // Draw pause menu overlay
            drawPauseMenu(window, font, pauseSelection);
        }
        else if (gameState == STATE_GAME_OVER) {
            view = og;
            // Draw game in background
            renderGame(window, bgTex, playerTex, enemyTex, eggplantTex, font);
            // Draw game over overlay
            drawGameOver(window, font);
        }
        else if (gameState == STATE_STAGE_COMPLETE) {
            // Draw game in background
            renderGame(window, bgTex, playerTex, enemyTex, eggplantTex, font);
            // Draw stage complete overlay
            drawStageComplete(window, font);
        }
        if (STATE_GAME_OVER == gameState || STATE_STAGE_COMPLETE == gameState) {
            view = og;
        }
        window.setView(view);
        window.display();
    }

    cout << "\n=== GAME CLOSED ===" << endl;
    cout << "Final Score: " << score << endl;
    cout << "Stage Reached: " << currentStage << endl;

    return 0;
}