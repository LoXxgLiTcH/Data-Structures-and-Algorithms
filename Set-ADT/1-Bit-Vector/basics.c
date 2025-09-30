//Bit Vector Implementation
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int SET[MAX];

void populateSet(SET L);
void printSet(SET L);
SET* Union(SET A, SET B);
SET* Intersection(SET A, SET B);
SET* Difference(SET A, SET B);

int main(){
    int choice;
    SET A = {};
    SET B = {};

    printf("Populate Set A:\n");
    populateSet(A);
    printf("Populate Set B:\n");
    populateSet(B);

    printf("Set A: ");
    printSet(A);

    printf("Set B: ");
    printSet(B);
    
    SET* U = Union(A, B);
    printf("Set U (Union): ");
    printSet(*U);

    SET* I = Intersection(A, B);
    printf("Set I (Intersection): ");
    printSet(*I);

    SET* D = Difference(A, B);
    printf("Set D (Difference A - B): ");
    printSet(*D);

    SET* E = Difference(B, A);
    printf("Set E (Difference B - A): ");
    printSet(*E);
    return 0;
}

void populateSet(SET L){
    int size;
    printf("Populate Set (MAX 10)\n");
    printf("Determine Size of Set: ");
    scanf("%d", &size);

    printf("Enter Elements: ");
    for(int i = 0; i < size; i++){
        int data;       
        scanf("%d", &data);

        if(data >= 0 && data < MAX){
            L[data] = 1;
        }
    }
}

void printSet(SET L){
    for(int i = 0; i < MAX; i++){
        printf(" %d", L[i]);
    }
    printf("\n");
}

SET* Union(SET A, SET B){
    SET* C = (SET*)malloc(MAX * sizeof(SET));
    
    for(int i = 0; i < MAX; i++){
        (*C)[i] = A[i] | B[i];
    }
    return C;
}

SET* Intersection(SET A, SET B){
    SET* I = (SET*)malloc(MAX * sizeof(SET));
    
    for(int i = 0; i < MAX; i++){
        (*I)[i] = A[i] & B[i];
    }
    return I;
}

SET* Difference(SET A, SET B){
    SET* D = (SET*)malloc(MAX * sizeof(SET));
    
    for(int i = 0; i < MAX; i++){
            (*D)[i] = A[i] & (~B[i]);
    }
    return D;
}