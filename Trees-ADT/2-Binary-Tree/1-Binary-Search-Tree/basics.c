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

    // Search Functions
    int Member(BST, int);
    int MemberRecursion(BST, int);
    BST* Min(BST*);
    BST* Max(BST*);
    // --- New Visualization Functions ---
    void visualizeInorder(BST T);
    void visualizePreorder(BST T, int level); // Helper for indented print
    void Visualize(BST T);
    // -----------------------------------

    int main(){
        // The base array for most tests
        int arr[] = {4, 7, 2, 3, 6, 1, 5, 8, 9, 10, 15, 28, 75, 17, 34};
        int size = sizeof(arr) / sizeof(arr[0]);
        BST S;
        int elem;

        // --- SETUP: Full Tree for Deletion Cases ---
        printf("\n--- Test Setup: Initial Full Tree ---\n");
        initTree(&S);
        insertAll(&S, arr, size);
        printf("Element to be Searched: ");
        scanf("%d", &elem);
        printf("Search Member (Non-Recursion):\n");
        Member(S, elem);
        printf("Search Member (Recursion):\n");
        MemberRecursion(S, elem);
        Visualize(S);

        // --- TEST 1, 2, 9: Leaf and Simple Deletion ---
        printf("\n\n--- TEST 1: Delete Leaf Node (1) ---\n");
        Delete(&S, 1);
        Visualize(S);

        printf("\n\n--- TEST 9: Repeated Deletion (6, then 6 again) ---\n");
        Delete(&S, 6); // Case 1: Leaf
        Delete(&S, 6); // Test: Not Found
        Visualize(S);

        // --- TEST 10: Delete Node with 1 Child (Left Link) ---
        printf("\n\n--- TEST 10: Delete Node with 1 Child (2) ---\n");
        Delete(&S, 2); // Case 2: 2 has only child 3
        Visualize(S);

        // --- TEST 3: Delete Node with 1 Child (Right Link) ---
        printf("\n\n--- TEST 3: Delete Node with 1 Child (7) ---\n");
        Delete(&S, 7); // Case 2: 7 has only child 8
        Visualize(S);


        // --- TEST 5 & 6: Two-Child Deletion (Harder Cases) ---
        printf("\n\n--- TEST 5: Delete Node with 2 Children (15) ---\n");
        Delete(&S, 15); // Case 3: 15 replaced by successor 17
        Visualize(S);
        
        printf("\n\n--- TEST 6: Delete Node with 2 Children (28) ---\n");
        Delete(&S, 28); // Case 3: 28 replaced by successor 34
        Visualize(S);

        // --- TEST 4: Delete the Root (The Ultimate Test) ---
        printf("\n\n--- TEST 4: Delete the Root (4) ---\n");
        Delete(&S, 4); // Case 3: 4 replaced by successor 5
        Visualize(S);

        // --- TEST 7: Element Not Found ---
        printf("\n\n--- TEST 7: Delete Non-Existent Element (99) ---\n");
        Delete(&S, 99); // Test: Not Found
        
        
        // --- TEST 8: Delete from Empty Tree ---
        printf("\n\n--- TEST 8: Delete from an Empty Tree ---\n");
        BST EmptyTree;
        initTree(&EmptyTree);
        Delete(&EmptyTree, 100); // Test: Empty Tree message

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
            BST *trav;
            for(trav = T; *trav != NULL && (*trav)->elem != elem; 
                trav = ((*trav)->elem > elem) ? &(*trav)->LC : &(*trav)->RC){}
            if(*trav != NULL){
                // Runs if Node to be Deleted Has Both Children
                BST temp;
                if((*trav)->LC != NULL && (*trav)->RC != NULL){
                    // Successor using Min
                    BST* successor = Min(&(*trav)->RC);
                    (*trav)->elem = (*successor)->elem;
                    trav = successor;

                    // Predecessor using Max
                    // BST* predecessor = Max(&(*trav)->LC);
                    // (*trav)->elem = (*predecessor)->elem;
                    // trav = predecessor;
                }
                // Runs Regardless of the Test Cases
                temp = *trav;               
                *trav = ((*trav)->LC == NULL) ? (*trav)->RC : (*trav)->LC;
                free(temp);
                printf("Element %d Deleted...\n", elem);
            }
            else{
                printf("Element does NOT exist in the BST...\n");    
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

    int MemberRecursion(BST T, int elem){
        if(T == NULL){
            printf("Element Not Found...\n");
            return 0;
        }
        if(T->elem == elem){
            printf("Element Found...\n");
            return 1;
        }
        
        return (T->elem < elem) ? MemberRecursion(T->RC, elem) : MemberRecursion(T->LC, elem);
    }

    BST* Min(BST *T){
        BST *trav;
        for(trav = T; (*trav)->LC != NULL; trav = &(*trav)->LC){}
        return trav;
    }

    BST* Max(BST *T){
        BST *trav;
        for(trav = T; (*trav)->RC != NULL; trav = &(*trav)->RC){}
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