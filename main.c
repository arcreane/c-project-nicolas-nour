#include <stdio.h>
#include <ctype.h>
#include "huffman.h"

int main()
{
    char language;
    char code;
    char data[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', ','};
    unsigned freqFR[] = {2000, 815, 97, 315, 373, 1739, 112, 97, 85, 731, 45, 2, 569, 287, 712, 528, 280, 121, 664, 814, 722, 638, 164, 3, 41, 28, 15, 1, 0};
    unsigned freqEN[] = {2000, 808, 167, 318, 399, 1256, 217, 180, 527, 724, 14, 63, 404, 260, 738, 747, 191, 9, 642, 659, 915, 279, 100, 189, 21, 165, 7, 1, 0};
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