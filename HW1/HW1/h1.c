// 1-1
// Min Heap sort

#include <stdio.h>
#include <stdlib.h>
#define MAX 99

void heapify(int n, int minHeap[]);
int deleteMin(int n, int minHeap[]);
void heapSort(int n, int minHeap[]);
void precDown(int n, int i, int minHeap[]);

int main(int argc, const char * argv[]) {
    int minHeap[MAX];
    int temp;  // check input is valid
    int n = 0; // # of keys
    while(1){
        scanf("%d", &temp);
        if(n > MAX){
            printf("error! out of index\n");
            return 0;
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
                minHeap[n] = temp;
                n++;
            }
        }
    }
    
    heapSort(n, minHeap);
    
    // print sorted array
    for(int i = 0; i < n; i++) {
        printf("%d ", minHeap[i]);
    }printf("\n");
    
    return 0;
}

// call precDown() n/2 to 0 (parent nodes)
void heapify(int n, int minHeap[]){
    for (int i = n/2; i > 0; i--) {
        precDown(i, n, minHeap);
    }
}
void precDown(int i, int n, int minHeap[]){
    int child = 0;
    int temp;
    for(temp = minHeap[i-1]; i*2 <= n; i = child){
        child = i*2;
        // compare children
        if(child != n && minHeap[i*2] < minHeap[i*2-1]){
            child++;
        }
        // compare with parent
        if(temp > minHeap[child-1]){
            minHeap[i-1] = minHeap[child-1];
        }
        else break;
    }
    minHeap[i-1] = temp;
}
int deleteMin(int n, int minHeap[]){
    int min = minHeap[0];
    // insert last node's value into first node
    minHeap[0] = minHeap[n-1];
    heapify(n, minHeap);
    return min;
}
void heapSort(int n, int minHeap[]){
    heapify(n, minHeap);
    for(int i = 0; n > 0; i++) {
        // Put min element at the end of the list.
        minHeap[n-1] = deleteMin(n, minHeap);
        // remove last node
        n--;
    }
}
