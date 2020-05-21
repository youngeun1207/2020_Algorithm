//  2-2.c
//  HW2
//  Longest Common Subsequence
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define UP 0
#define DIAGONAL 1
#define LEFT 2
#define NONE -1

typedef struct _Element{
    int Direction;  // 화살표
    int Length;     // 길이
}Element;

Element** Create_Table(int x, int y);
void LCS_Table(char* x, char* y, Element** table);
void Print_LCS(Element** table, char* x, int i, int j);

int main(int argc, const char * argv[]) {
    FILE *fi = fopen("./input2-2.txt", "r");
    // 개행문자를 고려하여 최대값 +1로 동적할당
    char* x = malloc(MAX+1);
    char* y = malloc(MAX+1);
    fgets(x, MAX, fi);
    fgets(y, MAX, fi);
    fclose(fi);
    // 이차원배열 선언 및 초기화
    Element** table = Create_Table((int)strlen(x), (int)strlen(y));
    // LCS 추적 이차원배열 만들기
    LCS_Table(x, y, table);
    // 역추적하여 LCS 출력
    Print_LCS(table, x, (int)strlen(x)-1, (int)strlen(y)-1);
    printf("\n");
    return 0;
}

Element** Create_Table(int x, int y){
    Element** table = malloc(sizeof(struct _Element) * x);
    for(int i = 0; i < x; i++){
        table[i] = malloc(sizeof(struct _Element) * y);
        // init table
        table[i][0].Length = 0;
        table[i][0].Direction = NONE;
    }
    // init table
    for(int i = 0; i < y; i++){
        table[0][i].Length = 0;
        table[0][i].Direction = NONE;
    }
    return table;
}
void LCS_Table(char* x, char* y, Element** table){
    int x_len = (int)strlen(x) - 1;
    int y_len = (int)strlen(y) - 1;
    
    for(int i = 0; i < x_len; i++){
        for(int j = 0; j < y_len; j++){
            // LCS에 해당하는 원소
            if(x[i] == y[j]){
                table[i+1][j+1].Length = table[i][j].Length + 1; // LCS 길이 증가
                table[i+1][j+1].Direction = DIAGONAL;
            }
            // 위가 왼쪽보다 크거나 같은 경우
            // 위와 왼쪽의 값이 같은 경우 위의 값을 선택해야하므로 UP 먼저 설정
            else if(table[i][j+1].Length >= table[i+1][j].Length){
                table[i+1][j+1].Length = table[i][j+1].Length;
                table[i+1][j+1].Direction = UP;
            }
            // 왼쪽이 더 큰 경우
            else{
                table[i+1][j+1].Length = table[i+1][j].Length;
                table[i+1][j+1].Direction = LEFT;
            }
        }
    }
}
void Print_LCS(Element** table, char* x, int i, int j){ // 화살표를 따라가며 재귀호출
    if(i == 0 || j == 0){
        return;
    }
    // LCS에 해당하는 원소
    if(table[i][j].Direction == DIAGONAL){
        Print_LCS(table, x, i-1, j-1);
        printf("%c",x[i-1]);
    }
    else if(table[i][j].Direction == UP){
        Print_LCS(table, x, i-1, j);
    }
    else{ // table[i][j].Direction == LEFT
        Print_LCS(table, x, i, j-1);
    }
}
