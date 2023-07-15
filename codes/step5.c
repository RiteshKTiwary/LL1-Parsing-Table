/* step-5 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void getDistinctStrings(const char* inputFileName, const char* outputFileName) {
    FILE *inputFile, *outputFile;
    char inputString[MAX_LENGTH];
    char distinctStrings[MAX_LENGTH][MAX_LENGTH];
    int distinctCount = 0;

    // Open input file
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return;
    }

    // Read input strings and store distinct strings
    while (fgets(inputString, MAX_LENGTH, inputFile) != NULL) {
        // Remove trailing newline character
        inputString[strcspn(inputString, "\n")] = '\0';

        // Check if the string is distinct
        int isDistinct = 1;
        for (int i = 0; i < distinctCount; i++) {
            if (strcmp(inputString, distinctStrings[i]) == 0) {
                isDistinct = 0;
                break;
            }
        }

        // If the string is distinct, store it
        if (isDistinct) {
            strcpy(distinctStrings[distinctCount], inputString);
            distinctCount++;
        }
    }

    // Close the input file
    fclose(inputFile);

    // Open output file
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        return;
    }

    fprintf(outputFile,"%d\n",distinctCount);

    // Write distinct strings to the output file
    for (int i = 0; i < distinctCount; i++) {
        fprintf(outputFile, "%s\n", distinctStrings[i]);
    }

    // Close the output file
    fclose(outputFile);

    printf("Distinct strings have been written to %s.\n", outputFileName);
}

int main() {

    const char* inputFile1 = "Id_list.txt";
    const char* outputFile1 = "distinct_id_list.txt";

    getDistinctStrings(inputFile1, outputFile1);

    const char* inputFile2 = "non_terminal_list.txt";
    const char* outputFile2 = "distinct_non_terminal_list.txt";

    getDistinctStrings(inputFile2, outputFile2);

    return 0;
}