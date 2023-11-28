#include <stdio.h>
#include <ctype.h>
#include "huffman.h"

int main()
{
    char language;
    char code;
    char data[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', '.', ',', ';', ':', '!', '?', '\'', '"', '-', '\n'};
    unsigned freqEN[] = {35, 30, 33, 26, 27, 13, 11, 25, 32, 10, 5, 15, 34, 31, 14, 28, 3, 29, 36, 37, 7, 4, 16, 2, 12, 1, 59, 42, 50, 51, 61, 47, 45, 53, 56, 8, 40, 52, 48, 57, 58, 46, 6, 54, 55, 60, 49, 41, 43, 24, 44, 9, 62, 39, 38, 17, 19, 18, 20, 22, 23, 21, 0};
    unsigned freqFR[] = {38, 17, 27, 28, 45, 15, 21, 14, 37, 12, 10, 30, 25, 35, 31, 20, 16, 33, 36, 26, 32, 18, 11, 13, 8, 9, 61, 43, 52, 53, 62, 40, 44, 41, 60, 29, 22, 54, 50, 58, 55, 49, 39, 57, 59, 51, 56, 42, 19, 34, 24, 23, 48, 46, 47, 7, 1, 2, 3, 4, 5, 6, 0};
    int size = sizeof(data) / sizeof(data[0]);
    char filename[50];

    printf("Hello, please choose a language:\n   [a] for English\n   [b] for French\n");
    scanf(" %c", &language);
    if (language != 'a' && language != 'b')
    {
        while (language != 'a' && language != 'b')
        {
            printf("Oops, your choice is not correct, please try again: ");
            scanf(" %c", &language);
        }
    }

    printf("Please enter a filename:\n");
    scanf("%s", filename);

    printf("Do you want to encode this file or decode it?\n   [a] encoding\n   [b] decoding\n");
    scanf(" %c", &code);
    if (code != 'a' && code != 'b')
    {
        while (code != 'a' && code != 'b')
        {
            printf("Oops, your choice is not correct, please try again: ");
            scanf(" %c", &code);
        }
    }

    if (language == 'a')
    {
        HuffmanCodes(data, freqEN, size, filename, code);
    }
    else if (language == 'b')
    {
        HuffmanCodes(data, freqFR, size, filename, code);
    }

    return 0;
}