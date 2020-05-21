//
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
    int Direction;
    char Element;
}Element;

Element** Create_Table(int x, int y);
void LCS_Len(char* x, char* y, Element** table);
void Print_LCS(Element** table, char* x, int i, int j);

int main(int argc, const char * argv[]) {
    FILE *fi = fopen("./input2-2.txt", "r");
    char* x = malloc(MAX+1);
    char* y = malloc(MAX+1);
    fgets(x, MAX, fi);
    fgets(y, MAX, fi);
    
    Element** table = Create_Table((int)strlen(x), (int)strlen(y));
    LCS_Len(x, y, table);
    Print_LCS(table, x, (int)strlen(x)-1, (int)strlen(y)-1);
    printf("\n");
    fclose(fi);
    
    return 0;
}

Element** Create_Table(int x, int y){
    Element** table = malloc(sizeof(struct _Element) * x);
    for(int i = 0; i < x; i++){
        table[i] = malloc(sizeof(struct _Element) * y);
        table[i][0].Element = 0;
        table[i][0].Direction = NONE;
    }
    for(int i = 0; i < y; i++){
        table[0][i].Element = 0;
        table[0][i].Direction = NONE;
    }
    return table;
}
void LCS_Len(char* x, char* y, Element** table){
    int x_len = (int)strlen(x) - 1;
    int y_len = (int)strlen(y) - 1;
    
    for(int i = 0; i < x_len; i++){
        for(int j = 0; j < y_len; j++){
            if(x[i] == y[j]){
                table[i+1][j+1].Element = table[i][j].Element + 1;
                table[i+1][j+1].Direction = DIAGONAL;
            }
            else if(table[i][j+1].Element >= table[i+1][j].Element){
                table[i+1][j+1].Element = table[i][j+1].Element;
                table[i+1][j+1].Direction = UP;
            }
            else{
                table[i+1][j+1].Element = table[i+1][j].Element;
                table[i+1][j+1].Direction = LEFT;
            }
        }
    }
}

void Print_LCS(Element** table, char* x, int i, int j){
    if(i == 0 || j == 0){
        return;
    }
    if(table[i][j].Direction == DIAGONAL){
        Print_LCS(table, x, i-1, j-1);
        printf("%c",x[i-1]);
    }
    else if(table[i][j].Direction == UP){
        Print_LCS(table, x, i-1, j);
    }
    else if(table[i][j].Direction == LEFT){
        Print_LCS(table, x, i, j-1);
    }
}
