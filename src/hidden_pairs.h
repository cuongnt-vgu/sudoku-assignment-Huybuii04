#pragma once

#include "sudoku.h"

struct NumIndexStore
{
    int potential;
    int IndexStore[2];
    int tempIndex;
};

int hidden_pairs(SudokuBoard *p_board);

void find_hidden_pairs(Cell **p_cell, int *result);

void GetFound(Cell **p_cell);