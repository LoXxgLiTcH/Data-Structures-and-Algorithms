// Basic Implementation of Binary Search
// Rule of Binary Search Algorithm, numbers to be sorted must be in order
#include <stdio.h>
#include <stdbool.h>
#define MAX 10

bool binarySearch(int[], int);

int main(){
    int arr[MAX] = {2, 4, 6, 7, 9, 10, 17, 21, 28, 69};
    int elem;
    printf("Element to be Searched: ");
    scanf("%d", &elem);

    if(binarySearch(arr, elem)){
        printf("Element Found...\n");
    }
    else{
        printf("Element not Found...\n");
    }
    return 0;
}

bool binarySearch(int arr[], int elem){
    int LB = 0;
    int RB = MAX - 1;
    int middle = LB + (RB - LB) / 2;

    while(LB <= RB && arr[middle] != elem){
        if(arr[middle] > elem)
        {
            RB = middle - 1;
        }
        else{
            LB = middle + 1;
        }
        middle = LB + (RB - LB) / 2; 
    }

    return (arr[middle] == elem) ? 1 : 0;
}