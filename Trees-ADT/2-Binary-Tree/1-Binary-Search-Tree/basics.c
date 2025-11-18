// Binary Search Tree Implementation
#include <stdio.h>
#include <stdlib.h>
#define SIZE 0xFF

typedef struct cell{
    int elem;
    struct cell *LC;
    struct cell *RC;
}ctype, *BST;

void initTree(BST*);
void Insert(BST*, int);
void Delete(BST*, int);
int Member(BST, int);
int Min(BST);
int Max(BST);

int main(){
    int arr[] = {4, 7, 2, 3, 6, 1, 5, 8, 9, 10, 15, 28, 75, 17, 34};
    int size = sizeof(arr) / sizeof(arr[0]);

    BST S;
    return 0;
}

void initTree(BST *T){
    *T = NULL;
}

void Insert(BST* T, int elem){
        BST* trav = T;
        while(*trav != NULL && (*trav)->elem != elem){
            trav = ((*trav)->elem > elem) ? &(*trav)->LC : &(*trav)->RC;
        }

        if(*trav == NULL){
            BST temp = (BST)malloc(sizeof(ctype));
            if(temp != NULL){
                temp->elem = elem;
                temp->RC = NULL;
                temp->LC = NULL;
                *trav = temp;
            }
            else{
                printf("Memory Allocation Failed...\n");
            }
        }
        else{
            printf("Element Already Exists...\n");
        }
}

void Delete(BST* T, int elem){
    if(*T != NULL){

    }
    else{
        printf("Tree is Empty...\n");
    }
}

int Member(BST T, int elem){
    while(T != NULL && T->elem != elem){
        T = (T->elem > elem) ? T->LC : T->RC;
    }

    if(T != NULL){
        printf("Element Found...\n");
        return 1;
    }
    else{
        printf("Element not Found...\n");
        return 0;
    }
}

int Min(BST T){

}

int Max(BST T)[

]