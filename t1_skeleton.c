#include <stdio.h>
#include <stdlib.h>
#include "t1.h"


//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    //TODO
    for(int i=0; i<size; i++){
        array[i] = i;
    }
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    //TODO
    int j = (size - 1);
    for(int i=0; i<size; i++){
        array[i] = j;
        j--;
    }
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    //TODO
    for(int i=0; i<size; i++){
        array[i] = 3;
    }
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed..
void fill_with_duplicates(int *array, int size)
{
    //TODO
    for(int i=0; i<size; i++){
        array[i] = (rand() % size);
    }
    
}

//HEADER FILE CANT BE EDITED..
// void shuffle_array(int *array, int size)
// {
//     //fisher yates algorithm
//     int i, j, tmp; // create local variables to hold values for shuffle

//     for (i = size - 1; i > 0; i--) { // for loop to shuffle
//         j = rand() % (i + 1); //randomise j for shuffle with Fisher Yates
//         tmp = array[j];
//         array[j] = array[i];
//         array[i] = tmp;
//     }
// }

//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    //TODO
    //orignally planned to fill array 0-size then shuffle

    int j;
    int used[size];

    //initialise bool array
    for(int i=0; i<size; i++){
        used[i]=0;
    }

    for(int i=0; i<size; i++){
        
        do{
            j = (rand() % size);
        }while(used[j] == 1);
        
        used[j] = 1;
        array[i] = j;
        
    }
    
    
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}
