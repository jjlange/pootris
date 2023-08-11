/**
 * Pootris
 * Configuration file
 *
 * @author jjlange
 */

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <string>

const std::string GAME_TITLE = "Pootris";

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 1000;
const int GRID_WIDTH = 10;        // Number of grid cells horizontally
const int GRID_HEIGHT = 20;       // Number of grid cells vertically

const float MOVE_INTERVAL = 0.2f; // Time interval for block movement (in seconds)

#endif // GAMECONFIG_H