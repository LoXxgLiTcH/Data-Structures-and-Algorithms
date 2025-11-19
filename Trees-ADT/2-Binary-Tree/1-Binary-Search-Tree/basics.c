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
void insertAll(BST*, int[], int);
void Insert(BST*, int);
void Delete(BST*, int);
int Member(BST, int);
BST* Min(BST*);
BST* Max(BST*);
// --- New Visualization Functions ---
void visualizeInorder(BST T);
void visualizePreorder(BST T, int level); // Helper for indented print
void Visualize(BST T);
// -----------------------------------

int main(){
    int arr[] = {4, 7, 2, 3, 6, 1, 5, 8, 9, 10, 15, 28, 75, 17, 34};
    int size = sizeof(arr) / sizeof(arr[0]);

    BST S;
    initTree(&S);
    insertAll(&S, arr, size);

    printf("--- Initial BST Visualization ---\n");
    Visualize(S);
    printf("-----------------------------------\n");

    int member = Member(S, 5);
    Delete(&S, 5);
    
    printf("\n--- BST Visualization After Deleting 5 ---\n");
    Visualize(S);
    printf("------------------------------------------\n");

    member = Member(S, 5);
    return 0;
}

void initTree(BST *T){
    *T = NULL;
}

void insertAll(BST *T, int arr[], int size){
    for(int i = 0; i < size; i++){
        Insert(T, arr[i]);
    }
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
        /*------------------------------------------------------------------------------------------------------------/
        /  Test Cases of Delete:                                                                                      /
        /    1. If the Node is the Leaf, meaning it has no Left and Right Children: Plain Delete, LINKED LIST STYLE.  /
        /    2. If the Node has one Child, either left or right: Point to Child then Delete Node.                     /
        /    3. If the Node has two Children: Use Min or Max Functions to Delete Node.                                /
        /------------------------------------------------------------------------------------------------------------*/

        if((*T) != NULL){
            BST *trav;
            for(trav = T; *trav != NULL && (*trav)->elem != elem; 
                trav = ((*trav)->elem > elem) ? &(*trav)->LC : &(*trav)->RC){}
            if(*trav != NULL){
                // Has Both Children
                BST temp;
                if((*trav)->LC != NULL && (*trav)->RC != NULL){
                    BST* min = Min(T);
                    (*trav)->elem = (*min)->elem;
                    temp = *min;
                    *min = NULL;
                }
                // Either No Children or Only one Child
                else{
                    temp = *trav;
                    *trav = ((*trav)->LC == NULL) ? (*trav)->RC : (*trav)->LC;
                }
                free(temp);
            }
            else{
                printf("Element does NOT exist in the BST...\n");    
            }
            printf("Element %d Deleted...\n", elem);
        }
        else{
            printf("Binary Search Tree is Empty...\n");
        }
        
    }
    else{
        printf("Binary Search Tree is Empty...\n");
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

BST* Min(BST *T){
    if(*T == NULL){
        printf("Binary Search Tree is Empty...\n");
        return NULL;
    }
    if((*T)->RC == NULL){
        printf("Root has no Right Child...\n");
        return NULL;
    }

    BST *trav = T;
    trav = &(*trav)->RC;
    for(; (*trav)->LC != NULL; trav = &(*trav)->LC){}
    return trav;
}

BST* Max(BST *T){
   if(*T == NULL){
        printf("Binary Search Tree is Empty...\n");
        return NULL;
    }
    if((*T)->RC == NULL){
        printf("Root has no Right Child...\n");
        return NULL;
    }

    BST *trav = T;
    trav = &(*trav)->LC;
    for(; (*trav)->RC != NULL; trav = &(*trav)->RC){}
    return trav;
}

// ----------------------------------------------------------------
// # Visualization Functions
// # NOTE: Taken From Gemini
// ----------------------------------------------------------------

void visualizeInorder(BST T) {
    if (T != NULL) {
        visualizeInorder(T->LC);
        printf("%d ", T->elem);
        visualizeInorder(T->RC);
    }
}

void visualizePreorder(BST T, int level) {
    if (T != NULL) {
        // Print the right child first (makes the output look like a tree turned 90 degrees left)
        visualizePreorder(T->RC, level + 1);

        // Print indentation
        for (int i = 0; i < level; i++) {
            printf("      "); // Adjust spacing for desired look
        }
        
        // Print the element, marking the root of the current subtree
        printf("|---%d\n", T->elem);

        // Print the left child
        visualizePreorder(T->LC, level + 1);
    }
}

void Visualize(BST T) {
    if (T == NULL) {
        printf("The BST is Empty.\n");
        return;
    }

    // 1. Inorder Traversal (Confirms Sorted Property)
    printf("\nInorder Traversal (Sorted Elements): ");
    visualizeInorder(T);
    printf("\n");

    // 2. Structural Visualization (Preorder with Indentation)
    printf("\nStructural Visualization:\n");
    visualizePreorder(T, 0);
    printf("\n");
}