#include <stdio.h>
#define SIZE 10

typedef struct{
    char elem[SIZE];
    int count;
}List;

void initList(List*);
void insertFirst(List*, char);
int deleteElem(List*, char);
int findElem(List, char);
void displayList(List);

int main(){
    List L;

    initList(&L);
    insertFirst(&L, 'A');
    insertFirst(&L, 'B');
    insertFirst(&L, 'C');
    insertFirst(&L, 'D');
    insertFirst(&L, 'E');
    insertFirst(&L, 'F');
    insertFirst(&L, 'G');

    printf("\nBefore Delete:\n");
    displayList(L);

    deleteElem(&L, 'A');
    deleteElem(&L, 'D');
    deleteElem(&L, 'F');

    printf("\nAfter Delete:\n");
    displayList(L);

    int isFound = findElem(L, 'C');
    if(isFound == -1){
        printf("\nNot Found.\n");
    }
    else{
        printf("\nFound Element.\n");
    }
    return 0; 
}

void initList(List *L){
    L->count = 0;
}

void insertFirst(List *L, char elem){
    if(L->count != SIZE){
        int i = L->count;
        for(; i > 0; i--){
            L->elem[i] = L->elem[i - 1];
        }
        L->elem[i] = elem;
        L->count++;
    }
}

int deleteElem(List *L, char elem){
    int i = 0;
    for(; i < L->count && L->elem[i] != elem; i++){}

    if(L->elem[i] == elem){
        for(int j = i; j < L->count; j++){
            L->elem[j] = L->elem[j + 1];
        }
        L->count--;
    }
    return (L->elem[i] == elem) ? 1 : 0;
}

int findElem(List L, char elem){
    int i;
    for(i = 0; i < L.count && L.elem[i] != elem; i++){}
    return (L.elem[i] == elem) ? i : -1;
}

void displayList(List L){
    for(int i = L.count - 1; i >= 0; i--){  
        printf("%c -> ", L.elem[i]);
    }
    printf("Finished");
}