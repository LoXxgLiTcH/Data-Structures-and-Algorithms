// MinHeap Implementation of Partially Ordered Tree
// Similar to basics.c but without the comments for hints
// Uses maxHeap which makes the Root the Biggest Element
#include <stdio.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int lastNdx;
} maxHeap;

void initTree(maxHeap*);
void insertTree(maxHeap*, int*);
void Insert(maxHeap*, int);
int Deletemax(maxHeap*);
void printTree(maxHeap);

int main(){
    int arr[MAX] = {14, 16, 17, 19, 20, 18, 15, 13, 12, 11};
    maxHeap H;
    initTree(&H);

    insertTree(&H, arr);
    printTree(H);

    int max = Deletemax(&H);
    printf("Deleted max Value: %d\n", max);

    printTree(H);
    return 0;
}

void initTree(maxHeap* H){
    H->lastNdx = -1;
}

void insertTree(maxHeap* H, int arr[]){
    for(int i = 0; i < MAX; i++){
        Insert(H, arr[i]);
    }
}

void Insert(maxHeap* H, int elem){
    if(H->lastNdx + 1 != MAX){
        int child = ++H->lastNdx;
        int parent = (child - 1) / 2;

        while(child != 0 && H->elem[parent] < elem){
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

int Deletemax(maxHeap* H){
    int maxValue = -1;

    if(H->lastNdx >= 0){
        maxValue = H->elem[0];
        int movedValue = H->elem[H->lastNdx--];
        int parent = 0;
        bool satisfied = false;

        if(H->lastNdx > 0){
            while(!satisfied){
                int LC = (2 * parent) + 1;
                int RC = LC + 1;
                int child;

                if(RC <= H->lastNdx){
                    child = (H->elem[LC] > H->elem[RC]) ? LC : RC;
                }
                else if(LC <= H->lastNdx){
                    child = LC;
                }
                else{
                    satisfied = true;
                }

                if(!satisfied){
                    if(H->elem[child] > movedValue){
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
    }
    else{
        printf("Tree is Empty...");
    }
    return maxValue;
}

void printTree(maxHeap H){
    if(H.lastNdx >= 0){
        int i;
        printf("Completed Tree:\n");
        for(i = 0; i < H.lastNdx; i++){
            printf(" %d,", H.elem[i]);
        }
        printf("%d\n", H.elem[i]);
    }
    else{
        printf("Tree is Empty...");
    }
}