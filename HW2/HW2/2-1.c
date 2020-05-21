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
    // 길이 당 Cost 저장
    int* costs = CreateArray(length);
    for(int i = 1; i <= length; i++){
        int cost;
        fscanf(fi, "%d", &cost);
        costs[i] = cost;
    }
    // 각 길이 별 최대 Cost 저장
    int* MaxCost = CreateArray(length);
    // 각 길이 별 최대 Cost가 나오는 길이 저장
    int* MaxLen = CreateArray(length);
    // 상향식 방법
    BottomUpCutRod(costs, length, MaxCost, MaxLen);
    
    // Print Cut Rod Solution
    printf("%d\n",MaxCost[length]);
    while(length > 0) {
        printf("%d ",MaxLen[length]);
        length -= MaxLen[length];
    }
    
    fclose(fi);
    return 0;
}

void BottomUpCutRod(int* costs, int length, int* MaxCost, int* MaxLen){
    int max;
    // 길이 i의 MaxCost 구하기
    for(int i = 1; i <= length; i++){
        max = INT_MIN; // 계산되지 않은 값 : -∞
        // i를 j와 i-j로 나눴을 때 최대 cost가 나오는 j 구하기
        for(int j = 1; j <= i; j++){
            if(max < costs[j] + MaxCost[i-j]){
                max = costs[j] + MaxCost[i-j];
                MaxLen[i] = j;
            }
        }
        MaxCost[i] = max;
    }
}

int* CreateArray(int length){
    int* arr = (int*)malloc(sizeof(int)*(length+1));
    arr[0] = 0; // 길이가 0인 막대는 cost 0
    return arr;
}
