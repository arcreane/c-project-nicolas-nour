#include <stdio.h>
#include <ctype.h>
#include "file.h"

int main()
{
    const int freqFileNameSize = 20;
    int language;
    char frequencyFile[2][20] = {"EngLetterFreq.txt", "FraLetterFreq.txt"};

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
    readFrequencyFile(language, freqFileNameSize, &frequencyFile[0][0]);

    return 0;
}