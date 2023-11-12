#include <stdio.h>
#include <ctype.h>
#include "huffman.h"

int main()
{
    int language;
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    unsigned freq[] = {815, 97, 315, 373, 1739, 112, 97, 85, 731, 45, 2, 569, 287, 712, 528, 280, 121, 664, 814, 722, 638, 164, 3, 41, 28, 15};
    int size = sizeof(data) / sizeof(data[0]);

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

    printf("Huffman Codes:\n");
    HuffmanCodes(data, freq, size);

    return 0;
}