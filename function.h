#include <stdbool.h>

struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
};

void encodeChar(struct Node* root, int arr[], int top, char c, char **out);
int decodeChar(struct Node* root, int arr[], int top, char bin[], char **out);
void freeHuffmanTree(struct Node* root);
void HuffmanCodes(char data[], unsigned freq[], int size, char input[], bool code, char **out);
char* mainFunction(bool english, bool encode, char input[]);