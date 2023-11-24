#include <stdio.h>
#include <ctype.h>
#include "huffman.h"

int main()
{
    int language;
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    unsigned freqFR[] = {815, 97, 315, 373, 1739, 112, 97, 85, 731, 45, 2, 569, 287, 712, 528, 280, 121, 664, 814, 722, 638, 164, 3, 41, 28, 15};
    unsigned freqEN[] = {808, 167, 318, 399, 1256, 217, 180, 527, 724, 14, 63, 404, 260, 738, 747, 191, 9, 642, 659, 915, 279, 100, 189, 21, 165, 7};
    int size = sizeof(data) / sizeof(data[0]);
    char filename[50];

    printf("Hello, please choose a language:\n   [0] for English\n   [1] for French\n");
    scanf("%d", &language);
    if (language != 0 && language != 1)
    {
        while (language != 0 && language != 1)
        {
            printf("Oops, your choice is not correct, please try again: ");
            scanf("%d", &language);
        }
    }

    printf("Please enter a filename to translate:\n");
    scanf("%s", filename);

    printf("Huffman Codes:\n");
    if (language == 0)
    {
        HuffmanCodes(data, freqEN, size, filename);
    }
    else if (language == 1)
    {
        HuffmanCodes(data, freqFR, size, filename);
    }

    return 0;
}