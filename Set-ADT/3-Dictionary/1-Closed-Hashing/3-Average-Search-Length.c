#include <stdio.h>
#include <stdbool.h>
#define SIZE 10

typedef enum{
    EMPTY = '\0',
    DELETED = '\1'
}Status;

typedef char Dictionary[SIZE];

void initDictionary(Dictionary D);
void insert(Dictionary D, char data, int hash);
void delete(Dictionary D, char data, int hash);
bool inDictionary(Dictionary D, char data, int hash);
void printDictionary(Dictionary D);
int searchLength(Dictionary D, char data, int hash);
float avgSearchLength(Dictionary D);

int main(){
    Dictionary D;

    initDictionary(D);

    insert(D, 'A', 1);
    insert(D, 'B', 4);
    insert(D, 'C', 9);
    insert(D, 'D', 9);
    insert(D, 'E', 0);
    insert(D, 'F', 3);
    insert(D, 'G', 4);
    insert(D, 'H', 3);

    printDictionary(D);

    bool found = inDictionary(D, 'B', 4);

    printf("Is Data in Dictionary? ");
    (found) ? printf("Yes\n") : printf("No\n");

    printf("The Average Size Length of all Data is: %.2f", avgSearchLength(D));

    return 0;
}

//Initializes Dictionary to all be EMPTY
void initDictionary(Dictionary D){
    for(int i = 0; i < SIZE; i++){
        D[i] = EMPTY;
    }
}

//Creates Hash Value
int hash(char data){
    int hash = data % SIZE;
    return hash;
}

void insert(Dictionary D, char data, int hash){
    int start = hash;
    int index = start; 
    int delCell = -1;
    bool isFull = false;

    //-------------------------------------------------------------------------------------------------//    
    /*  Conditions of WHILE Loop:                                                                       /        
    /     1. Dictionary is NOT FULL                                                                     /
    /     2. Index is NOT EQUAL to data                                                                 /
    /     3. Index is NOT EMPTY, EMPTY meaning it is a free cell with no previous data stored in it    */
    //-------------------------------------------------------------------------------------------------//
    while(!isFull && D[index] != data && D[index] != EMPTY){
        //Checks First Deleted Cell
        if(delCell == -1 && D[index] == DELETED){
            delCell = index;
        }

        //Goes to next Index, Circular Array
        index = (index + 1) % SIZE;

        //Checks if Index is Equal to Start meaning the Dictionary is Full
        if(index == start){
            isFull = true;
        }
    }
    //End of Loop Code Block

    //Checks if Dictionary is FULL and there is no DELETED cell to insert
    if(isFull && delCell == -1){
        printf("\nDictionary is FULL!\n");
    }
    //Checks if Index is an EMPTY Cell or there is an available DELETED Cell
    else if(delCell != -1 || D[index] == EMPTY){
        //Ternary Operator to insert in EMPTY Cell or DELETED CELL
        D[(delCell == -1) ? index : delCell] = data;
    }
}

void delete(Dictionary D, char data, int hash){
    int start = hash;
    int index = start;
    bool finished = false;

    //-------------------------------------------------------------------------------------------------//    
    /*  Conditions of WHILE Loop:                                                                       /        
    /     1. Has not finished Looping around once                                                       /
    /     2. Index is NOT EQUAL to data                                                                 /
    /     3. Index is NOT EMPTY, EMPTY meaning it is a free cell with no previous data stored in it    */
    //-------------------------------------------------------------------------------------------------//
    while(D[index] != data && !finished && D[index] != EMPTY) {
        index = (index + 1) % SIZE;

        //Index has looped once and has returned to start meaning data was not found
        if(index == start){
            finished = true;
        }
    }

    //Checks if data was found in index
    if(D[index] == data){
        D[index] = DELETED;
    }
}

//Checks if data is in Dictionary
bool inDictionary(Dictionary D, char data, int hash){
    int start = hash;
    int index = start;
    bool finished = false;

    //-------------------------------------------------------------------------------------------------//    
    /*  Conditions of WHILE Loop:                                                                       /        
    /     1. Has not finished Looping around once                                                       /
    /     2. Index is NOT EQUAL to data                                                                 /
    /     3. Index is NOT EMPTY, EMPTY meaning it is a free cell with no previous data stored in it    */
    //-------------------------------------------------------------------------------------------------//
    while(D[index] != data && !finished && D[index] != EMPTY) {
        index = (index + 1) % SIZE;

        //Index has looped once and has returned to start meaning data was not found
        if(index == start){
            finished = true;
        }
    }

    //Ternary Operator returning true or false if data was found in the Dictionary or Not
    return (D[index] == data) ? true : false;
}


//Prints Dictionary
void printDictionary(Dictionary D){
    for(int i = 0; i < SIZE; i++){
        if(D[i] == EMPTY){
            printf("EMPTY -> ");
        }
        else if(D[i] == DELETED){
            printf("DELETED -> ");
        }
        else{
            printf("%c -> ", D[i]);
        }
    }

    printf("FINSIHED\n");
}

int searchLength(Dictionary D, char data, int hash){
    int start = hash;
    int index = start;
    bool finished = false;

    while(!finished && D[index] != EMPTY && D[index] != data){
        index = (index + 1) % SIZE;

        if(index == start){
            finished == true;
        }
    }

    int length = (index - start + SIZE) % SIZE + 1;

    printf("Average Size Length of %c: %d\n", data, length);
    return (finished != true) ? length : -1;
}

float avgSearchLength(Dictionary D){
    int sum = searchLength(D, 'A', 1) + searchLength(D, 'B', 4) + searchLength(D, 'C', 9) + searchLength(D, 'D', 9) + searchLength(D, 'E', 0)
              + searchLength(D, 'F', 3) + searchLength(D, 'G', 4) + searchLength(D, 'H', 3);

    float size = 0;          
    for(int i = 0; i < SIZE; i++){
        if(D[i] != EMPTY || D[i] != DELETED){
            size++;
        }
    }
    return (sum / size);
}