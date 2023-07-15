/* Step 2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void updateInputFile(const char* inputFile, const char* outputFile) {
    FILE* input = fopen(inputFile, "r");
    FILE* output = fopen(outputFile, "w");

    if (input == NULL || output == NULL) {
        printf("Failed to open the files.\n");
        return;
    }

    char previousLine[MAX_LENGTH] = "";
    char trimmedCurrentLine[MAX_LENGTH] = "";
    char trimmedLine[MAX_LENGTH] = "";
    char currentLine[MAX_LENGTH];

    while (fgets(currentLine, MAX_LENGTH, input) != NULL) {
        // Remove the newline character at the end of the line
        currentLine[strcspn(currentLine, "\n")] = '\0';

        // Check if the line contains a producer
        char* producerPtr = strchr(currentLine, '>');
        if (producerPtr != NULL) {
            // calculate the length upto producerPtr
            size_t length = producerPtr - currentLine;
            char trimmedLine[length+2];
            strncpy(trimmedLine, currentLine, length+1);
            trimmedLine[length+1] = '\0';
            strcpy(trimmedCurrentLine,trimmedLine);
            strcpy(previousLine, currentLine);
            fprintf(output, "%s\n", currentLine);
        } else {
            
            fprintf(output, "%s %s\n", trimmedCurrentLine, currentLine);
        }
    }

    fclose(input);
    fclose(output);
}

int main() {
    const char* inputFile = "outputs1.txt";
    const char* outputFile = "outputs2.txt";

    updateInputFile(inputFile, outputFile);

    printf("Input file has been updated. Please check the output file.\n\n\n");

    return 0;
}
