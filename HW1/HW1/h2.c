// 1-2
// merge sorted lists by heap sort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_STR 600
#define MAX 100

typedef struct _Element{
    int Line;
    int Element;
}Element;

typedef struct _Heap{
    int Capacity;
    int Size;
    Element *Key;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap* heap, int value, int line);
Element DeleteMin(Heap* heap, int** lists);
void Heapify(Heap* heap);
void PrecDown(Heap* heap, int i);

int main(int argc, const char * argv[]) {
    FILE *fp = fopen("./input1-2.txt", "r");
    int num;
    char input_node[MAX_STR];
    char* token;
    Element Min;
    
    fgets(input_node, MAX, fp);
    num = atoi(input_node);
    
    if(num >= MAX || num < 0){
        printf("error! out of index\n");
        return 0;
    }
    
    // Dynamic allocation of double pointers to store lists lines
    int** lists = (int**)malloc(sizeof(int*)*num);
    // Save index of elements in the list to put in the heap
    int* index = (int*)malloc(sizeof(int)*num);
    
    for(int i = 0; i < num; i++){
        fgets(input_node, MAX_STR, fp);
        lists[i] = (int*)malloc(sizeof(int)*MAX);
        token = strtok(input_node, " ");
        
        if(input_node[0] == '\n'){
            printf("line %d is empty\n", i+1);
            index[i] = 0;
            continue;
        }
        
        // index [i][0] is for len of list
        int j = 1;
        
        while(token!=NULL){
            lists[i][j] = atoi(token);
            token = strtok(NULL, " ");
            if(j == MAX){
                printf("error! out of index\n");
                return 0;
            }
            j++;
        }
        // Save # of elements of lists[i] in lists[i][0]
        lists[i][0] = j - 1;
        
        // Initialize the index to be put into heap with 1(first element of the lists)
        index[i] = 1;
    }
    
    Heap* minHeap = CreateHeap(num);
    
    // init Heap
    for (int i = 0; i < num; i++) {
        if(lists[i][0] == 0){
            minHeap->Capacity--;
            continue;
        }
        else{
            Insert(minHeap, lists[i][index[i]++], i);
        }
    }
    
    // run loop till every line is empty
    while(minHeap->Capacity){
        Heapify(minHeap);
        Min = DeleteMin(minHeap, lists);
        printf("%d ", Min.Element);
        
        if(lists[Min.Line][0] == 0){
            continue;
        }
        Insert(minHeap, lists[Min.Line][index[Min.Line]++], Min.Line);
    }
    printf("\n");
    fclose(fp);
    return 0;
}

Heap* CreateHeap(int heapSize){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if(heap == NULL){
        printf("Out of Space\n");
        return NULL;
    }
    heap->Key = (Element*)malloc(sizeof(struct _Element) * (heapSize + 1));
    if(heap->Key == NULL){
        printf("Out of Space\n");
        return NULL;
    }
    heap->Size = 0;
    heap->Capacity = heapSize;
    heap->Key[0].Line = 0;
    heap->Key[0].Element = INT_MIN;
    return heap;
}

void Insert(Heap* heap, int value, int line){
    heap->Key[++heap->Size].Element = value;
    heap->Key[heap->Size].Line = line;
}

Element DeleteMin(Heap* heap, int** lists){
    int i, Child;
    Element Min;
    Element Last;

    if(heap->Size == 0){
        printf("error! heap is empty!\n");
    }
    Min.Element = heap->Key[1].Element;
    Min.Line = heap->Key[1].Line;
    
    Last.Element = heap->Key[heap->Size].Element;
    Last.Line = heap->Key[heap->Size--].Line;
    
    for(i = 1; i * 2 <= heap->Size; i = Child){
        Child = i * 2;
        if(Child != heap->Size && heap->Key[Child + 1].Element < heap->Key[Child].Element)
            Child++;
        if(Last.Element > heap->Key[Child].Element){
            heap->Key[i].Element = heap->Key[Child].Element;
            heap->Key[i].Line = heap->Key[Child].Line;
        }
        else break;
    }
    heap->Key[i].Element = Last.Element;
    heap->Key[i].Line = Last.Line;
    
    // If an empty line occurs, reduce the capacity
    if(--lists[Min.Line][0] == 0){
        heap->Capacity--;
    }
    return Min;
}

void Heapify(Heap* heap){
    for (int i = heap->Size/2; i > 0; i--) {
        PrecDown(heap, i);
    }
}

void PrecDown(Heap* heap, int i){
    int Child = 0;
    
    Element temp;
    temp.Element = heap->Key[i].Element;
    temp.Line = heap->Key[i].Line;
    
    for(; i*2 <= heap->Size; i = Child){
        Child = i*2;
        if(Child != heap->Size && heap->Key[Child+1].Element < heap->Key[Child].Element){
            Child++;
        }
        if(temp.Element > heap->Key[Child].Element){
            heap->Key[i].Element = heap->Key[Child].Element;
            heap->Key[i].Line = heap->Key[Child].Line;
        }
        else break;
    }
    heap->Key[i].Element = temp.Element;
    heap->Key[i].Line = temp.Line;
}
