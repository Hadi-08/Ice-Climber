#include "sprites.hpp"

// POPO (Blue Ice Climber Character)

void createPopoSprite(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(32, 40);
    renderTex.clear(sf::Color::Transparent);

    // Blue parka (Ice Climber signature blue)
    sf::RectangleShape body(sf::Vector2f(22, 26));
    body.setPosition(5, 10);
    body.setFillColor(sf::Color(82, 163, 255)); // Ice Climber blue
    body.setOutlineThickness(1);
    body.setOutlineColor(sf::Color(41, 102, 204));
    renderTex.draw(body);

    // Hood/Head (tan skin)
    sf::CircleShape head(8);
    head.setPosition(8, 1);
    head.setFillColor(sf::Color(255, 206, 165)); // Skin tone
    renderTex.draw(head);

    // Hood fur trim (white)
    sf::RectangleShape hoodTrim(sf::Vector2f(20, 3));
    hoodTrim.setPosition(6, 9);
    hoodTrim.setFillColor(sf::Color::White);
    renderTex.draw(hoodTrim);

    // Eyes (black dots)
    sf::RectangleShape eye1(sf::Vector2f(2, 2));
    eye1.setPosition(12, 6);
    eye1.setFillColor(sf::Color::Black);
    renderTex.draw(eye1);

    sf::RectangleShape eye2(sf::Vector2f(2, 2));
    eye2.setPosition(18, 6);
    eye2.setFillColor(sf::Color::Black);
    renderTex.draw(eye2);

    // Arms (blue)
    sf::RectangleShape arm1(sf::Vector2f(5, 16));
    arm1.setPosition(2, 14);
    arm1.setFillColor(sf::Color(82, 163, 255));
    renderTex.draw(arm1);

    sf::RectangleShape arm2(sf::Vector2f(5, 16));
    arm2.setPosition(25, 14);
    arm2.setFillColor(sf::Color(82, 163, 255));
    renderTex.draw(arm2);

    // Legs/feet (darker blue)
    sf::RectangleShape leg1(sf::Vector2f(8, 6));
    leg1.setPosition(8, 34);
    leg1.setFillColor(sf::Color(41, 102, 204));
    renderTex.draw(leg1);

    sf::RectangleShape leg2(sf::Vector2f(8, 6));
    leg2.setPosition(16, 34);
    leg2.setFillColor(sf::Color(41, 102, 204));
    renderTex.draw(leg2);

    renderTex.display();
    texture = renderTex.getTexture();
}
// TOPI (White Seal Enemy)
void createTopiSprite(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(32, 32);
    renderTex.clear(sf::Color::Transparent);

    // White body (seal shape)
    sf::CircleShape body(14);
    body.setPosition(2, 4);
    body.setFillColor(sf::Color(240, 240, 255)); // Off-white
    body.setOutlineThickness(1);
    body.setOutlineColor(sf::Color(200, 200, 220));
    renderTex.draw(body);

    // Gray spots
    sf::CircleShape spot1(4);
    spot1.setPosition(8, 10);
    spot1.setFillColor(sf::Color(180, 180, 200));
    renderTex.draw(spot1);

    sf::CircleShape spot2(5);
    spot2.setPosition(18, 8);
    spot2.setFillColor(sf::Color(180, 180, 200));
    renderTex.draw(spot2);

    sf::CircleShape spot3(3);
    spot3.setPosition(12, 20);
    spot3.setFillColor(sf::Color(180, 180, 200));
    renderTex.draw(spot3);

    // Black eyes
    sf::CircleShape eye1(3);
    eye1.setPosition(10, 12);
    eye1.setFillColor(sf::Color::Black);
    renderTex.draw(eye1);

    sf::CircleShape eye2(3);
    eye2.setPosition(19, 12);
    eye2.setFillColor(sf::Color::Black);
    renderTex.draw(eye2);

    // Pink nose
    sf::CircleShape nose(2);
    nose.setPosition(15, 20);
    nose.setFillColor(sf::Color(255, 150, 180));
    renderTex.draw(nose);

    // Whiskers
    sf::RectangleShape whisker1(sf::Vector2f(6, 1));
    whisker1.setPosition(6, 21);
    whisker1.setFillColor(sf::Color(100, 100, 120));
    renderTex.draw(whisker1);

    sf::RectangleShape whisker2(sf::Vector2f(6, 1));
    whisker2.setPosition(20, 21);
    whisker2.setFillColor(sf::Color(100, 100, 120));
    renderTex.draw(whisker2);

    renderTex.display();
    texture = renderTex.getTexture();
}
// VEGETABLES (Collectibles)

void createEggplantSprite(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(24, 24);
    renderTex.clear(sf::Color::Black);

    // Purple eggplant body
    sf::CircleShape body(10);
    body.setPosition(2, 6);
    body.setFillColor(sf::Color(138, 43, 226)); // Purple
    body.setOutlineThickness(1);
    body.setOutlineColor(sf::Color(98, 30, 160));
    renderTex.draw(body);

    // Green stem
    sf::RectangleShape stem(sf::Vector2f(6, 8));
    stem.setPosition(9, 0);
    stem.setFillColor(sf::Color(34, 139, 34));
    renderTex.draw(stem);

    // Leaf
    sf::CircleShape leaf(4);
    leaf.setPosition(8, 1);
    leaf.setFillColor(sf::Color(50, 205, 50));
    renderTex.draw(leaf);

    // Highlight (shine)
    sf::CircleShape shine(3);
    shine.setPosition(6, 10);
    shine.setFillColor(sf::Color(180, 100, 255, 150));
    renderTex.draw(shine);

    renderTex.display();
    texture = renderTex.getTexture();
}

void createCarrotSprite(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(24, 24);
    renderTex.clear(sf::Color::Transparent);

    // Orange carrot body
    sf::ConvexShape body;
    body.setPointCount(3);
    body.setPoint(0, sf::Vector2f(12, 22));
    body.setPoint(1, sf::Vector2f(5, 8));
    body.setPoint(2, sf::Vector2f(19, 8));
    body.setFillColor(sf::Color(255, 140, 0));
    body.setOutlineThickness(1);
    body.setOutlineColor(sf::Color(200, 100, 0));
    renderTex.draw(body);

    // Green leaves
    sf::RectangleShape leaf1(sf::Vector2f(3, 8));
    leaf1.setPosition(8, 2);
    leaf1.setFillColor(sf::Color(34, 139, 34));
    renderTex.draw(leaf1);

    sf::RectangleShape leaf2(sf::Vector2f(3, 8));
    leaf2.setPosition(13, 2);
    leaf2.setFillColor(sf::Color(34, 139, 34));
    renderTex.draw(leaf2);

    renderTex.display();
    texture = renderTex.getTexture();
}

void createCabbageSprite(sf::Texture& texture) {
    sf::RenderTexture renderTex;
    renderTex.create(24, 24);
    renderTex.clear(sf::Color::Transparent);

    // Green cabbage
    sf::CircleShape body(10);
    body.setPosition(2, 4);
    body.setFillColor(sf::Color(144, 238, 144)); // Light green
    body.setOutlineThickness(1);
    body.setOutlineColor(sf::Color(34, 139, 34));
    renderTex.draw(body);

    // Texture lines
    sf::RectangleShape line1(sf::Vector2f(16, 2));
    line1.setPosition(4, 10);
    line1.setFillColor(sf::Color(34, 139, 34, 100));
    renderTex.draw(line1);

    sf::RectangleShape line2(sf::Vector2f(16, 2));
    line2.setPosition(4, 16);
    line2.setFillColor(sf::Color(34, 139, 34, 100));
    renderTex.draw(line2);

    renderTex.display();
    texture = renderTex.getTexture();
}