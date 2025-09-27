#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stdio.h>
#define MAX 10

typedef struct{
    char elem[MAX];
    int count;
}List;

void initList(List *L);
void insertFirst(List *L);
void insertLast(List *L);
void deleteElem(List *L);

void initList(List *L){
    L->count = 0;
}
#endif