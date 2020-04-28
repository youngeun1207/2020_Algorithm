// 1-3
// random pivot Quick sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000
#define MIN 3
#define INSERTION 10

int RandomPivot(int arr[], int l, int r);
int RandomPartition(int arr[], int l, int r);
void QuiskSort(int arr[], int l, int r);
void swap(int* a, int* b);
int Partition(int arr[], int l, int r);
void InsertionSort(int arr[], int n);
void PrintList(int arr[], int n, FILE *fp, float delay);

int main(int argc, const char * argv[]){
    FILE *fp = fopen("./input1-3.txt", "r");
    int arr[MAX];
    int num;
    clock_t start, end;
    float delay;
    
    if(fp == NULL){
        printf("There is no file : %s\n", argv[1]);
        exit(-1);
    }
    
    int len = 0;
    while(EOF != fscanf(fp, "%d", &num)){
        if(num < 0 || num >= 1000){
            printf("error! out of bound\n");
            return 0;
        }
        arr[len] = num;
        len++;
    }
    fclose(fp);
    if(len < MIN){
        printf("error! you must insert at least 3 numbers\n");
        return 0;
    }
    else if (len >= MAX){
        printf("error! out of index\n");
        return 0;
    }
    else{
        start = clock( );
        if(len <= INSERTION){
            InsertionSort(arr, len);
        }
        else{
            int l = 0;
            int r = len-1;
            QuiskSort(arr, l, r);
        }
    }
    end = clock( );
    delay = (float)(end - start) / CLOCKS_PER_SEC;
    FILE *fpw = fopen("./output1-3.txt", "wt");
    PrintList(arr, len, fpw, delay);
    fclose(fpw);
    return 0;
}

int RandomPartition(int arr[], int l, int r){
    int i[3];
    int count;
    count = r - l + 1;
    srand((unsigned int)time(NULL));
    if(count >= 3){
        int j = 0;
        while(j < 3){
            i[j] = l + rand() % (r - l);
            j++;
        }
        InsertionSort(i, 3);
    }
    else{
        i[1] = l + rand() % (r - l);
    }
    swap(&arr[r], &arr[i[1]]);
    return Partition(arr, l, r);
}

void QuiskSort(int arr[], int l, int r){
    int q;
    if(l < r){
        q = RandomPartition(arr, l, r);
        QuiskSort(arr, l, q-1);
        QuiskSort(arr, q+1, r);
    }
}

void InsertionSort(int arr[], int n){
    int i, j, key;
    for (j = 1; j < n; j++){
        key = arr[j];
        i = j - 1;
        while (i >= 0 && key < arr[i]){
            arr[i+1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

int Partition(int arr[], int l, int r){
    int pivot = arr[r];
    int i = l - 1;
    for (int j = l; j < r; j++){
        if(arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    
    return i+1;
}

void swap(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void PrintList(int arr[], int n, FILE* fp, float delay){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
        fprintf(fp, "%d ", arr[i]);
    }
    printf("\n%lf s\n", delay);
    fprintf(fp, "\n%lf s", delay);
}
