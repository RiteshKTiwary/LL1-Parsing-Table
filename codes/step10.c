#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void modifyArray(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        int lastNonZero = 0;
        int lastIndex = -1;

        // Find the last non-zero element in the current row
        for (int j = 0; arr[i][j] > 0 && arr[i][j] < 50 && arr[i][j]; j++) {
            lastNonZero = arr[i][j];
            lastIndex = j;
        }

        // Move the last non-zero element to the second position
        if (lastIndex != -1) {
            for (int j = lastIndex; j > 1; j--) {
                arr[i][j] = arr[i][j - 1];
            }
            arr[i][1] = lastNonZero;
        }

        // Set the second element to 0 if the last non-zero element is the first element
        if (lastIndex == 0) {
            arr[i][1] = 0;
        }
    }
}

int main() {
    FILE* file = fopen("convertedToInt.txt", "r"); 

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int** arr = NULL;    // Pointer to store the 2D array
    
    int rows = 0;        // Number of rows in the array

    char line[100];      // Assuming each line contains at most 100 characters

    while (fgets(line, sizeof(line), file)) {
        int numElements = 0;
        int* row = NULL;

        char tempLine[100];
        strcpy(tempLine, line);  // Create a temporary copy of the line

        char* token = strtok(tempLine, " ");
        while (token != NULL) {
            int element = atoi(token);
            row = realloc(row, (numElements + 1) * sizeof(int));
            row[numElements++] = element;
            token = strtok(NULL, " ");
        }

        arr = realloc(arr, (rows + 1) * sizeof(int*));
        arr[rows] = row;

        rows++;
    }

    fclose(file);

    modifyArray(arr, rows);

    FILE* output = fopen("modified.txt","w");
    if (output == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    for (int i = 0; i < rows; i++){
        if (arr[i][1] != 0){
            for (int j = 0; j < arr[i][1]+2; j++){
                fprintf(output,"%d ",arr[i][j]);
            }
            fprintf(output,"\n");
        } else {
            for (int j = 0; j < 3; j++){
                fprintf(output,"%d ",arr[i][j]);
            }
            fprintf(output,"\n");
        }
    }

    fclose(output);

    // Free the allocated memory
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}