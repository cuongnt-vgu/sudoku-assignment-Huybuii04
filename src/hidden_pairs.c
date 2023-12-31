#include "hidden_pairs.h"
#include<stdlib.h>
#include<stdio.h>
int hidden_pairs(SudokuBoard* p_board)
{
    for (int i = 0; i < 9; i++) //loop in row
    {
        GetFound(p_board->p_rows[i]);
    }
    for (int i = 0; i < 9; i++) //loop in column
    {
        GetFound(p_board->p_cols[i]);
    }
    for (int i = 0; i < 9; i++) //loop in boxes
    {
        GetFound(p_board->p_boxes[i]);
    }

    int result = 0;

    for (int i = 0; i < 9; i++) //loop in row
    {
        //printf("currently in row %d\n", i);
        find_hidden_pairs(p_board->p_rows[i], &result);
    }
    for (int i = 0; i < 9; i++) //loop in column
    {
        //printf("currently in column %d\n", i);
        find_hidden_pairs(p_board->p_cols[i], &result);
    }
    for (int i = 0; i < 9; i++) //loop in boxes
    {
        //printf("currently in box %d\n", i);
        find_hidden_pairs(p_board->p_boxes[i], &result);
    }

    return result;
}
void find_hidden_pairs(Cell** p_cell, int* result)
{
    struct NumIndexStore* ValueStore[9];
    for (int i = 0; i < 9; i++)
    {
        ValueStore[i] = malloc(sizeof(struct NumIndexStore));
        ValueStore[i]->potential = 1;
        ValueStore[i]->tempIndex = 0;
    }



    for (int i = 0; i < 9; i++) //loop through each cell
    {
        for (int j = 0; j < 9; j++) //loop through each candidate in cell
        {
            if (p_cell[i]->candidates[j] == 1)
            {
                if (ValueStore[j]->potential == 0)
                {
                    continue;
                }
                if (ValueStore[j]->tempIndex == 2)
                {
                    ValueStore[j]->potential = 0;
                }
                else
                {

                    //printf("currently in cell %d\n",i);
                    ValueStore[j]->IndexStore[ValueStore[j]->tempIndex] = i;
                    //printf("ValueStore[%d]->IndexStore[ValueStore[%d]->tempIndex]=%d\n",j,j,i);
                    ValueStore[j]->tempIndex = ValueStore[j]->tempIndex + 1;
                }
            }
        }

    }

    for (int i = 0; i < 9; i++)
    {
        if (ValueStore[i]->tempIndex != 2)
            ValueStore[i]->potential = 0;
    }
    //print check
    /*
    for (int i=0;i<9;i++)
    {
        if (ValueStore[i]->potential==1)
        {
            printf("\n");
            printf("Value %d appear twice at index %d and %d",i+1,ValueStore[i]->IndexStore[0],ValueStore[i]->IndexStore[1]);
        }
    }
    */
    for (int i = 0; i < 8; i++)
    {
        if (ValueStore[i]->potential == 1)
        {
            for (int j = i + 1; j < 9; j++)
            {
                if (ValueStore[j]->potential == 1)
                {
                    if (ValueStore[i]->IndexStore[0] == ValueStore[j]->IndexStore[0] && ValueStore[i]->IndexStore[1] == ValueStore[j]->IndexStore[1])
                    {

                        if (p_cell[ValueStore[i]->IndexStore[0]]->num_candidates > 2 || p_cell[ValueStore[i]->IndexStore[1]]->num_candidates > 2)
                        {
                            //printf("\n Hidden Pair value %d %d appears at index %d and %d \n", i + 1, j + 1, ValueStore[i]->IndexStore[0], ValueStore[i]->IndexStore[1]);
                            if (p_cell[ValueStore[i]->IndexStore[0]]->Found != 1 || p_cell[ValueStore[i]->IndexStore[1]]->Found != 1)
                            {
                                p_cell[ValueStore[i]->IndexStore[0]]->Found = 1;
                                p_cell[ValueStore[i]->IndexStore[1]]->Found = 1;
                                *result = (*result) + 1;
                            }
                            for (int t = 0; t < 9; t++)
                            {
                                if (t == ValueStore[i]->IndexStore[0] || t == ValueStore[i]->IndexStore[1])
                                {

                                    for (int k = 0; k < 9; k++)
                                    {
                                        if (k == i || k == j)
                                        {
                                            continue;
                                        }
                                        unset_candidate(p_cell[t], k + 1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        free(ValueStore[i]);
    }

}

void GetFound(Cell** p_cell)
{
    for (int i = 0; i < 9; i++)
    {
        p_cell[i]->Found = 0;
    }
}