/**
 * Pootris
 * FontManager implementation
 *
 * @author jjlange
 */

#include <iostream>
#include "FontManager.h"

// Initialise static variables
sf::Font FontManager::tetrisFont;
sf::Font FontManager::robotoFont;

void FontManager::loadFonts() {
    if (!tetrisFont.loadFromFile("./assets/fonts/Tetris.ttf")) {
        // Handle font loading error
        std::cout << "Error loading Tetris font" << std::endl;
    }

    if (!robotoFont.loadFromFile("./assets/fonts/Roboto-Regular.ttf")) {
        // Handle font loading error
        std::cout << "Error loading Roboto font" << std::endl;
    }

    // Load other fonts..
}

// Path: src/Utils/FontManager.cpp