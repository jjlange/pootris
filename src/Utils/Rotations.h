/**
 * Pootris
 * Header for Rotations
 *
 * @author jjlange
 */

#pragma once

#ifndef ROTATIONS_H
#define ROTATIONS_H

#include "../Types/TetrisBlock.h" // Include the necessary header for TetrisBlock
#include "../Types/RotationState.h" // Include the necessary header for RotationState
#include <vector>        // Include the necessary header for std::vector

bool isRotationAllowed(const TetrisBlock& block, RotationState newRotation, int newX, int newY, const std::vector<std::vector<int>>& matrix);

#endif // ROTATIONS_H