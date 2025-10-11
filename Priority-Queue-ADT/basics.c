//Implementing Basic HeapSort
/* Formulas to Remember: 
        Get the Index of child nodes: 2 * (Index of Parent Node) + 1
        Determine the index of the lowest level parent node: (Last index - 1) / 2
*/
#include <stdio.h>
#define MAX 10

typedef struct{
    int elem[MAX];
    int lastNdx;
}Heap, List;

void Insert(Heap, int);
void Deletemin(Heap);
void HeapSort(List);

int main(){

    return 0;
}

void Insert(Heap H, int elem){
    
}