// MinHeap Implementation of Partially Ordered Tree
// Similar to basics.c of Trees but without the comments for hints
#include <stdio.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int lastNdx;
}minHeap;

void initTree(minHeap*);
void insertTree(minHeap*, int*);
void Insert(minHeap*, int);
int Deletemin(minHeap*);
void printTree(minHeap);

int main(){
    int arr[MAX] = {2, 5, 7, 8, 9, 10, 3, 4, 6, 1};
    minHeap H;
    initTree(&H);

    insertTree(&H, arr);
    printTree(H);

    int min = Deletemin(&H);
    printf("Deleted min Value: %d\n", min);

    printTree(H);
    return 0;
}

void initTree(minHeap* H){
    H->lastNdx = -1;
}

void insertTree(minHeap* H, int* arr){
    for(int i = 0; i < MAX; i++){
        Insert(H, arr[i]);
    }
}

void Insert(minHeap *H, int elem){
    if(H->lastNdx + 1 != MAX){
        int child = ++H->lastNdx;
        int parent = (child - 1) / 2;

        while(child != 0 && H->elem[parent] > elem){
            H->elem[child] = H->elem[parent];

            child = parent;
            parent = (child - 1) / 2;
        }

        H->elem[child] = elem;
    }
    else{
        printf("Tree is Full...\n");
    }
}

int Deletemin(minHeap* H){
    int minValue = -1;

    if(H->lastNdx < 0){
        printf("Tree is Empty...\n");
        return minValue;
    }

    minValue = H->elem[0];
    int movedValue = H->elem[H->lastNdx--];
    int parent = 0;
    bool satisfied = false;

    if(H->lastNdx > 0){

        while(!satisfied){
            int LC = (2 * parent) + 1;
            int RC = LC + 1;
            int child;

            if(RC <= H->lastNdx){
                child = (H->elem[LC] <= H->elem[RC]) ? LC : RC;
            }
            else if(LC <= H->lastNdx){
                child = LC;
            }
            else{
                satisfied = true;
            }

            if(!satisfied){
                if(H->elem[child] < movedValue){
                    H->elem[parent] = H->elem[child];
                    parent = child;
                }
                else{
                    satisfied = true;
                }
            }
        }
        H->elem[parent] = movedValue;
    }
    return minValue;
}

void printTree(minHeap H){
    if(H.lastNdx >= 0){
        int i;
        printf("Completed Tree:\n");
        for(i = 0; i < H.lastNdx; i++){
            printf(" %d,", H.elem[i]);
        }
        printf(" %d\n", H.elem[i]);
    }
    else{
        printf("Tree is Empty...\n");
    }
}