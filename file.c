#include "file.h"

void readFrequencyFile(int language, int frequencyFileNameSize, char *frequencyFile)
{
    int offset = language * frequencyFileNameSize; // Calculate offset to the start of the string
    char *actualFrequencyFileName = frequencyFile + offset; // Get specific string

    FILE *fptr;
    fptr = fopen(actualFrequencyFileName, "r"); // Open file in read mode

    char character;
    while ((character = fgetc(fptr)) != EOF) { // Read file character by character
        printf("%c", character);
    }

    fclose(fptr); // Close file
}