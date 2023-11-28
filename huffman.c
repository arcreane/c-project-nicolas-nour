#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int StringSize = 1000;

// Structure for a Huffman tree node
struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
};

// Structure for a priority queue to hold Huffman tree nodes
struct PriorityQueue {
    unsigned size;
    unsigned capacity;
    struct Node **array;
};

// Function to create a new Huffman tree node
struct Node* newNode(char data, unsigned freq) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Function to create a priority queue of given capacity
struct PriorityQueue* createQueue(unsigned capacity) {
    struct PriorityQueue* queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = (struct Node**)malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

// Function to swap two nodes of a priority queue
void swapNode(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify a subtree with the root at given index
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

// Function to check if the size of the queue is 1
int isSizeOne(struct PriorityQueue* queue) {
    return (queue->size == 1);
}

// Function to extract the node with the smallest frequency from the priority queue
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

// Function to print the Huffman codes from the root of the Huffman tree
void printCodes(struct Node* root, int arr[], int top) {
    // Assign 0 to the left edge and 1 to the right edge in the codes array
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If the leaf node is reached, print the character and its code
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void encodeChar(struct Node* root, int arr[], int top, char c) {
    if (root->left) {
        arr[top] = 0;
        encodeChar(root->left, arr, top + 1, c);
    }

    if (root->right) {
        arr[top] = 1;
        encodeChar(root->right, arr, top + 1, c);
    }

    if (!(root->left) && !(root->right)) {
        if (c == root->data) {
            for (int i = 0; i < top; ++i) {
                printf("%d", arr[i]);
            }
        }
    }
}

void encodeText(struct Node* root, int arr[], int top, char filename[]) {
    FILE *file;
    char ch;
    file = fopen(filename, "r");
    while ((ch = fgetc(file)) != EOF) {
        encodeChar(root, arr, top, ch);
    }
}

int decodeChar(struct Node* root, int arr[], int top, char bin[]) {
    int res;
    int temp;

    if (root->left) {
        arr[top] = 0;
        res = decodeChar(root->left, arr, top + 1, bin);
    }

    if (root->right) {
        arr[top] = 1;
        temp = decodeChar(root->right, arr, top + 1, bin);
        if (res != 1) res = temp;
    }

    if (!(root->left) && !(root->right)) {
        char* str = malloc(StringSize);
        memset(str, 0, StringSize);
        for (int i = 0; i < top; ++i) {
            char ch = (char)(arr[i] + 48);
            strncat(str, &ch, 1);
        }
        if (strcmp(bin, str) == 0) {
            printf("%c", root->data);
            return 1;
        }
        return 0;
    }
    return res;
}

void decodeText(struct Node* root, int arr[], int top, char filename[]) {
    FILE *file;
    char ch;
    int res;
    file = fopen(filename, "r");
	fseek(file, 0L, SEEK_END);
	int sz = ftell(file);
    char* bin = (char*) malloc(sz);
    memset(bin, 0, sz);
	fseek(file, 0L, SEEK_SET);
    while ((ch = fgetc(file)) != EOF) {
        strncat(bin, &ch, 1);
        res = decodeChar(root, arr, top, bin);
        if (res == 1) bin[0] = '\0';
    }
}

// Function to build Huffman codes and print them
void HuffmanCodes(char data[], unsigned freq[], const int size, char filename[], char code) {
    // Build the Huffman tree
    struct Node* root = buildHuffmanTree(data, freq, size);

    // Create an array to store Huffman codes
    int* arr= (int*)malloc(size*sizeof(int));
    int top = 0;

    // Print the Huffman codes
    //printf("Huffman Codes:\n");
    //printCodes(root, arr, top);

    printf("Output:\n");
    if (code == 'a') { // Translate the text from the inputed file
        encodeText(root, arr, top, filename);
    }
    else {
        decodeText(root, arr, top, filename);
    }

    // Clean up memory
    free(root);
}