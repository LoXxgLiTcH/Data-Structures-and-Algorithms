// Implementing Basic Partially Ordered Tree
// Minheap Implementation
/* Formulas to Remember: 
        Get the Index of Left Child: 2 * (Parent Index) + 1
        Get the Index of Right Child: 2 * (Parent Index) + 2
        Determine the index of Parent Node: (Child Index - 1) / 2
    Notes on Operations:
    1. Insert(x, A) = adds element x in set A, if element x is not yet a member of the set
    2. Deletemin(A) = removes and returns the smallest element in set A if the set is not empty; otherwise, the operation fails. 
*/
#include <stdio.h>
#include <stdbool.h>
#define MAX 10

typedef struct{
    int elem[MAX];
    int lastNdx;
}Tree;

void initTree(Tree*);
void insertTree(Tree*, int*);
void Insert(Tree*, int);
int Deletemin(Tree*);
void printTree(Tree);

int main(){
    Tree T;
    initTree(&T);

    int arr[MAX] = {3, 5, 7, 2, 6, 1, 4, 8, 9, 10};
    insertTree(&T, arr); 

    printTree(T);
    int min = Deletemin(&T);
    printf("Deleted min: %d\n", min);

    printTree(T);
    return 0;
}

// Initializes Tree by making lastNdx = -1
void initTree(Tree *T){
    T->lastNdx = -1;
}

// Places the values in the array into the Tree making sure P.O.T is satisfied
void insertTree(Tree *T, int arr[]){
    for(int i = 0; i < MAX; i++){
        Insert(T, arr[i]);
    }
}

void Insert(Tree *T, int elem){
    if(T->lastNdx + 1 != MAX){
        //Increment lastNdx and give it's value to child
        int child = ++T->lastNdx;
        int parent = (child - 1) / 2;

        // Conditions: While child is not the root (not reached the top) AND while the Parent is more than the Child (Minheap so parent must be less than the child)
        while(child != 0 && T->elem[parent] > elem){
            // Child value will be replaced with the parent's value
            T->elem[child] = T->elem[parent];

            // The parent will become the new child (It goes up the tree)
            child = parent;
            // The parent will become the parent of the new child
            parent = (child - 1) / 2;
        }

        // Insert at the right place in the tree
        T->elem[child] = elem;
    }
}

// This Function uses the Last Element of the Tree to fix P.O.T Property
int Deletemin(Tree *T){
    int temp = -1;

    // Checks if the Tree is Empty
    if(T->lastNdx >= 0){
        temp = T->elem[0];
        // data becomes the last element and lastNdx is decremented
        int data = T->elem[T->lastNdx--];
        // Hamilton Reference
        bool satisfied = false;
        int parent = 0;

        // Checks if the there are 2 or more elements in the Tree, if there is one left after decrementing, replace root with the 2nd element
        if(T->lastNdx > 0){
            while(!satisfied){
                int LC = parent * 2 + 1;
                int RC = LC + 1;
                int child;

                // Checks which child has higher priority and if Parent is a Leaf Node
                // If first condition not satisfied then go to next condition
                // Check if Right Child is Less than or Equal to the Last Index
                if(RC <= T->lastNdx){
                    // Check if Left Child is less than Right Child, if Left Child is less, child becomes LC otherwise child becomes RC
                    child = (T->elem[LC] <= T->elem[RC]) ? LC : RC;
                }
                // Check if Left Child is Less than or Equal to the Last Index
                else if(LC <= T->lastNdx){
                    child = LC;
                }
                else{
                    // P.O.T is satisfied
                    satisfied = true;
                }

                //Check if Parent is More than the Child, if yes, swap, as long as P.O.T is not Satisfied
                if(!satisfied){
                    if(T->elem[child] < data){
                        T->elem[parent] = T->elem[child];
                        parent = child;
                    }
                    else{
                        satisfied = true;
                    }
                }
            }
        }
        //Insert Last Element to Correct Spot
        T->elem[parent] = data;
    }
    return temp;
}

void printTree(Tree T){
    if(T.lastNdx == -1){
        printf("Tree is Empty!");
    }
    else{
        printf("Complete Tree List:\n");
        int i;
        for(i = 0; i < T.lastNdx; i++){
            printf(" %d,", T.elem[i]);
        }
        printf(" %d\n", T.elem[i]);
    } 
}