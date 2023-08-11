/**
 * Pootris
 * Definition of all Tetris blocks
 *
 * @author jjlange
 */

#include <vector>

#include "../Types/TetrisBlock.h"

const std::vector<TetrisBlock> TetrisBlocks = {
    {TetrisBlockType::I, {{0, 0, 0, 0},
                          {1, 1, 1, 1},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}}},

    {TetrisBlockType::J, {{1, 0, 0, 0},
                          {1, 1, 1, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}}},

    {TetrisBlockType::L, {{0, 0, 1, 0},
                          {1, 1, 1, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}}},

    {TetrisBlockType::O, {{1, 1, 0, 0},
                          {1, 1, 0, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}}},

    {TetrisBlockType::S, {{0, 1, 1, 0},
                          {1, 1, 0, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}}},

    {TetrisBlockType::T, {{0, 1, 0, 0},
                          {1, 1, 1, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}}},

    {TetrisBlockType::Z, {{1, 1, 0, 0},
                          {0, 1, 1, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}}}
};

// Path: src/Tetris/TetrisGame.cpp