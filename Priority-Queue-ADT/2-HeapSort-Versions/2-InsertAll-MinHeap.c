#include <stdio.h>
#define SIZE 0xFF
typedef struct{
    int elem[SIZE];
    int count;
}minHeap;

// --- InsertAll MinHeap Operations --- 
// Basic Operations
void initTree(minHeap*);

// Insert Operations
void insertMinHeap(minHeap*, int);
void insertAllMinHeap(minHeap*, int[]);

// Delete Operation
int deleteMin(minHeap*);

// Sorting Operations
void heapSort(minHeap*, int[]);

// Printing Operations
void printTree(minHeap);

int main(){
    int arr[10] = {4, 6, 7, 9, 8, 10, 5, 3, 2, 1};
    minHeap H;
    initTree(&H);

    printf("Before Heapify:\n");
    for(int i = 0; i < 10; i++){
        if(i < 9){
            printf(" %d,", arr[i]);
        }
        else{
            printf(" %d\n", arr[i]);
        }
    }
    
    heapSort(&H, arr);
    return 0;
}

void initTree(minHeap* H){
    H->count = 0;
}

void insertMinHeap(minHeap* H, int elem){
    if(H->count - 1 < SIZE){
        int child = H->count++;
        int parent = (child - 1) / 2;

        while(child != 0 && H->elem[parent] > elem){
            H->elem[child] = H->elem[parent];
            child = parent;
            parent = (child - 1) / 2;
        }

        H->elem[child] = elem;
    }
    else{
        printf("Tree is Full...");
    }
}

void insertAllMinHeap(minHeap* H, int arr[]){
    for(int i = 0; i < 10; i++){
        insertMinHeap(H, arr[i]);
    }
}

int deleteMin(minHeap* H){
    int min = -1;
    if(H->count > 0){
        int parent = 0;
        min = H->elem[0];
        H->elem[0] = H->elem[H->count - 1];
        H->count--;
        int satisfied = 0;

        while(satisfied == 0){
            int LC = (2 * parent) + 1;
            int RC = LC + 1;
            int child;

            if(RC < H->count){
                child = (H->elem[LC] < H->elem[RC]) ? LC : RC;
            }
            else if(LC < H->count){
                child = LC;
            }
            else{
                satisfied = 1;
            }

            if(satisfied == 0){
                if(H->elem[child] < H->elem[parent]){
                    int temp = H->elem[parent];
                    H->elem[parent] = H->elem[child];
                    H->elem[child] = temp;
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
    return min;
}

void heapSort(minHeap* H, int *arr){
    printf("After Heapify:\n");
    insertAllMinHeap(H, arr);
    printTree(*H);
    int originalCount = H->count;
    while(H->count > 1){
        int min = deleteMin(H);
        H->elem[H->count] = min;
    }

    H->count = originalCount;
    printf("After Heapsort:\n");
    printTree(*H);
}

void printTree(minHeap H){
    int i;
    printf("Completed Tree:\n");
    for(i = 0; i < H.count - 1; i++){
        printf(" %d,", H.elem[i]);
    }
    printf(" %d\n", H.elem[i]);
}