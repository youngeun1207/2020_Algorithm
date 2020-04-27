// 1-1
// Max Heap sort

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void heapify(int n, int maxHeap[]);
int deleteMax(int n, int maxHeap[]);
void heapSort(int n, int maxHeap[], int* sorted);
void precDown(int n, int i, int maxHeap[]);

int main(int argc, const char * argv[]) {
    int maxHeap[MAX];
    int temp;                                       // check input is valid
    int n = 0;                                      // # of keys
    while(1){
        scanf("%d", &temp);
        if(n > MAX){
            printf("error! out of index\n");
            break;
        }
        if (temp == -1){
            if(n == 0){
                printf("error! You must insert at least one number\n");
            }
            else break;
        }
        else{
            if(temp < 0 || temp >= 1000){
                printf("error! out of range\n");
            }
            else{
                maxHeap[n] = temp;
                n++;
            }
        }
    }
    
    int* sorted = (int*)malloc(sizeof(int) * n);    // sorted array
    
    heapSort(n, maxHeap, sorted);
    
    for(int i = 0; i < n; i++) {                    // print sorted array
        printf("%d ", sorted[i]);
    }printf("\n");
    
    return 0;
}

void heapify(int n, int maxHeap[]){                 // call precDown() n/2 to 0 (parent nodes)
    for (int i = n/2; i > 0; i--) {
        precDown(i, n, maxHeap);
    }
}
void precDown(int i, int n, int maxHeap[]){
    int child = 0;
    int temp;
    for(temp = maxHeap[i-1]; i*2 <= n; i = child){
        child = i*2;
        if(child != n && maxHeap[i*2] > maxHeap[i*2-1]){    // compare children
            child++;
        }
        if(temp < maxHeap[child-1]){                        // compare with parent
            maxHeap[i-1] = maxHeap[child-1];
        }
        else break;
    }
    maxHeap[i-1] = temp;
}
int deleteMax(int n, int maxHeap[]){
    int max = maxHeap[0];
    maxHeap[0] = maxHeap[n-1];              // insert last node's value into first node
    heapify(n, maxHeap);
    return max;
}
void heapSort(int n, int maxHeap[], int* sorted){
    heapify(n, maxHeap);
    for(int i = 0; n > 0; i++) {
        sorted[i] = deleteMax(n, maxHeap);
        n--;                                // remove last node
    }
}
