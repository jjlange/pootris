/**
 * Pootris
 * FontManager header
 *
 * @author jjlange
 */

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>

class FontManager {
public:
    static void loadFonts();

    static sf::Font tetrisFont;
    static sf::Font robotoFont;
    // Add more fonts if needed

private:
    FontManager(); // Private constructor to prevent instantiation
};

#endif // FONTMANAGER_H