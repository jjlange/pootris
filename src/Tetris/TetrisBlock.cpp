/**
 * Pootris
 * Implementation of TetrisBlock class methods
 *
 * @author jjlange
 */

#include "../Types/TetrisBlock.h"
#include "../GameConfig.h" // Include any other necessary headers

// Implement the clockwise rotation logic for the block cells
void TetrisBlock::rotateClockwise()
{
    if (type == TetrisBlockType::O)
    {
        // O block does not change on rotation, so return early
        return;
    }

    // Create a temporary copy of the cells array to store the rotated state
    int tempCells[4][4];

    // Perform the clockwise rotation on the cells array
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            tempCells[j][3 - i] = cells[i][j];
        }
    }

    // Copy the rotated state back to the original cells array
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cells[i][j] = tempCells[i][j];
        }
    }
}

// Method to check if the rotated block is allowed at the new position
bool TetrisBlock::isRotationAllowed(RotationState newRotation, int newX, int newY, const std::vector<std::vector<int>> &matrix)
{
    TetrisBlock rotatedBlock = *this;

    // Apply the rotation to the copied block
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            int newRow, newCol;
            // Rotate the block based on the new rotation state
            switch (newRotation)
            {
            case RotationState::UP:
                newRow = i;
                newCol = j;
                break;
            case RotationState::RIGHT:
                newRow = j;
                newCol = 3 - i;
                break;
            case RotationState::DOWN:
                newRow = 3 - i;
                newCol = 3 - j;
                break;
            case RotationState::LEFT:
                newRow = 3 - j;
                newCol = i;
                break;
            }

            rotatedBlock.cells[newRow][newCol] = cells[i][j];
        }
    }

    // Check if the rotated block is allowed at the new position
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (rotatedBlock.cells[i][j] == 1)
            {
                int row = newY + i;
                int col = newX + j;
                if (row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH || matrix[row][col] == 1)
                {
                    return false; // Rotation is not allowed
                }
            }
        }
    }

    return true; // Rotation is allowed
}