#pragma once

#include "sudoku.h"

int naked_pairs(SudokuBoard *p_board);

struct Numstore
{
    int PairValueArray[2];
    int groupable;
    

};

void find_naked_pairs_value(Cell **p_cells, int *result);

void GetFounds(Cell **p_cell);