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
    int mean = LB + (RB - LB) / 2;

    while(LB <= RB && arr[mean] != elem){
        if(arr[mean] > elem)
        {
            RB = mean - 1;
        }
        else{
            LB = mean + 1;
        }
        mean = LB + (RB - LB) / 2; 
    }

    return (arr[mean] == elem) ? 1 : 0;
}