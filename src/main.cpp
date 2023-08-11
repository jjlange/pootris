/**
 * Pootris
 * Main entry point for the game
 *
 * @author jjlange
 */

// C++ Standard Library
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <chrono>

// SFML
#include <SFML/Graphics.hpp>

// Game Config
#include "GameConfig.h"

// Types
#include "Types/TetrisBlock.h"
#include "Types/GameState.h"
#include "Types/RotationState.h"

// Utils
#include "Utils/Rotations.h"

// Managers
#include "Managers/FontManager.h"

// Screens
#include "Screens/GameOverScreen.h"
#include "Screens/StartScreen.h"

using namespace std;

// Main entry point
int main()
{
    // Create game window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Titlebar | sf::Style::Close);

    // Current state of the matrix
    std::vector<std::vector<int>> matrix(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));

    // Variables to control block movement
    sf::Clock clock; // Timer for block movement
    float moveTimer = 0.0f;

    // Variables for block properties
    int blockIndex = 0;
    const TetrisBlock *currentBlock = nullptr;
    int x = 0;
    int y = 0;

    // Game Status
    GameState gameState = GameState::START;

    // Initialise the current rotation state
    RotationState currentRotation = RotationState::UP;

    bool hasChangedBlock = false;

    // Load all fonts
    FontManager::loadFonts();

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;

        // Handle events
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::KeyPressed)
            {
                if (gameState == GameState::START || gameState == GameState::GAME_OVER)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        // Reset the game
                        matrix = std::vector<std::vector<int>>(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));

                        // Reset the block properties
                        currentBlock = nullptr;

                        // Reset the game status
                        gameState = GameState::PLAYING;
                    }
                }

                if (currentBlock != nullptr)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {

                        // Move the block left
                        bool canMoveLeft = true;

                        for (int i = 0; i < 4; ++i)
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (currentBlock->cells[i][j] == 1)
                                {
                                    int nextColumn = x + j - 1;
                                    if (nextColumn < 0 || matrix[y + i][nextColumn] == 1)
                                    {
                                        canMoveLeft = false;
                                        break;
                                    }
                                }
                            }

                            if (!canMoveLeft)
                            {
                                break;
                            }
                        }

                        if (canMoveLeft)
                        {
                            x -= 1;
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        // Move the block right
                        bool canMoveRight = true;
                        for (int i = 0; i < 4; ++i)
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (currentBlock->cells[i][j] == 1)
                                {
                                    int nextColumn = x + j + 1;
                                    if (nextColumn >= GRID_WIDTH || matrix[y + i][nextColumn] == 1)
                                    {
                                        canMoveRight = false;
                                        break;
                                    }
                                }
                            }
                            if (!canMoveRight)
                            {
                                break;
                            }
                        }

                        if (canMoveRight)
                        {
                            x += 1;
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        // Rotate the block
                        TetrisBlock rotatedBlock = *currentBlock;
                        for (int i = 0; i < 4; ++i)
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                rotatedBlock.cells[i][j] = currentBlock->cells[3 - j][i];
                            }
                        }

                        bool canRotate = true;
                        for (int i = 0; i < 4; ++i)
                        {
                            if (x + i >= GRID_WIDTH)
                            {
                                canRotate = false;
                                break;
                            }

                            for (int j = 0; j < 4; ++j)
                            {
                                if (rotatedBlock.cells[i][j] == 1)
                                {
                                    if (matrix[y + i][x + j] == 1)
                                    {
                                        canRotate = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        // Move the block down
                        bool canMoveDown = true;
                        for (int i = 0; i < 4; ++i)
                        {
                            if (y + i + 1 >= GRID_HEIGHT)
                            {
                                canMoveDown = false;
                                break;
                            }

                            for (int j = 0; j < 4; ++j)
                            {
                                if (currentBlock->cells[i][j] == 1)
                                {
                                    if (matrix[y + i + 1][x + j] == 1)
                                    {
                                        canMoveDown = false;
                                        break;
                                    }
                                }
                            }
                        }

                        if (canMoveDown)
                        {
                            y += 1;
                        }
                    }

                    else if (event.key.code == sf::Keyboard::Z)
                    {
                        // Create a copy of the current block
                        TetrisBlock rotatedBlock = *currentBlock;

                        // Rotate the block clockwise
                        rotatedBlock.rotateClockwise();

                        // Check if the rotated block is allowed at the new position
                        if (rotatedBlock.isRotationAllowed(currentRotation, x, y, matrix))
                        {
                            // If rotation is allowed, update the current block and current rotation state
                            currentBlock = &rotatedBlock;
                            currentRotation = static_cast<RotationState>((static_cast<int>(currentRotation) + 1) % 4);
                        }
                    }

                    else if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift)
                    {
                        if (!hasChangedBlock)
                        {
                            // Replace the current block with a new block but with the same position
                            int oldX = x;
                            int oldY = y;
                            int oldBlockIndex = blockIndex;
                            blockIndex = rand() % TetrisBlocks.size();
                            currentBlock = &TetrisBlocks[blockIndex];
                            x = oldX;
                            y = oldY;
                        }
                    }
                }
            }
        }

        if (gameState == GameState::START)
        {
            StartScreen::render(window);
        }
        else if (gameState == GameState::GAME_OVER)
        {
            GameOverScreen::render(window);
        }
        else if (gameState == GameState::PLAYING)
        {

            // Update the move timer
            float deltaTime = clock.restart().asSeconds();
            moveTimer += deltaTime;

            // Check if it's time to move the block down
            if (moveTimer >= MOVE_INTERVAL)
            {
                moveTimer = 0.0f; // Reset the timer

                if (currentBlock == nullptr)
                {

                    // Spawn a new block at the top //
                    blockIndex = rand() % TetrisBlocks.size(); // Randomly select a block
                    currentBlock = &TetrisBlocks[blockIndex];  // Get the block from the vector
                    x = GRID_WIDTH / 2 - 2;                    // Center the block horizontally
                    y = 0;                                     // Place the block at the top

                    hasChangedBlock = false;

                    // Check if the new block can be placed at the top
                    for (int i = 0; i < 4; ++i)
                    { // Loop through the block's rows
                        for (int j = 0; j < 4; ++j)
                        { // Loop through the block's columns
                            if (currentBlock->cells[i][j] == 1)
                            { // Check if the cell is occupied
                                if (matrix[y + i][x + j] == 1)
                                { // Check if the cell is occupied in the matrix
                                    // Game over //
                                    gameState = GameState::GAME_OVER; // Change the game status
                                    std::cout << "[*] Status changed to GAME_OVER" << std::endl;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // Move the block down
                    bool canMoveDown = true; // Flag to check if the block can move down
                    for (int i = 0; i < 4; ++i)
                    { // Loop through the block's rows
                        for (int j = 0; j < 4; ++j)
                        { // Loop through the block's columns
                            if (currentBlock->cells[i][j] == 1)
                            {                            // Check if the cell is occupied
                                int nextRow = y + i + 1; // Get the next row
                                if (nextRow >= GRID_HEIGHT || matrix[nextRow][x + j] == 1)
                                {                        // Check if the next row is occupied in the matrix
                                    canMoveDown = false; // Set the flag to false
                                    break;
                                }
                            }
                        }
                    }

                    // If the block can't move down further, fix it in the matrix and remove currentBlock
                    if (!canMoveDown)
                    { // Check if the block can move down
                        for (int i = 0; i < 4; ++i)
                        { // Loop through the block's rows
                            for (int j = 0; j < 4; ++j)
                            { // Loop through the block's columns
                                if (currentBlock->cells[i][j] == 1)
                                {                             // Check if the cell is occupied
                                    matrix[y + i][x + j] = 1; // Fix the block in the matrix
                                }
                            }
                        }

                        currentBlock = nullptr; // Remove the current block
                    }
                    else
                    {
                        y += 1; // Move the block down
                    }
                }
            }

            // Clear the window
            window.clear();

            // Check if a whole line in the matrix is filled
            for (int i = 0; i < GRID_HEIGHT; ++i)
            {
                bool isLineFilled = true;
                for (int j = 0; j < GRID_WIDTH; ++j)
                {
                    if (matrix[i][j] == 0)
                    {
                        isLineFilled = false;
                        break;
                    }
                }

                if (isLineFilled)
                {
                    // Remove the filled line
                    std::cout << "[*] Removing line " << i << std::endl;
                    for (int k = i; k > 0; --k)
                    {
                        for (int j = 0; j < GRID_WIDTH; ++j)
                        {
                            matrix[k][j] = matrix[k - 1][j];
                        }
                    }
                }
            }

            // Draw the grid
            for (int i = 0; i < GRID_HEIGHT; ++i)
            {
                for (int j = 0; j < GRID_WIDTH; ++j)
                {
                    sf::RectangleShape cell(sf::Vector2f(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT));
                    cell.setPosition(j * WINDOW_WIDTH / GRID_WIDTH, i * WINDOW_HEIGHT / GRID_HEIGHT);
                    cell.setOutlineThickness(1);
                    cell.setOutlineColor(sf::Color::White);
                    cell.setFillColor(matrix[i][j] == 1 ? sf::Color::Red : sf::Color::Black);
                    window.draw(cell);
                }
            }

            // Draw the current block if available
            if (currentBlock != nullptr)
            {
                for (int i = 0; i < 4; ++i)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        if (currentBlock->cells[i][j] == 1)
                        {
                            sf::RectangleShape cell(sf::Vector2f(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT));
                            cell.setPosition((x + j) * WINDOW_WIDTH / GRID_WIDTH, (y + i) * WINDOW_HEIGHT / GRID_HEIGHT);
                            cell.setOutlineThickness(1);
                            cell.setOutlineColor(sf::Color::White);
                            cell.setFillColor(sf::Color::Red);
                            window.draw(cell);
                        }
                    }
                }
            }

            // Draw the window
            window.display();
        }
    }

    return 0;
}
