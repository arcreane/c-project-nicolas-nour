#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

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

struct Node* newNode(char data, unsigned freq) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct PriorityQueue* createQueue(unsigned capacity) {
    struct PriorityQueue* queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = (struct Node**)malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

void swapNode(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct PriorityQueue* queue, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < queue->size && queue->array[left]->freq < queue->array[smallest]->freq)
        smallest = left;

    if (right < queue->size && queue->array[right]->freq < queue->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&queue->array[smallest], &queue->array[idx]);
        minHeapify(queue, smallest);
    }
}

int isSizeOne(struct PriorityQueue* queue) {
    return (queue->size == 1);
}

struct Node* extractMin(struct PriorityQueue* queue) {
    struct Node* temp = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    --queue->size;
    minHeapify(queue, 0);
    return temp;
}

// Function to insert a new node with a given character and frequency into the priority queue
void insert(struct PriorityQueue* queue, struct Node* node) {
    ++queue->size;
    int i = queue->size - 1;
    while (i && node->freq < queue->array[(i - 1) / 2]->freq) {
        queue->array[i] = queue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->array[i] = node;
}

// Function to build the Huffman tree and return the root
struct Node* buildHuffmanTree(char data[], unsigned freq[], int size) {
    struct Node *left, *right, *top;
    // Create a priority queue and insert all characters with their frequencies
    struct PriorityQueue* queue = createQueue(size);
    for (int i = 0; i < size; ++i)
        insert(queue, newNode(data[i], freq[i]));

    // Build the Huffman tree
    while (!isSizeOne(queue)) {
        left = extractMin(queue);
        right = extractMin(queue);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert(queue, top);
    }

    // The root of the Huffman tree is the only node left in the priority queue
    return extractMin(queue);
}
