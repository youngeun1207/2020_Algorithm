// 1-3
// random pivot Quick sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000
#define MIN 3
#define INSERTION 10

typedef struct Node* PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

struct Node{
    int Element;
    Position Next;
};

List MakeEmpty(List L);
void Insert(List L, int X, Position P);
Position FindLast(List L);
void QuickSort(List L, int l, int r);
int RandomPivot(List L);

int main(int argc, const char * argv[]){
    FILE *fp = fopen(argv[1], "r");
    Position header = NULL;
    
    int num;
    if(fp == NULL){
        printf("There is no file : %s\n", argv[1]);
        exit(-1);
    }
    header = MakeEmpty(header);
    
    while(fscanf(fp, "%d", &num) != EOF){
        Insert(header, num, FindLast(header));
        header->Element++;
    }
    if(header->Element < MIN){
        printf("error! you must insert at least 3 numbers\n");
        return 0;
    }
    else if (header->Element >= MAX){
        printf("error! out of index\n");
        return 0;
    }
    else{
        
    }
    return 0;
}

List MakeEmpty(List L)
{
    L = (List)malloc(sizeof(struct Node));
    L->Element = 0;
    L->Next = NULL;
    return L;
}

void Insert(List L, int X, Position P){
    Position TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    TmpCell->Element = X;
    P->Next = TmpCell;
    TmpCell->Next = NULL;
}

Position FindLast(List L)
{
    Position P;
    P = L->Next;
    while(P->Next != NULL)
        P = P->Next;
    return P;
}

void QuickSort(List L, int l, int r){
    RandomPivot(L);
    
}


