#include <stdio.h>
#include <stdbool.h>
#define MAX 10

typedef struct{
    char data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int avail;
}VirtualHeap;

typedef int List;

// Function Prototypes
void init(List*);
void insertFirst(List*, VirtualHeap*, char);
void insertLast(List*, VirtualHeap*, char);
void delete(List*, VirtualHeap*, char);
bool member(List, VirtualHeap, char);
int locate(List, VirtualHeap, char);
void printVHeap(List, VirtualHeap);

// Cursor Based Functions Prototypes
void initVirtualHeap(VirtualHeap*);
int mallocVHeap(VirtualHeap*);
void freeVHeap(VirtualHeap*, int);

int main(){
    List L;
    VirtualHeap VH;

    init(&L);
    initVirtualHeap(&VH);

    insertFirst(&L, &VH, 'h');
    insertFirst(&L, &VH, 'c');
    insertFirst(&L, &VH, 'e');
    insertFirst(&L, &VH, 'x');
    insertFirst(&L, &VH, 'm');
    insertLast(&L, &VH, 'a');
    insertLast(&L, &VH, 'e');
    insertLast(&L, &VH, 'l');
    insertLast(&L, &VH, 'a');
    insertLast(&L, &VH, 'y');

    printVHeap(L, VH);

    delete(&L, &VH, 'x');
    delete(&L, &VH, 'y');

    printVHeap(L, VH);

    char input;
    printf("\nEnter an Element to be Located (character only): ");
    scanf("%c", &input);
    bool isMember = member(L, VH, input);
    isMember ? printf("Element is Found\n") : printf("Element not Found\n");
    printf("Element is at: %d\n", locate(L, VH, input));
    
    return 0;
}

void initVirtualHeap(VirtualHeap *VH){
    VH->avail = 0;
    /* Loop that links each Node to the next Node  /
    /  VH->Nodes[0].link = 1                       /
    /  VH->Nodes[1].link = 2                       /
    /  VH->Nodes[2].link = 3                      */
    for(int i = 1; i < MAX; i++){
        VH->Nodes[i - 1].link = i;
    }
    
    // Assigns -2 to the link of the Last Node
    VH->Nodes[MAX - 1].link = -1;
}

int mallocVHeap(VirtualHeap *VH){
    int temp = VH->avail;
    // Checks if there are still available Nodes in the Virtual Heap.
    if(temp != -1){
        VH->avail = VH->Nodes[temp].link;
    }
    return temp;
}

void freeVHeap(VirtualHeap *VH, int index){
    // Checks if index is less than MAX and Index is more than or equal to zero
    if(index < MAX && index >= 0){
        VH->Nodes[index].link = VH->avail; // Makes the link of the index the First Available Node
        VH->avail = index; // Makes the First Available Node the Index to be Freed
    }
}

void init(List *L){
    *L = -1;
}

void insertFirst(List *L, VirtualHeap *VH, char data){
    int temp = mallocVHeap(VH);

    if(temp != -1){
        VH->Nodes[temp].data = data; //Inserts Data
        VH->Nodes[temp].link = *L; // Changes link of added Node to the Head Node
        *L = temp; //Changed Head to the Newly Added Node
    }
}

void insertLast(List *L, VirtualHeap *VH, char data){
    int *trav;
    int temp = mallocVHeap(VH);
    if(temp != -1){
        // &(VH->Nodes[*trav].link) The Memory Address of the Next Node's Link
        for(trav = L; *trav != -1; trav = &(VH->Nodes[*trav].link)){} //Traverses the Entirety of the List

        VH->Nodes[temp].data = data;
        VH->Nodes[temp].link = -1;
        *trav = temp;
    }
}

void delete(List *L, VirtualHeap *VH, char data){
    int *trav;
    if(*L != -1){
        // &(VH->Nodes[*trav].link) The Memory Address of the Next Node's Link
        // Conditions: While List doesn't reach the End and Data is not Found in the List
        for(trav = L; *trav != -1 && VH->Nodes[*trav].data != data; trav= &(VH->Nodes[*trav].link)){}

        if(*trav != -1){
            int temp = *trav;
            *trav = VH->Nodes[*trav].link;
            freeVHeap(VH, temp);
        }
        else{
            printf("Element not Found in List.\n");
        }
    }
    else{
        printf("List is Empty.\n");
    }
}

bool member(List L, VirtualHeap VH, char data){
    int trav = L;
    if(trav != -1){
        // Similar to previous Functions
        for(; trav != -1 && VH.Nodes[trav].data != data; trav = VH.Nodes[trav].link){}

        return (trav != -1) ? true : false;
    }
    else{
        printf("List is Empty.\n");
        return false;
    }
}

int locate(List L, VirtualHeap VH, char data){
    int trav;
    // Similar to previous Functions
    for(trav = L; trav != -1 && VH.Nodes[trav].data != data; trav = VH.Nodes[trav].link){}
    return trav;
}

void printVHeap(List L, VirtualHeap VH){
    int trav;
    printf("Printing List:\n");
    for(trav = L; trav != -1; trav = VH.Nodes[trav].link){
        printf("%c -> ", VH.Nodes[trav].data);
    }
    printf("FINISHED\n");
}