// Exercise 2 - Basic Implementation of ADT UID in Computer Word
#include <stdio.h>
#include <stdbool.h>

//unsigned == Only positive values
typedef unsigned char SET;

void initSet(SET*);
void displaySet(SET, char[]);
void insert(SET*, int);
bool member(SET, int);
void delete(SET*, int);
SET Union(SET, SET);
SET Intersection(SET, SET);
SET Difference(SET, SET);

int main(){
    
    SET A;
    initSet(&A);

    insert(&A, 1);
    insert(&A, 5);
    insert(&A, 7);
    insert(&A, 4);
    insert(&A, 3);
    insert(&A, 6);

    displaySet(A, "Set A");
    delete(&A, 4);
    displaySet(A, "Set A");

    bool isFound = member(A, 4);
    if(isFound){
        printf("Element Found\n");
    }
    else{
        printf("Element not Found\n");
    }

    SET B;
    initSet(&B);

    insert(&B, 2);
    insert(&B, 5);
    insert(&B, 7);
    insert(&B, 6);
    insert(&B, 3);

    SET U = Union(A, B);
    SET I = Intersection(A, B);
    SET D = Difference(A, B);
    SET D_Reversed = Difference(B, A);

    printf("=================================================\n");
    displaySet(A, "Set A");
    displaySet(B, "Set b");
    displaySet(U, "Union of Set A and Set B");
    displaySet(I, "Intersection of Set A and Set B");
    displaySet(D, "Difference of Set A and Set B");
    displaySet(D_Reversed, "Difference of Set B and Set A");

    return 0;
}


//Initialize Set to 0
void initSet(SET* Z){
    *Z = 0;
}

void displaySet(SET Z, char set[]){
    SET mask = 1;
    printf("Displaying %s: { ", set);
    for(int i = 0; i < sizeof(SET) * 8; i++){
        //Checks if mask has a value, if it does, meaning the element is in the Computer Word Set
        /* ex.  Set Z = { 1, 0, 1, 1, 0 }   /
        /       mask  = { 0, 0, 1, 0, 0 }   /
        /    Z & mask = { 0, 0, 1, 0, 0 }  */
        //mask has value therefore element is there
        if((mask & Z) != 0){
            printf(" %d ", i);
        }
        mask = mask << 1;
    }
    printf(" }\n");
}

void insert(SET *Z, int data){
    SET mask = 1;
    //Inserts Using Bitwise OR
    *Z = *Z | (mask << data);
}

void delete(SET *Z, int data){
    printf("Deleting Element %d\n", data);
    SET mask = 1;
    //Deletes by Using Bitwise AND
    /* ex.      Z = { 1, 0, 1, 1, 1 } + /
    /        mask = { 0, 0, 0, 1, 0 }   /
    /       ~mask = { 1, 1, 1, 0, 1 } + /
    /   Z & ~mask = { 1, 0, 1, 0, 1 }   */   
    //Succesfully Deleted
    *Z = *Z & ~(mask << data);
}

bool member(SET Z, int data){
    SET mask = 1;
    Z = Z & (mask << data);
     //Checks if mask has a value, if it does, meaning the element is in the Computer Word Set
    /* ex.  Set Z = { 1, 0, 1, 1, 0 }   /
    /       mask  = { 0, 0, 1, 0, 0 }   /
    /    Z & mask = { 0, 0, 1, 0, 0 }  */
    //mask has value therefore element is there
    return (Z != 0) ? true : false;
}

SET Union(SET A, SET B){
    //Gets Union using Bitwise OR
    /* ex.  Set A = { 1, 0, 1, 1, 0 }   /
    /       Set B = { 1, 1, 0, 1, 1 }   /
    /       A | B = { 1, 1, 1, 1, 1 }  */
    return A | B;
}

SET Intersection(SET A, SET B){
    //Gets Intersection using Bitwise AND
    /* ex.  Set A = { 1, 0, 1, 1, 0 }   /
    /       Set B = { 1, 1, 0, 1, 1 }   /
    /       A & B = { 1, 0, 0, 1, 0 }  */
    return A & B;
}

SET Difference(SET A, SET B){
    //Gets Difference using Bitwise AND as well as Complimenting the Second Set
    /* ex.  Set A = { 1, 0, 1, 1, 0 } + /
    /       Set B = { 1, 1, 0, 1, 1 }   /
    /      Set ~B = { 0, 0, 1, 0, 0 } + /
    /      A & ~B = { 0, 0, 1, 0, 0 }  */
    return A & ~B;
}