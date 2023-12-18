#include <stdbool.h>
#include <string.h>
#include "huffman.h"

const int StringSize = 1000;

void encodeChar(struct Node* root, int arr[], int top, char c, char **out) {
    if (root->left) {
        arr[top] = 0;
        encodeChar(root->left, arr, top + 1, c, out);
    }

    if (root->right) {
        arr[top] = 1;
        encodeChar(root->right, arr, top + 1, c, out);
    }

    if (!(root->left) && !(root->right)) {
        if (c == root->data) {
            for (int i = 0; i < top; ++i) {
                char temp = (char)arr[i] + 48;
                size_t size = strlen(*out) + strlen(&temp) + 1;
                *out = realloc(*out, size);
                strcat(*out, &temp);
            }
        }
    }
}

int decodeChar(struct Node* root, int arr[], int top, char bin[], char **out) {
    int res;
    int temp;

    if (root->left) {
        arr[top] = 0;
        res = decodeChar(root->left, arr, top + 1, bin, out);
    }

    if (root->right) {
        arr[top] = 1;
        temp = decodeChar(root->right, arr, top + 1, bin, out);
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
            size_t size = strlen(*out) + 2;
            *out = realloc(*out, size);
            (*out)[size - 2] = root->data;
            (*out)[size - 1] = '\0';
            free(str);
            return 1;
        }
        free(str);
        return 0;
    }
    return res;
}

void freeHuffmanTree(struct Node* root) {
    if (root == NULL) return;

    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);

    free(root);
}

// Main function to build the tree and encode/decode the input
void HuffmanCodes(char data[], unsigned freq[], const int size, char input[], bool code, char **out) {
    struct Node* root = buildHuffmanTree(data, freq, size); // Build the Huffman tree from specified data
    int* arr= (int*)malloc(size*sizeof(int)); // Create an array to store Huffman codes
    int top = 0;

    if (code == true) { // Translate the text from the inputed file
        for (int i = 0; i < strlen(input); i++) {
            encodeChar(root, arr, top, input[i], out);
        }
    }
    else {
        int res;
        char ch;
        int len = strlen(input);
        char* bin = (char*)malloc(len + 1);
        memset(bin, 0, len + 1);

        for (int i = 0; i < len; ++i) {
            ch = input[i];
            strncat(bin, &ch, 1);
            res = decodeChar(root, arr, top, bin, out);
            if (res == 1) {
                bin[0] = '\0';
            }
        }

        free(bin);
    }

    freeHuffmanTree(root);
}

char* mainFunction(bool english, bool encode, char input[])
{
    char data[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', '.', ',', ';', ':', '!', '?', '\'', '"', '-', '\n'};
    unsigned freqEN[] = {35, 30, 33, 26, 27, 13, 11, 25, 32, 10, 5, 15, 34, 31, 14, 28, 3, 29, 36, 37, 7, 4, 16, 2, 12, 1, 59, 42, 50, 51, 61, 47, 45, 53, 56, 8, 40, 52, 48, 57, 58, 46, 6, 54, 55, 60, 49, 41, 43, 24, 44, 9, 62, 39, 38, 17, 19, 18, 20, 22, 23, 21, 0};
    unsigned freqFR[] = {38, 17, 27, 28, 45, 15, 21, 14, 37, 12, 10, 30, 25, 35, 31, 20, 16, 33, 36, 26, 32, 18, 11, 13, 8, 9, 61, 43, 52, 53, 62, 40, 44, 41, 60, 29, 22, 54, 50, 58, 55, 49, 39, 57, 59, 51, 56, 42, 19, 34, 24, 23, 48, 46, 47, 7, 1, 2, 3, 4, 5, 6, 0};
    int size = sizeof(data) / sizeof(data[0]);
    
    char inputCleaned[strlen(input) - 1];
    strncpy(inputCleaned, input, strlen(input) - 1); // Remore unwanted characters from string
    char *output = malloc(1); // Create empty variable size string
    output[0] = '\0';

    if (english == true)
        HuffmanCodes(data, freqEN, size, inputCleaned, encode, &output);
    else
        HuffmanCodes(data, freqFR, size, inputCleaned, encode, &output);
    
    return output;
}