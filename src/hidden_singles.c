#include "hidden_singles.h"
#include<stdlib.h>
#include<stdio.h>
int hidden_singles(SudokuBoard *p_board)
{
    // Loop in rows
    int res = 0;
    Cell **array_total = malloc(40 * sizeof(Cell *));
    int array_index = 0;  // Index for array_total

    for (int i = 0; i < 9; i++)
    {
        //printf("currently in row %d\n", i);
        int *array_int = calloc(9, sizeof(int));
        int num_array = find_hidden_single_values(p_board->p_rows[i], array_int);

        for (int x = 0; x < 9; x++)
        {
            if (array_int[x] != 0)
            {
                //printf("found array_int[%d] in row %d has value %d \n",x,i,array_int[x]);
                Cell *hidden_single_cell = malloc(sizeof(Cell));
                hidden_single_cell->row_index = i;
                hidden_single_cell->col_index = x;
                hidden_single_cell->val = array_int[x];
                array_total[array_index++] = hidden_single_cell;
            }
        }

        res += num_array;

        free(array_int);
    }

    // Loop in columns
    for (int i = 0; i < 9; i++)
    {
        //printf("currently in column %d\n", i);
        int *array_int = calloc(9, sizeof(int));
        int num_array = find_hidden_single_values(p_board->p_cols[i], array_int);

        for (int x = 0; x < 9; x++)
        {
            if (array_int[x] != 0)
            {
                //printf("found array_int[%d] in row %d has value %d \n",x,i,array_int[x]);
                Cell *hidden_single_cell = malloc(sizeof(Cell));
                hidden_single_cell->row_index = x;
                hidden_single_cell->col_index = i;
                hidden_single_cell->val = array_int[x];
                array_total[array_index++] = hidden_single_cell;
            }
        }

        res += num_array;

        free(array_int);
    }

    // Loop in boxes
    for (int i = 0; i < 9; i++)
    {
        //printf("currently in box %d\n", i);
        int *array_int = calloc(9, sizeof(int));
        //printf("currently in box %d\n", i);
        int num_array = find_hidden_single_values(p_board->p_boxes[i], array_int);

        for (int x = 0; x < 9; x++)
        {
            if (array_int[x] != 0)
            {
                //printf("found array_int[%d] in row %d has value %d \n",x,i,array_int[x]);
                Cell *hidden_single_cell = malloc(sizeof(Cell));
                hidden_single_cell->row_index = 3 * (i / 3) + x / 3;
                hidden_single_cell->col_index = 3 * (i % 3) + x % 3;
                hidden_single_cell->val = array_int[x];
                array_total[array_index++] = hidden_single_cell;
            }
        }

        res += num_array;

        free(array_int);
    }
    int num_detects;
    Implement_hidden_single(p_board, res, array_total, &num_detects);
    //printf("num_detects = %d\n", num_detects);

    // Free array_int only after all loops are done
    for (int i = 0; i < array_index; i++)
    {
        free(array_total[i]);
    }
    free(array_total);

    return num_detects;
}

int numberofuniquefilledcells(int *arr1, int *arr2, int NumsofHiddenSingle) {
    int count=0, flag;
    for (int i=0; i<NumsofHiddenSingle; i++) {
        flag = 0;
        for (int j=0; j<i; j++) {
            if (arr1[i] == arr1[j] && arr2[i] == arr2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) count++;
    }
    return count;
}

void Implement_hidden_single(SudokuBoard *p_board,int NumsofHiddenSingle,Cell **array_total, int *changer)
{
    int *rowposition = malloc(NumsofHiddenSingle * sizeof(int));
    int *colposition = malloc(NumsofHiddenSingle * sizeof(int));
    //int rowposition[NumsofHiddenSingle], colposition[NumsofHiddenSingle];
    for (int i=0;i<NumsofHiddenSingle;i++)
    {
        
        int tempRowIndex=array_total[i]->row_index;
        int tempColIndex=array_total[i]->col_index;
        int tempVal=array_total[i]->val;
        
        rowposition[i] = tempRowIndex;
        colposition[i] = tempColIndex;

        int candidates[] = {tempVal};
        int num_candidates = 1;
        //printf("Filled cell [%d][%d] with number %d\n",tempRowIndex,tempColIndex,tempVal);
        set_candidates(&p_board->data[tempRowIndex][tempColIndex], candidates, num_candidates);

    }
    *changer = numberofuniquefilledcells(rowposition, colposition, NumsofHiddenSingle);
    free(rowposition);
    free(colposition);
}


int find_hidden_single_values(Cell **p_cells, int *hidden_single_values) // int *hidden_single_values: empty dynamic array of 81 
{                   
    int res=0;
    for (int i=1;i<=9;i++) //count from 1 to 9
    {
        int tempIndex=0;
        int count=0; 
        //int temp_index=-1;
      
        for (int j=0;j<9;j++) //loop for number of cells in row,column or box
        {
            if (p_cells[j]->num_candidates==1)
        {
            continue;         
        }
            for (int k=0;k<9;k++) //loop for number of element in candidates list in a cell
            {
                if (1==p_cells[j]->candidates[k]&&i==k+1)
                {                   
                    tempIndex=j;
                    //printf("Found number %d appear at cells %d\n",i,j);
                    
                    count++;
                }
                
            }

                    
            
            
        }
        if (count==1)
        {
                hidden_single_values[tempIndex]=i; //store cell tempIndex the hidden single value i
                //printf("Found hidden single value %d at cell %d\n",i,tempIndex);
                res++;
        }

    }
    return res;

}