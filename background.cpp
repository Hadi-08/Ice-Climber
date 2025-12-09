#include "background.hpp"
#include "common.hpp"
#include <cstdlib>


// STAGE 1-2: MOUNTAIN BASE (Blue sky, brown mountains)

void createMountainBackground(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(WINDOW_WIDTH, WINDOW_HEIGHT * 2); // Taller for scrolling

    // Sky gradient
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = sf::Vector2f(0, 0);
    gradient[0].color = sf::Color(135, 206, 250); // Sky blue
    gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
    gradient[1].color = sf::Color(135, 206, 250);
    gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT * 2);
    gradient[2].color = sf::Color(70, 130, 180); // Steel blue
    gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT * 2);
    gradient[3].color = sf::Color(70, 130, 180);
    renderTex.draw(gradient);

    // Brown mountain peaks
    sf::ConvexShape mountain1;
    mountain1.setPointCount(3);
    mountain1.setPoint(0, sf::Vector2f(0, WINDOW_HEIGHT * 2));
    mountain1.setPoint(1, sf::Vector2f(300, WINDOW_HEIGHT + 200));
    mountain1.setPoint(2, sf::Vector2f(600, WINDOW_HEIGHT * 2));
    mountain1.setFillColor(sf::Color(139, 90, 43)); // brown
    renderTex.draw(mountain1);

    sf::ConvexShape mountain2;
    mountain2.setPointCount(3);
    mountain2.setPoint(0, sf::Vector2f(400, WINDOW_HEIGHT * 2));
    mountain2.setPoint(1, sf::Vector2f(700, WINDOW_HEIGHT + 100));
    mountain2.setPoint(2, sf::Vector2f(1000, WINDOW_HEIGHT * 2));
    mountain2.setFillColor(sf::Color(160, 100, 50));
    renderTex.draw(mountain2);

    // White snow caps
    sf::ConvexShape snow1;
    snow1.setPointCount(3);
    snow1.setPoint(0, sf::Vector2f(250, WINDOW_HEIGHT + 250));
    snow1.setPoint(1, sf::Vector2f(300, WINDOW_HEIGHT + 200));
    snow1.setPoint(2, sf::Vector2f(350, WINDOW_HEIGHT + 250));
    snow1.setFillColor(sf::Color::White);
    renderTex.draw(snow1);

    renderTex.display();
    texture.loadFromImage(renderTex.getTexture().copyToImage());
}

// STAGE 3-4: ICE CAVE (Dark blue, ice crystals)

void createIceCaveBackground(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(WINDOW_WIDTH, WINDOW_HEIGHT * 2);

    // Dark blue gradient
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = sf::Vector2f(0, 0);
    gradient[0].color = sf::Color(25, 25, 112); // Midnight blue
    gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
    gradient[1].color = sf::Color(25, 25, 112);
    gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT * 2);
    gradient[2].color = sf::Color(0, 0, 139); // Dark blue
    gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT * 2);
    gradient[3].color = sf::Color(0, 0, 139);
    renderTex.draw(gradient);

    // Ice crystals scattered around
    for (int i = 0; i < 30; i++) {
        sf::CircleShape crystal(5 + (i % 3) * 2);
        crystal.setPosition(rand() % WINDOW_WIDTH, rand() % (WINDOW_HEIGHT * 2));
        crystal.setFillColor(sf::Color(173, 216, 230, 100)); // Light blue transparent
        renderTex.draw(crystal);
    }

    // Icicles
    for (int i = 0; i < 15; i++) {
        sf::ConvexShape icicle;
        icicle.setPointCount(3);
        float x = i * 80.0f;
        icicle.setPoint(0, sf::Vector2f(x, 0));
        icicle.setPoint(1, sf::Vector2f(x + 15, 0));
        icicle.setPoint(2, sf::Vector2f(x + 7, 40 + (i % 3) * 20));
        icicle.setFillColor(sf::Color(200, 230, 255, 180));
        renderTex.draw(icicle);
    }

    renderTex.display();
    texture = renderTex.getTexture();
}

// STAGE 5-6: SNOW PEAK (White, snowy)

void createSnowPeakBackground(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(WINDOW_WIDTH, WINDOW_HEIGHT * 2);

    // Light sky gradient
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = sf::Vector2f(0, 0);
    gradient[0].color = sf::Color(176, 224, 230); // Powder blue
    gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
    gradient[1].color = sf::Color(176, 224, 230);
    gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT * 2);
    gradient[2].color = sf::Color(240, 248, 255); // Alice blue
    gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT * 2);
    gradient[3].color = sf::Color(240, 248, 255);
    renderTex.draw(gradient);

    // Snowy mountains (white)
    sf::ConvexShape mountain1;
    mountain1.setPointCount(3);
    mountain1.setPoint(0, sf::Vector2f(0, WINDOW_HEIGHT * 2));
    mountain1.setPoint(1, sf::Vector2f(400, WINDOW_HEIGHT));
    mountain1.setPoint(2, sf::Vector2f(800, WINDOW_HEIGHT * 2));
    mountain1.setFillColor(sf::Color(255, 250, 250)); // Snow
    renderTex.draw(mountain1);

    // Snowflakes
    for (int i = 0; i < 50; i++) {
        sf::CircleShape snowflake(3);
        snowflake.setPosition(rand() % WINDOW_WIDTH, rand() % (WINDOW_HEIGHT * 2));
        snowflake.setFillColor(sf::Color(255, 255, 255, 200));
        renderTex.draw(snowflake);
    }

    renderTex.display();
    texture = renderTex.getTexture();
}

// STAGE 7-8: GLACIER

void createGlacierBackground(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(WINDOW_WIDTH, WINDOW_HEIGHT * 2);

    // Aurora-like gradient (purple/cyan/green)
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = sf::Vector2f(0, 0);
    gradient[0].color = sf::Color(138, 43, 226); // Blue violet
    gradient[1].position = sf::Vector2f(WINDOW_WIDTH, 0);
    gradient[1].color = sf::Color(0, 255, 255); // Cyan
    gradient[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT * 2);
    gradient[2].color = sf::Color(0, 100, 100);
    gradient[3].position = sf::Vector2f(0, WINDOW_HEIGHT * 2);
    gradient[3].color = sf::Color(75, 0, 130);
    renderTex.draw(gradient);

    // Aurora waves
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape wave(sf::Vector2f(WINDOW_WIDTH, 80));
        wave.setPosition(0, i * 300);
        wave.setFillColor(sf::Color(0, 255, 200, 30));
        renderTex.draw(wave);
    }

    // Cyan ice formations
    for (int i = 0; i < 10; i++) {
        sf::RectangleShape ice(sf::Vector2f(40, 100 + (i % 3) * 50));
        ice.setPosition(i * 120, WINDOW_HEIGHT * 2 - 150);
        ice.setFillColor(sf::Color(0, 255, 255, 100));
        renderTex.draw(ice);
    }

    renderTex.display();
    texture = renderTex.getTexture();
}

// BONUS STAGE (Stars, rainbow)

void createBonusBackground(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(WINDOW_WIDTH, WINDOW_HEIGHT * 2);

    // Dark starry sky
    sf::RectangleShape sky(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT * 2));
    sky.setFillColor(sf::Color(10, 10, 40));
    renderTex.draw(sky);

    // Stars
    for (int i = 0; i < 100; i++) {
        sf::CircleShape star(2 + rand() % 3);
        star.setPosition(rand() % WINDOW_WIDTH, rand() % (WINDOW_HEIGHT * 2));
        star.setFillColor(sf::Color(255, 255, 200 + rand() % 56));
        renderTex.draw(star);
    }

    // Rainbow arc
    for (int i = 0; i < 7; i++) {
        sf::Color rainbowColors[7] = {
            sf::Color(255, 0, 0, 100),    // Red
            sf::Color(255, 127, 0, 100),  // Orange
            sf::Color(255, 255, 0, 100),  // Yellow
            sf::Color(0, 255, 0, 100),    // Green
            sf::Color(0, 0, 255, 100),    // Blue
            sf::Color(75, 0, 130, 100),   // Indigo
            sf::Color(148, 0, 211, 100)   // Violet
        };

        sf::CircleShape arc(300 - i * 20);
        arc.setPosition(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT);
        arc.setFillColor(sf::Color::Transparent);
        arc.setOutlineThickness(15);
        arc.setOutlineColor(rainbowColors[i]);
        renderTex.draw(arc);
    }

    renderTex.display();
    texture = renderTex.getTexture();
}