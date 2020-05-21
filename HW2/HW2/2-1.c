//
//  2-1.c
//  HW2
//  Rod Cutting
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void BottomUpCutRod(int* costs, int length, int* r, int* s);
int* CreateArray(int length);

int main(int argc, const char * argv[]) {
    FILE *fi = fopen("./input2-1.txt", "r");
    int length;
    fscanf(fi, "%d\n", &length);
    if(length > 100 || length < 1){
        printf("error: out of range\n");
        return 0;
    }
    int* costs = (int*)malloc(sizeof(int)*(length+1));
    
    char temp = 0;
    costs[0] = 0;
    int i = 1;
    while(temp != '\n'){
        int cost;
        fscanf(fi, "%d", &cost);
        costs[i++] = cost;
        temp = fgetc(fi);
    }
    int* MaxCost = CreateArray(length);
    int* MaxLen = CreateArray(length);
    
    BottomUpCutRod(costs, length, MaxCost, MaxLen);
    
    printf("%d\n",MaxCost[length]);
    while(length > 0) {
        printf("%d ",MaxLen[length]);
        length -= MaxLen[length];
    }
    
    fclose(fi);
    free(costs);
    return 0;
}

void BottomUpCutRod(int* costs, int length, int* MaxCost, int* MaxLen){
    int q;
    for(int i = 1; i <= length; i++){
        q = INT_MIN;
        for(int j = 1; j <= i; j++){
            if(q < costs[j] + MaxCost[i-j]){
                q = costs[j] + MaxCost[i-j];
                MaxLen[i] = j;
            }
        }
        MaxCost[i] = q;
    }
}

int* CreateArray(int length){
    int* arr = (int*)malloc(sizeof(int)*(length+1));
    arr[0] = 0;
    return arr;
}
