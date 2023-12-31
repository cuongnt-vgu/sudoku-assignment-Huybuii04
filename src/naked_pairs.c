#include "naked_pairs.h"
#include<stdio.h>
#include<stdlib.h>
int naked_pairs(SudokuBoard *p_board)
{
    for (int i=0;i<9;i++) //loop in row
    {
        GetFounds(p_board->p_rows[i]);
    }
    for (int i=0;i<9;i++) //loop in column
    {
        GetFounds(p_board->p_cols[i]);
    }
    for (int i=0;i<9;i++) //loop in boxes
    {
        GetFounds(p_board->p_boxes[i]);
    }



int result=0;


    for (int i=0;i<9;i++) //loop in row
    {
        //printf("currently in row %d\n", i);
        find_naked_pairs_value(p_board->p_rows[i],&result);
    }
    for (int i=0;i<9;i++) //loop in column
    {
        //printf("currently in column %d\n", i);
        find_naked_pairs_value(p_board->p_cols[i],&result);
    }
    for (int i=0;i<9;i++) //loop in boxes
    {
        //printf("currently in box %d\n", i);
        find_naked_pairs_value(p_board->p_boxes[i],&result);
    }
    return result;
}
void find_naked_pairs_value(Cell **p_cells,int *result)
{
    struct Numstore *store[9];
    // Initialized storage for pair cells
    for (int i=0; i<9; i++) // count from 1 to 9
    {

        store[i] = (struct Numstore *)malloc(sizeof(struct Numstore));
        for (int k=0;k<2;k++)
        {
            store[i]->PairValueArray[k] = 0;
            //printf("store[%d]->PairValueArray[%d] = 0\n",i-1,k);
        }
        
    }
    
    
    for (int j=0; j<9; j++) // loop for number of cells in row, column, or box
    {
        int tempCount=0;
        if (p_cells[j]->num_candidates != 2)
        {
            continue;
        }
        else
        {
            for (int k=0;k<9;k++) //find the 2 elements in the pair cells and put it in the storage
            {
                if (p_cells[j]->candidates[k]==1)
                {
                    store[j]->PairValueArray[tempCount]=k+1;
                    //printf("store[%d]->PairValueArray[%d]=%d\n",j,tempCount,k+1);
                    tempCount++;
                }
            }
        }
    }
    //after that go to the store again, compare each element found in pair cells and compare it with the other pair cells
    for (int i=0;i<8;i++) //loop through index of each element in the storage which is equal to the index of pair cell 
    {
        if (store[i]->PairValueArray[0]==0) //skip through the not-pair store[i] 
        {
            continue;
        }
        else //else compare it with the rest of the pair store[i]
        {
            
            int tempArray[2]={store[i]->PairValueArray[0],store[i]->PairValueArray[1]}; //extract 2 value from pair cell and put it into temporary array
            {


                for (int j=i+1;j<9;j++)
                {
                    if (store[i]->PairValueArray[0]==0) //skip through the not-pair store[i] 
                    {
                        continue;
                    }
                    else
                    {
                        if (store[j]->PairValueArray[0]==tempArray[0]&&store[j]->PairValueArray[1]==tempArray[1]) 
                        {        //extract 2 value from The Other pair cell and compare it with temporary array
                        if(p_cells[i]->num_candidates==2&&p_cells[j]->num_candidates==2)
                        {
                            //printf("Found naked pairs at index %d and index %d\n",i,j);       
                            if (p_cells[i]->Found!=1&&p_cells[j]->Found!=1)
                            {
                                p_cells[i]->Found=1;
                                p_cells[j]->Found=1;
                                *result=(*result)+1;
                            }
                            for (int t=0;t<9;t++)
                            {
                                //After having found the naked pair, unset the value inside that naked pair to the rest of the cell
                                if (t==i||t==j)
                                {
                                    continue;
                                }
                                else
                                {
                                    unset_candidate(p_cells[t],tempArray[0]);
                                    unset_candidate(p_cells[t],tempArray[1]);
                                }
                            } 
                        }
                        }                    
                        
                    }


                }

            }
        }
    }
    

    

    for (int i = 0; i < 9; i++) {
        free(store[i]);
    }
}


void GetFounds(Cell **p_cell)
{
    for (int i=0;i<9;i++)
    {
        p_cell[i]->Found=0;
    }
}