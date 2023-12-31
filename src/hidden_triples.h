#pragma once

#include "sudoku.h"

int hidden_triples(SudokuBoard *p_board);

struct NumIndexStore2
{
    int Potential;
    int indexStore[3];
    int TempIndex;
};

void find_hidden_triples(Cell **p_cell, int *result);

void CompareArray2(int a[], int b[], int c[], int size); 


int combineArray2(int a[], int b[], int size); 

void get_candidates_plus2(struct NumIndexStore2 *ValueStore, int out[]);

int CountNonZero2(int array[],int size);

void GetFoundTrip2(Cell **p_cell);