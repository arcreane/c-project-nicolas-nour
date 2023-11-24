#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
};

struct PriorityQueue {
    unsigned size;
    unsigned capacity;
    struct Node **array;
};

struct Node* newNode(char data, unsigned freq);
struct PriorityQueue* createQueue(unsigned capacity);
void swapNode(struct Node** a, struct Node** b);
void minHeapify(struct PriorityQueue* queue, int idx);
int isSizeOne(struct PriorityQueue* queue);
struct Node* extractMin(struct PriorityQueue* queue);
void insert(struct PriorityQueue* queue, struct Node* node);
struct Node* buildHuffmanTree(char data[], unsigned freq[], int size);
void printCodes(struct Node* root, int arr[], int top);
void translateChar(struct Node* root, int arr[], int top, char c);
void translateText(struct Node* root, int arr[], int top, char filename[]);
void HuffmanCodes(char data[], unsigned freq[], int size, char filename[]);