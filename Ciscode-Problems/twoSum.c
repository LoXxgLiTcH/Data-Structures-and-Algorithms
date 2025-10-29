#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX 0XA

/*********************************/
/*    USER-DEFINED DATA TYPES    */
/*********************************/
typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef KeyValuePair Dictionary[MAX];

typedef enum {
    EMPTY = -999999,
    DELETED = -1000000
} DictStatus;

/*********************************/
/*       HELPER FUNCTIONS        */
/*********************************/
void initDict(Dictionary D);
int hash(int key);

/*********************************/
/*          YOUR TASKS           */
/*********************************/
int* twoSum(int sum, int arr[], int size, int *retSize);
void insert(Dictionary D, int key, int value);
int getValue(Dictionary D, int key);

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter elements in the array (unique): ");
    for (int i = 0; i < size; i++) scanf("%d", arr + i);

    int sum;
    printf("Enter sum: ");
    scanf("%d", &sum);

    int retSize;
    int *sumIndices = twoSum(sum, arr, size, &retSize);
    printf("Indices of elements adding up to %d are: ", sum);

    for (int i = 0; i < retSize; i++) printf("%d%s", sumIndices[i], (i + 1 == retSize) ? "" : " & ");

    return 0;
}

/*********************************/
/*       HELPER FUNCTIONS        */
/*********************************/
void initDict(Dictionary D) {
    for(int i = 0; i < MAX; i++) {
        D[i].key = EMPTY;
    }
}

int hash(int key) {
    return abs(key) % MAX;
}


/*********************************/
/*          YOUR TASKS           */
/*********************************/


// Function that returns indices of 
// two numbers that add up to `sum`
int* twoSum(int sum, int arr[], int size, int *retSize) {
    Dictionary d;
    initDict(d);
    *retSize = 0;
    bool isFound = false;
    int *indices = (int*)malloc(2 * sizeof(int));
    // Implementation here...
  for(int i = 0; i < size && !isFound; i++){
    int num = getValue(d, sum - arr[i]);
    if(num != -1){
      isFound = true;
      *retSize = 2;
      indices[0] = num;
      indices[1] = i;
    }
    else{
      insert(d, arr[i], i);
      indices[0] = -1;
      indices[1] = -1;
    }
  }
  return indices;
}

// Function that inserts a key-value
// pair into the Dictionary
void insert(Dictionary D, int key, int value) {
    // Implementation here..
  int start = hash(key);
  int index = start;
  int delCell = -1;
  bool isFull = false;

  while(!isFull && D[index].key != key && D[index].key != EMPTY){
    if(delCell == -1 && D[index].key == DELETED){
      delCell = index;
    }

    index = (index + 1) % MAX;

    if(index == start){
      isFull = true;
    }
  }

  if(!isFull){
    if(D[index].key == key){
      D[index].value = value;
    }
    else{
      int finalIdx = (delCell == -1) ? index : delCell;
      D[finalIdx].key = key;
      D[finalIdx].value = value;
    }
  }
}


// Function that returns the value based on the passed key
// Function returns -1 if key is not in the dictionary
int getValue(Dictionary D, int key) {
    // Implementation here...
  int start = hash(key);
  int index = start;
  bool finished = false;

  // Conditions: While not Finished One Loop, While key is NOT EMPTY, While Key is not Found in Dictionary
  while(!finished && D[index].key != EMPTY && D[index].key != key){
    index = (index + 1) % MAX;

    if(index == start){
      finished = true;
    }
  }

  return (D[index].key == key) ? D[index].value : -1;
}