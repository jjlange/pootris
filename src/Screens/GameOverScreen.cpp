/**
 * Pootris
 * GameOverScreen implementation
 *
 * @author jjlange
 */

#include "GameOverScreen.h"
#include "../GameConfig.h"

void GameOverScreen::render(sf::RenderWindow& window) {
    sf::Text text;
    text.setFont(FontManager::tetrisFont);
    text.setString("Game Over");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::White);
    text.setPosition(WINDOW_WIDTH / 2 - text.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 - text.getLocalBounds().height / 2);

    // Another text below
    sf::Text text2;
    text2.setFont(FontManager::robotoFont);
    text2.setString("Press Enter to play again");
    text2.setCharacterSize(28);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(WINDOW_WIDTH / 2 - text2.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 - text2.getLocalBounds().height / 2 + 100);

    window.clear();
    window.draw(text);
    window.draw(text2);
    window.display();
}

// Path: src/Screens/GameOverScreen.cpp