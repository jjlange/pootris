/**
 * Pootris
 * Header file for TetrisBlock struct
 *
 * @author jjlange
 */

#ifndef TETRIS_BLOCKS_H
#define TETRIS_BLOCKS_H

#include <vector>
#include <initializer_list>
#include "../Types/RotationState.h"

enum class TetrisBlockType {
    I, J, L, O, S, T, Z
};

struct TetrisBlock {
    int cells[4][4] = {0};
    TetrisBlockType type;

    TetrisBlock(TetrisBlockType type, std::initializer_list<std::initializer_list<int>> config) : type(type) {
        int i = 0;
        for (const auto& row : config) {
            int j = 0;
            for (const auto& cell : row) {
                cells[i][j] = cell;
                ++j;
            }
            ++i;
        }
    }

    // Method to rotate the block clockwise
    void rotateClockwise();

    // Method to check if the rotated block is allowed at the new position
    bool isRotationAllowed(RotationState newRotation, int newX, int newY, const std::vector<std::vector<int>>& matrix);
};

// Declare the vector as an extern variable
extern const std::vector<TetrisBlock> TetrisBlocks;

#endif // TETRIS_BLOCKS_H

// Path: src/Types/TetrisBlock.h