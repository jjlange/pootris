/**
 * Pootris
 * Implementation of rotation functions
 *
 * @author jjlange
 */

#include "Rotations.h"
#include "../Types/RotationState.h"
#include "../GameConfig.h" // Include any other necessary headers

bool isRotationAllowed(const TetrisBlock& block, RotationState newRotation, int newX, int newY, const std::vector<std::vector<int>>& matrix) {
    TetrisBlock rotatedBlock = block;

    // Apply the rotation to the copied block
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int newRow, newCol;
            // Rotate the block based on the new rotation state
            switch (newRotation) {
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

            rotatedBlock.cells[newRow][newCol] = block.cells[i][j];
        }
    }

    // Check if the rotated block is allowed at the new position
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (rotatedBlock.cells[i][j] == 1) {
                int row = newY + i;
                int col = newX + j;
                if (row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH || matrix[row][col] == 1) {
                    return false; // Rotation is not allowed
                }
            }
        }
    }

    return true; // Rotation is allowed
}
