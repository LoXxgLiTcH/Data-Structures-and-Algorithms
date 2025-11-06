#include <stdio.h>
#define SIZE 10

typedef struct{
    int elem[SIZE];
    int count;
}maxHeap;

void maxSubHeapify(maxHeap*, int); // Makes the Subtree a Heap
void maxHeapifyTree(maxHeap*); // Calls MaxSubHeapify
void swap(int, int); // Swaps the root with the lowest level leaf node found at the rightmost
void heapSort(maxHeap*); // Sorts in Ascending Order, Calls all Functions to Sort the Heap

int main(){
    int arr[10] = {3, 5, 8, 2, 4, 8, 9, 1, 7, 10}; 
    return 0;
}