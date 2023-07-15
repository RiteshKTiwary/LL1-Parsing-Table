/* Step 3 */

#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_LENGTH 100

void outputFirstWordFromFile(const char* inputFile, const char* outputFile) {
    char words[MAX_ROWS][MAX_LENGTH];
    int num_rows = 0;

    // Open the input file
    FILE* input = fopen(inputFile, "r");
    FILE* output = fopen(outputFile, "w");
    if (input == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read words from the file
    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), input) != NULL && num_rows < MAX_ROWS) {
        // Extract the first word from each line
        sscanf(line, "%s", words[num_rows]);
        num_rows++;
    }
    // Output the first word from each row
    for (int i = 0; i < num_rows; i++) {
        fprintf(output, "%s\n", words[i]);
    }

    // Close the file
    fclose(input);
    fclose(output);

    
}

int main() {
    // Example usage
    const char* inputFile = "outputs2.txt";
    const char* outputFile = "non_terminal_list.txt";

    outputFirstWordFromFile(inputFile, outputFile);

    printf("Input file has been updated. Please check the output file.\n\n\n");

    return 0;
}
