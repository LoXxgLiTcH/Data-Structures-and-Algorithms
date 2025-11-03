//Implementing Basic HeapSort
/* Formulas to Remember: 
        Get the Index of Child Nodes: 2 * (Parent Index) + 1
        Determine the index of Parent Node: (Child Index - 1) / 2
*/
#include <stdio.h>
#define MAX 10

typedef struct{
    int elem[MAX];
    int lastNdx;
}Heap, List;

void Insert(Heap*, int);
void Deletemin(Heap*);
void HeapSort(List*);

int main(){

    return 0;
}

void Insert(Heap *H, int elem){
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
}

void Deletemin(Heap *H){
    
}