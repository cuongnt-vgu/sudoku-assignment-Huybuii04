#include "naked_triples.h"
#include<stdio.h>
#include<stdlib.h>
int naked_triples(SudokuBoard *p_board)
{
    for (int i=0;i<9;i++) //loop in row
    {
        GetFoundTrip(p_board->p_rows[i]);
    }
    for (int i=0;i<9;i++) //loop in column
    {
        GetFoundTrip(p_board->p_cols[i]);
    }
    for (int i=0;i<9;i++) //loop in boxes
    {
        GetFoundTrip(p_board->p_boxes[i]);
    }


  int result=0;


    for (int i=0;i<9;i++) //loop in row
    {
        //printf("currently in row %d\n", i);
        find_naked_triple_value(p_board->p_rows[i],&result);
    }
    for (int i=0;i<9;i++) //loop in column
    {
        //printf("currently in column %d\n", i);
        find_naked_triple_value(p_board->p_cols[i],&result);
    }
    for (int i=0;i<9;i++) //loop in box
    {
        //printf("currently in box %d\n", i);
        find_naked_triple_value(p_board->p_boxes[i],&result);
    }


    
    return result;
}

void find_naked_triple_value(Cell **p_cells, int*result)
{
    for (int i=0;i<7;i++) //first loop through cells
    {
      int GroupingArray[3]={0,0,0};
      
      if (p_cells[i]->num_candidates<2||p_cells[i]->num_candidates>3)
      {
        continue;
      }
      get_candidates_plus(p_cells[i],GroupingArray);
      for (int j=i+1;j<8;j++) //loop through to find second naked cell and compare it with first one (second loop)
      {
        
        
        if (p_cells[j]->num_candidates<2||p_cells[j]->num_candidates>3)
        {
          continue;
        }
        
        int TempArray[3]={0,0,0};
        get_candidates_plus(p_cells[j],TempArray);
        int TempResultArray[3]={0,0,0};
        CompareArray(GroupingArray,TempArray,TempResultArray,3);  
                                  /*
                                  printf("  currently comparing with cell[%d] \n",j); 
                                  printf("Grouping array in first loop is\n");
                                    for (int a=0;a<3;a++)
                                    {
                                      printf("%d ",GroupingArray[a]);
                                    }
                                    printf("\n");             
                                  printf("the difference between Grouping array and TempArray is: ");
                                  for (int a=0;a<3;a++)
                                  {
                                    printf("%d",TempResultArray[a]);
                                  }
                                  printf("\n");
                                */
        int GroupingArrayCopy[3];
        for (int a=0;a<3;a++)
        {
          GroupingArrayCopy[a]=GroupingArray[a];
        }
        int Res=combineArray(GroupingArrayCopy,TempResultArray,3);
        if (Res==0)
        {
          continue;
        }
                              /*
                              printf("One of possible combination is: ");
                              for (int a=0;a<3;a++)
                              {
                                printf("%d ",GroupingArrayCopy[a]);
                              }
                              printf("\n");
                              */
        for (int k=j+1;k<9;k++) //compare first and second cell with third cell (final loop)
        {
          if (p_cells[k]->num_candidates<2||p_cells[k]->num_candidates>3)
          {
            continue;
          }
          int TempArray2[3]={0,0,0};
          get_candidates_plus(p_cells[k],TempArray2);
          int TempResultArray2[3]={0,0,0};
          CompareArray(GroupingArrayCopy,TempArray2,TempResultArray2,3);
          int GroupingArrayCopyCopy[3];
          for (int a=0;a<3;a++)
          {
            GroupingArrayCopyCopy[a]=GroupingArrayCopy[a];
          }
          int Res2=combineArray(GroupingArrayCopyCopy,TempResultArray2,3);
          if (Res2==0)
          {
            continue;
          }
          int CountNotZero=CountNonZero(GroupingArrayCopyCopy,3);
          if (CountNotZero==3)
          {
            //printf("\nNaked triple is at index %d %d %d\n",i,j,k);
            if (p_cells[i]->Found!=1&&p_cells[j]->Found!=1&&p_cells[k]->Found!=1)
                            {
                                p_cells[i]->Found=1;
                                p_cells[j]->Found=1;
                                p_cells[k]->Found=1;
                                *result=(*result)+1;
                            }
            for (int t=0;t<9;t++)
            {
              if (t==i||t==j||t==k)
              {
                continue;
              }
              else
              {
                for (int z=0;z<3;z++)
                {
                  unset_candidate(p_cells[t],GroupingArrayCopyCopy[z]);

                }

                //fix here
              }
            }
          }
        }
      } //end second for loop



    } 
}

    



int CountNonZero(int array[], int size)
{
    // Initialize a variable to store the count
    int count = 0;

    // Loop through the array elements
    for (int i = 0; i < size; i++)
    {
        // If the element is not zero, increment the count
        if (array[i] != 0)
        {
            count++;
        }
    }

    // Return the count
    return count;
}

void get_candidates_plus(Cell *p_cells, int out[]) //note that out need to be declared with the size of numcandidates
{
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells->candidates[i])
        {
            out[counter++] = i + 1;
        }
    }
   
}

// This function compares two arrays of integers with the same size and stores the values that are in b but not in a in array c
void CompareArray(int a[], int b[], int c[], int size) {
  // Initialize a variable to keep track of the index of c
  int index = 0;
  // Loop through each element of b
  for (int i = 0; i < size; i++) {
    // Initialize a flag to indicate if b[i] is in a or not
    int flag = 0;
    // Loop through each element of a
    for (int j = 0; j < size; j++) {
      // If b[i] is equal to a[j], set the flag to 1 and break the loop
      if (b[i] == a[j]) {
        flag = 1;
        break;
      }
    }
    // If the flag is still 0, it means b[i] is not in a, so store it in c[index] and increment index
    if (flag == 0) {
      c[index] = b[i];
      index++;
    }
  }
  // Fill the remaining elements of c with 0
  for (int i = index; i < size; i++) {
    c[i] = 0;
  }
}




/*
note that a and b share the same size
what is does is to replace every zero value in a with value from b. If every non-zero value in b is filled in a,it will return 1, else it will return 0

*/
int combineArray(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        // If a[i] is 0, find the first non-zero value in b and assign it to a[i]
        if (a[i] == 0) {
            int j;
            for (j = 0; j < size; j++) {
                if (b[j] != 0) {
                    a[i] = b[j];
                    b[j] = 0; // Mark the used value in b as 0
                    break;
                }
            }
            
        }
    }

    // Check if there are any remaining non-zero values in b
    for (int i = 0; i < size; i++) {
        if (b[i] != 0) {
            return 0;
        }
    }

    return 1;
}

void GetFoundTrip(Cell **p_cell)
{
    for (int i=0;i<9;i++)
    {
        p_cell[i]->Found=0;
    }
}