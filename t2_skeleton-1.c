#include <stdio.h> 
#include <math.h>
#include "t2.h"
#include <stdlib.h>

int number_comparisons = 0;
int number_swaps = 0;

void swap(int *x, int *y){
  int tmp = *x;
  *x = *y;
  *y = tmp;
  number_swaps++;
}

void selectionSort(int arr[], int size) 
{ 
  //TODO
  int min_pos;

  for(int i = 0; i<(size-1); i++){
    min_pos = i;

    for(int j = (i+1); j < size; j++){
      number_comparisons++;
      //comparing arr[j] to arr[min_pos]
      if(arr[j] < arr[min_pos]){
        min_pos = j;
      }
    }

    if((min_pos != i) && (arr[min_pos] != arr[i])){
      // printf("SWAPING %i and %i\n", arr[min_pos], arr[i]);
      swap(&arr[min_pos], &arr[i]);
    }
  }
} 

void insertionSort(int arr[], int size) 
{ 
  //TODO

  int j; 
  int key;
  for (int i = 1; i<size; i++){
    key = arr[i];
    j = (i-1);
    
    
    //comparing key to arr[j]

    while ((j>= 0) && (arr[j] > key)){
      arr[j+1] = arr[j];
      number_swaps++; //swaping j and j+1
      j--;
      number_comparisons++;//comparing key to arr[j] every loop
    }

    number_comparisons++;//comparing key to arr[j] once regardless
    arr[j + 1] = key;
  }
  
}

int Partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low - 1);

  for(int j = low; j<high; j++){
    number_comparisons++; //comparing arr[j] to pivot
    if(arr[j] <= pivot){
        i++;
        if(arr[i] != arr[j]){
          // printf("SWAPING %i and %i\n", arr[i], arr[j]);
          swap(&arr[i], &arr[j]);
        }
    }
  }

  if(arr[i+1] != arr[high]){
    // printf("SWAPING %i and %i\n", arr[i+1], arr[high]);
    swap(&arr[i+1], &arr[high]);
  }
  

  return (i + 1);
}

void quickSortAlgo(int arr[], int low, int high){
    // pi is the partition return index of pivot
    number_comparisons++;
    if(low<high){
        int pivot_index = Partition(arr,low,high);
        quickSortAlgo(arr, low, pivot_index-1);
        quickSortAlgo(arr, pivot_index+1, high);
    }
}

void quickSort(int arr[], int size) 
{ 
  int low = 0;
  int high = size-1;
  quickSortAlgo(arr, low, high);
}




