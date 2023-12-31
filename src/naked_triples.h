#pragma once

#include "sudoku.h"

int naked_triples(SudokuBoard *p_board);

void find_naked_triple_value(Cell **p_cells, int *result);


void CompareArray(int a[], int b[], int c[], int size); 


int combineArray(int a[], int b[], int size); 

void get_candidates_plus(Cell *p_cells, int out[]);

int CountNonZero(int array[],int size);

void GetFoundTrip(Cell **p_cell);