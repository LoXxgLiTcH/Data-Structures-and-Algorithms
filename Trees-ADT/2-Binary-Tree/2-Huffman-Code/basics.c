// Implementation of Huffman Code
#include <stdio.h>
#define SIZE 0xFF

typedef struct {
    char elem;
    int occurence;
}ctype;

typedef struct {
    ctype node[SIZE];
    int lastNdx;
}Tree;

void initTree(Tree*);
void populateTempTree(ctype[]);
void insertTree(Tree*, ctype[]);
int smallestOccurences(ctype[]);
void insertAllMinHeap(Tree*, ctype[]);
void insertMinHeap(Tree*, ctype);
void Insert(Tree*, ctype[]);
void avgCodeLength(Tree*, char);

int main(){
    Tree T;
    ctype temp[6];
    initTree(&T);

    populateTempTree(temp);
    insertTree(&T, temp);
   
}

void initTree(Tree* T){ 
    T->lastNdx = -1;
}

void populateTempTree(ctype arr[]){
    arr[0].elem = 'A';
    arr[0].occurence = 25;
    arr[1].elem = 'B';
    arr[1].occurence = 5;
    arr[2].elem = 'C';
    arr[2].occurence = 20;
    arr[3].elem = 'D';
    arr[3].occurence = 15;
    arr[4].elem = 'E';
    arr[4].occurence = 15;
    arr[5].elem = 'F';
    arr[5].occurence = 20;
}

void insertAllMinHeap(Tree* T, ctype arr[]){
    for(int i = 0; i < 6; i++){
        insertMinHeap(T, arr[i]);
    }
}

void insertMinHeap(Tree *T, ctype node){
    
}

void Insert(Tree* T, ctype arr[]){
    if(T->lastNdx < SIZE){

    }
    else{
        printf("Tree is Full...\n");
    }
}