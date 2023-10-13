#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const int nbLetterAlphabet = 26; // Number of letters in the alphabet (lowercase only exculding accents)

void getOccurence(char filename[], int letterOccurence[nbLetterAlphabet])
{
    FILE *file;
    char ch;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("File not found or unable to open.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) { // Is a letter?
            ch = tolower(ch); // Convert to lowercase
            letterOccurence[ch - 'a']++; // Increment the count for the corresponding letter
        }
    }

    fclose(file);
}

int main() {
    char filename[100];
    int letterOccurence[26] = {0}; // Initialize an array to store the occurence of each letter (case-insensitive)

    printf("Enter the filename: ");
    scanf("%s", filename);

    getOccurence(filename, letterOccurence);

    // Display the letter count
    for (int i = 0; i < 26; i++) {
        if (letterOccurence[i] > 0) {
            printf("%c: %d\n", 'a' + i, letterOccurence[i]);
        }
    }

    return 0;
}
