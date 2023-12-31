#include "hidden_triples.h"
#include<stdlib.h>
#include<stdio.h>
int hidden_triples(SudokuBoard *p_board)
{

    for (int i=0;i<9;i++) //loop in row
    {
        GetFoundTrip2(p_board->p_rows[i]);
    }
    for (int i=0;i<9;i++) //loop in column
    {
        GetFoundTrip2(p_board->p_cols[i]);
    }
    for (int i=0;i<9;i++) //loop in boxes
    {
        GetFoundTrip2(p_board->p_boxes[i]);
    }

    int result=0;

    for (int i=0;i<9;i++) //loop in row
    {
        //printf("currently in row %d\n", i);
        find_hidden_triples(p_board->p_rows[i],&result);
    }
    for (int i=0;i<9;i++) //loop in column
    {
        //printf("currently in column %d\n", i);
        find_hidden_triples(p_board->p_cols[i],&result);
    }
    for (int i=0;i<9;i++) //loop in boxes
    {
        //printf("currently in box %d\n", i);
        find_hidden_triples(p_board->p_boxes[i],&result);
    }

    return result;
}

void find_hidden_triples(Cell **p_cell, int *result)
{

    struct NumIndexStore2 *ValueStore[9];
    for (int i=0;i<9;i++)
    {
        ValueStore[i]=malloc(sizeof(struct NumIndexStore2));
        ValueStore[i]->Potential=1;
        ValueStore[i]->TempIndex=0;
        ValueStore[i]->indexStore[2]=0;
    }

        for (int i=0;i<9;i++) //loop through each cell
    {
        for (int j=0;j<9;j++) //loop through each candidate in cell
        {
            if (p_cell[i]->candidates[j]==1)
            {
                if (ValueStore[j]->Potential==0)
                {
                    continue;
                }
                if (ValueStore[j]->TempIndex==3)
                {
                    ValueStore[j]->Potential=0;
                }
                else
                {
               
                    //printf("currently in cell %d\n",i);
                    ValueStore[j]->indexStore[ValueStore[j]->TempIndex]=i;
                    //printf("ValueStore[%d]->IndexStore[ValueStore[%d]->tempIndex]=%d\n",j,j,i);
                    ValueStore[j]->TempIndex=ValueStore[j]->TempIndex+1;
                }
            }
        }
        
    }

    for (int i=0;i<9;i++)
    {
        if (ValueStore[i]->TempIndex>3||ValueStore[i]->TempIndex<2)
        ValueStore[i]->Potential=0;
    }
    //print check
    /*
    for (int i=0;i<9;i++)
    { 
        if (ValueStore[i]->Potential==1)
        {
            printf("\n");
            printf("Value %d appear triple at index %d %d %d",i+1,ValueStore[i]->indexStore[0],ValueStore[i]->indexStore[1],ValueStore[i]->indexStore[2]);
            printf("\n");
        }
    }
    */

   for (int i=0;i<7;i++)
   {
        int GroupingArray[3]={0,0,0};
        if (ValueStore[i]->Potential!=1)
        {
            continue;            
        }
        get_candidates_plus2(ValueStore[i],GroupingArray);
        for (int j=i+1;j<8;j++)
        {
            if (ValueStore[j]->Potential!=1)
            {
                continue;
            }
            int TempArray[3]={0,0,0};
            get_candidates_plus2(ValueStore[j],TempArray);
            int TempResultArray[3]={0,0,0};
            CompareArray2(GroupingArray,TempArray,TempResultArray,3);
            int GroupingArrayCopy[3];
            for (int a=0;a<3;a++)
            {
            GroupingArrayCopy[a]=GroupingArray[a];
            }
            int Res=combineArray2(GroupingArrayCopy,TempResultArray,3);
            if (Res==0)
            {
            continue;
            }
            for (int k=j+1;k<9;k++)
            {
                if (ValueStore[k]->Potential!=1)
                {
                    continue;
                }
                int TempArray2[3]={0,0,0};
                get_candidates_plus2(ValueStore[k],TempArray2);
                int TempResultArray2[3]={0,0,0};
                CompareArray2(GroupingArrayCopy,TempArray2,TempResultArray2,3);
                int GroupingArrayCopyCopy[3];
                for (int a=0;a<3;a++)
                {
                    GroupingArrayCopyCopy[a]=GroupingArrayCopy[a];
                }
                int Res2=combineArray2(GroupingArrayCopyCopy,TempResultArray2,3);
                if (Res2==0)
                {
                    continue;
                }
                int CountNotZero=CountNonZero2(GroupingArrayCopyCopy,3);
                if (CountNotZero==3)
                {
                    if (p_cell[GroupingArrayCopyCopy[0]]->num_candidates>3&&p_cell[GroupingArrayCopyCopy[1]]->num_candidates>3&&p_cell[GroupingArrayCopyCopy[2]]->num_candidates>3)
                    {
                        
                        if (p_cell[ValueStore[i]->indexStore[0]]->Found!=1||p_cell[ValueStore[i]->indexStore[1]]->Found!=1||p_cell[ValueStore[i]->indexStore[2]]->Found!=1)
                            {
                                p_cell[ValueStore[i]->indexStore[0]]->Found=1;
                                p_cell[ValueStore[i]->indexStore[1]]->Found=1;
                                p_cell[ValueStore[i]->indexStore[2]]->Found=1;
                                *result=(*result)+1;
                            }


                    //printf("\nHidden triple value %d %d %d is at index %d %d %d\n",i+1,j+1,k+1,GroupingArrayCopyCopy[0],GroupingArrayCopyCopy[1],GroupingArrayCopyCopy[2]);

                    for (int t=0;t<9;t++)
                    {
                        if (t==GroupingArrayCopyCopy[0]||t==GroupingArrayCopyCopy[1]||t==GroupingArrayCopyCopy[2])
                        {
                            for (int p=0;p<9;p++)
                            {
                                if (p==i||p==j||p==k)
                                {
                                    continue;
                                }
                                unset_candidate(p_cell[t],p+1);
                            }
                        }
                    }
                    }
                }
            }          
        }
   }

    for (int i=0;i<9;i++)
    {
        free(ValueStore[i]);
    }
}
int CountNonZero2(int array[], int size)
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

void get_candidates_plus2(struct NumIndexStore2 *ValueStore, int out[]) //note that out need to be declared with the size of numcandidates
{
    int counter = 0;
    for (int i = 0; i < 3; i++)
    {      
            out[counter++] = ValueStore->indexStore[i];
    }
   
}

// This function compares two arrays of integers with the same size and stores the values that are in b but not in a in array c
void CompareArray2(int a[], int b[], int c[], int size) {
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
int combineArray2(int a[], int b[], int size) {
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

void GetFoundTrip2(Cell **p_cell)
{
    for (int i=0;i<9;i++)
    {
        p_cell[i]->Found=0;
    }
}