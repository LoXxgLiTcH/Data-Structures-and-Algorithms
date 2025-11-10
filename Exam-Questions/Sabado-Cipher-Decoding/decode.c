#include <stdio.h>
#include <stdlib.h>
#include "decode.h"


// Write your functions here...
int* bitmaskToArray(short int word[]){
    int *conv = (int*)malloc(64 * sizeof(int));
    int count = 0;
    if(conv != NULL){
        for(int i = 0; i < 4; i++){
            for(unsigned short int mask = 1 << ((8 * sizeof(short int)) - 1); mask != 0; mask = mask >> 1){
               if((mask & word[i]) != 0){
                   conv[count] = 1;
               }
               else{
                   conv[count] = 0;
               }
            count++;
            }
        }
    }
    else{
        printf("MEMORY ALLOCATION FAILED!");
    }
    return conv;
}
char* decodeString(int arr[]){
    char* decoded = (char*)malloc(9 * sizeof(char));
    int counter = 0;
    for(int i = 0; i < 8; i++){
        int sum = 0;
        for(int j = 7; j >= 0; j--){
            if(arr[counter] == 1){
                sum += 1 << j;
            }
            counter++;
        }
        decoded[i] = (char)sum;
    }
    decoded[8] = '\0';
   return decoded;
}
void displayBitPattern(int arr[]){
    for(int i = 0; i < 64; i++){
      printf("%d%s", arr[i], (i + 1) % 16 == 0 ? " " : "");
    }
}