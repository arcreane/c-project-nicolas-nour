#include <stdio.h>

int main()
{
    char language;
    int frequencyFileNameSize = 17;
    char frequencyFile[frequencyFileNameSize];

    printf("Hello, please choose a language:\n   [1] for English\n   [2] for French\n");
    scanf("%c", &language);
    if (language == '1')
    {
        printf("You have chosen English.");
        frequencyFile[frequencyFileNameSize] = 'EngLetterFreq.txt';
    } else if (language == '2')
    {
        printf("You have chosen French.");
        frequencyFile[frequencyFileNameSize] = 'FraLetterFreq.txt';
    }

    return 0;
}