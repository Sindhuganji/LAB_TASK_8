#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    char data;
    int freq;
    struct Node *left,*right;
} NODE;
typedef struct Heap{
    int capacity;
    int size;
    NODE ** Array;
} HEAP;
NODE* CreateNode(char ch,int f){
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = ch;
    newnode->freq = f;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
HEAP* CreateHeap(int capacity) {
    HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
    heap->capacity = capacity;
    heap->size = 0;
    heap->Array = (NODE**)malloc(capacity * sizeof(NODE*));
    return heap;
}
void MinHeapify(HEAP* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < heap->size && heap->Array[left]->freq < heap->Array[smallest]->freq) {
        smallest = left;
    }
    if (right < heap->size && heap->Array[right]->freq < heap->Array[smallest]->freq) {
        smallest = right;
    }
    if (smallest != idx) {
        NODE* temp = heap->Array[smallest];
        heap->Array[smallest] = heap->Array[idx];
        heap->Array[idx] = temp;
        MinHeapify(heap, smallest);
    }
}
void Insert(HEAP* heap, NODE* node) {
    if (heap->size == heap->capacity) {
        return; 
    }
    heap->Array[heap->size] = node;
    heap->size++;
}
NODE* Extract(HEAP* heap) {
    if (heap->size == 0) {
        return NULL;
    }
    NODE* minNode = heap->Array[0];
    heap->Array[0] = heap->Array[heap->size - 1];
    heap->size--;
    MinHeapify(heap, 0);   
    return minNode;
}
void BuildMinHeap(HEAP* heap) {
    int n = heap->size;
    for (int i = (n - 2) / 2; i >= 0; i--) {
        MinHeapify(heap, i);
    }
}
NODE* HuffmanCoding(char data[], int freq[], int size) {
    NODE *left, *right, *top;
    HEAP* heap = CreateHeap(size);
    for (int i = 0; i < size; i++) {
        Insert(heap, CreateNode(data[i], freq[i]));
    }
    BuildMinHeap(heap);
    while (heap->size > 1) {
        left = Extract(heap);
        right = Extract(heap);
        top = CreateNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        Insert(heap, top);
        BuildMinHeap(heap);
    }
    return Extract(heap);
}
void PrintCodes(NODE* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        PrintCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        PrintCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}
int main() {
    int freq[100],n;
    char ch[100];
    printf("Enter number of characters: ");
    scanf("%d",&n);
    printf("Enter characters and their frequencies:\n");
    for(int i=0;i<n;i++){
        scanf(" %c %d",&ch[i],&freq[i]);
    }
    NODE* root = HuffmanCoding(ch, freq, n);
    int arr[100], top = 0;
    printf("Character codes:\n");
    PrintCodes(root, arr, top);
    return 0;
}