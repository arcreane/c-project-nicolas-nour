#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

const int nbAscii = 128; // Number of letters in the alphabet (lowercase only exculding accents)

void getOccurence(char filename[], int characterOccurence[nbAscii])
{
    FILE *file;
    unsigned char ch;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("File not found or unable to open.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF) {
        characterOccurence[ch]++; // Increment the count for the corresponding letter
    }

    fclose(file);
}

int main() {
    char filename[100];
    int characterOccurence[nbAscii]; // Initialize an array to store the occurence of each letter (case-insensitive)
    memset(characterOccurence, 0, nbAscii*sizeof(int));

    printf("Enter the filename: ");
    scanf("%s", filename);

    getOccurence(filename, characterOccurence);

    // Display the letter count
    for (int i = 0; i < nbAscii; i++) {
        if (characterOccurence[i] > 0) {
            printf("%c: %d\n", i, characterOccurence[i]);
        }
    }

    return 0;
}
