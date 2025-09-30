#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

typedef struct node{
    char elem;
    struct node* next;
}*nodetype;

typedef nodetype Dictionary[SIZE];

void initDictionary(Dictionary);
int hash(char);
void insert(Dictionary, char);
void delete(Dictionary, char);
void inDictionary(Dictionary, char);
void printDictionary(Dictionary);

int main(){
    Dictionary D;
    initDictionary(D);

    insert(D, 'A');
    insert(D, 'B');
    insert(D, 'C');
    insert(D, 'D');
    insert(D, 'E');

    printDictionary(D);

    inDictionary(D, 'B');

    delete(D, 'B');
    delete(D, 'D');

    printDictionary(D);

    return 0;
}

void initDictionary(Dictionary D){
    for(int i = 0; i < SIZE; i++){
        D[i] = NULL;
    }
}

int hash(char elem){
    return elem % SIZE;
}

void insert(Dictionary D, char elem){
    int index = hash(elem);
    nodetype *trav;

    for(trav = &D[index]; *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->next){}

    if(*trav == NULL){
        nodetype temp = (nodetype)malloc(sizeof(struct node));

        if(temp != NULL){
            temp->elem = elem;
            temp->next = NULL;
            *trav = temp;
        }
    }
}

void delete(Dictionary D, char elem){
    int index = hash(elem);
    nodetype *trav;

    for(trav = &D[index]; *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->next){}

    if(*trav != NULL){
        nodetype temp = *trav;
        *trav = temp->next;
        free(temp);
    }
}

void inDictionary(Dictionary D, char elem){
    int index = hash(elem);
    nodetype *trav;

    for(trav = &D[index]; *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->next){}

    if(*trav != NULL){
        printf("Element Found.");        
    }
    else{
        printf("Element not Found");
    }
}

void printDictionary(Dictionary D){
    printf("\nDictionary:\n");
    for(int i = 0; i < SIZE; i++){
        for(nodetype trav = D[i]; trav != NULL; trav = trav->next){
            printf("%c -> ", trav->elem);
        }
    }
    printf("FINSIHED\n");
}