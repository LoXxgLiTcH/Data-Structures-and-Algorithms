#include <stdio.h>
#include <stdbool.h>
#define SIZE 10

typedef enum{
    EMPTY = '\0',
    DELETED = '\1'
}Status;

typedef char Dictionary[SIZE];

void initDictionary(Dictionary);
int hash(char);
void insert(Dictionary, char);
void delete(Dictionary, char);
bool inDictionary(Dictionary, char);
void printDictionary(Dictionary);

int main(){
    Dictionary D;

    initDictionary(D);

    insert(D, 'a');
    insert(D, 'd');
    insert(D, 'c');
    insert(D, 'f');
    insert(D, 'h');
    insert(D, 's');
    insert(D, 'l');
    insert(D, 'v');

    printDictionary(D);

    delete(D, 'd');
    delete(D, 's');

    bool found = inDictionary(D, 'h');

    if(found){
        printf("Found\n");
    }
    else{
        printf("Not Found\n");
    }

    printDictionary(D);
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

void insert(Dictionary D, char data){
    int start = hash(data);
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

void delete(Dictionary D, char data){
    int start = hash(data);
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
bool inDictionary(Dictionary D, char data){
    int start = hash(data);
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