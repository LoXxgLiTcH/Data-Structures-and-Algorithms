#include <stdio.h>
#include <math.h>
#define SIZE 0xFF
typedef struct{
    int elem[SIZE];
    int count;
}maxHeap;

// --- Heapify MaxHeap Operations ---
// Basic Operations
void initTree(maxHeap*);
void insertTree(maxHeap*, int[], int);

// MaxHeap Specific Operations
void maxSubHeapify(maxHeap*, int); // Makes the Subtree a Heap
void maxHeapifyTree(maxHeap*); // Calls MaxSubHeapify

// Sorting Operations
void swap(int*, int*); // Swaps the root with the lowest level leaf node found at the rightmost
void heapSort(maxHeap*); // Sorts in Ascending Order, Calls all MaxHeap Specific Functions to Sort the Heap

// Printing Tree Operation
void printTreeList(maxHeap);
void visualizeTree(maxHeap, int, int, char*, int, int);

int main(){
    int arr[10] = {3, 5, 6, 2, 4, 8, 9, 1, 7, 10};
    maxHeap H;
    initTree(&H);

    insertTree(&H, arr, 10);
    printf("Before Heapify:\n");
    printTreeList(H);
    printf("Visualize Tree:\n");
    visualizeTree(H, H.count, 0, "", 0, 1);

    maxHeapifyTree(&H);
    printf("\nAfter Heapify:\n");
    printTreeList(H);
    printf("Visualize Tree:\n");
    visualizeTree(H, H.count, 0, "", 0, 1);

    heapSort(&H);
    printf("\nAfter Heapsort:\n");
    printTreeList(H);
    printf("Visualize Tree:\n");
    visualizeTree(H, H.count, 0, "", 0, 1);
    return 0;
}

void initTree(maxHeap* H){
    H->count = 0;
}

void insertTree(maxHeap* H, int* arr, int size){
    for(int i = 0; i < size; i++){
        H->elem[i] = arr[i];
        H->count++;
    }
}

void swap(int* root, int* leaf){
    int temp = *root;
    *root = *leaf;
    *leaf = temp;
}

void maxSubHeapify(maxHeap* H, int parent){
    // Checks if Empty
    if(H->count > 0){
        int satisfied = 0;

        while(satisfied == 0){
            int LC = (2 * parent) + 1;
            int RC = LC + 1;
            int child;

            if(RC < H->count){
                child = (H->elem[LC] > H->elem[RC]) ? LC : RC;
            }
            else if(LC < H->count){
                child = LC;
            }
            else{
                satisfied = 1;
            }

            if(satisfied == 0){
                if(H->elem[parent] < H->elem[child]){
                    int temp = H->elem[child];
                    H->elem[child] = H->elem[parent];
                    H->elem[parent] = temp;

                    parent = child;
                }
                else{   
                    satisfied = 1;
                }
            }
        }
    }
    else{
        printf("Tree is Empty...\n");
    }  
}

void maxHeapifyTree(maxHeap* H){
    if(H->count > 0){
        int lastNdx = H->count - 1;
        for(int i = (lastNdx - 1) / 2; i >= 0; i--){
            maxSubHeapify(H, i);
        }
    }
}

void heapSort(maxHeap* H){
    maxHeapifyTree(H);
    int originalCount = H->count;
    while(H->count > 1){
        swap(&H->elem[0], &H->elem[H->count - 1]);
        H->count--;
        maxSubHeapify(H, 0);
    }
    H->count = originalCount;
}

void printTreeList(maxHeap H){
    int i;
    printf("Completed Tree:\n");
    for(i = 0; i < H.count - 1; i++){
        printf(" %d,", H.elem[i]);
    }
    printf(" %d\n", H.elem[i]);
}

void visualizeTree(maxHeap H, int n, int index, char *prefix, int isLeft, int isRoot) {
    if (index >= n) return;

    if (isRoot) {
        printf("%d\n", H.elem[index]);
    } else {
        printf("%s", prefix);
        printf("%s-- %d\n", isLeft ? "|": "\\", H.elem[index]);
    }

    char newPrefix[200];
    if (isRoot) {
        newPrefix[0] = '\0';
    } else {
        sprintf(newPrefix, "%s%s", prefix, isLeft ? "|   " : "    ");
    }

    int left  = 2*index + 1;
    int right = 2*index + 2;

    if (left < n)
        visualizeTree(H, n, left, newPrefix, 1, 0);

    if (right < n)
        visualizeTree(H, n, right, newPrefix, 0, 0);
}
  