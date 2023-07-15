#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

int main() {
    const char* inputFile1 = "distinct_terminal_list.txt";
    const char* inputFile2 = "distinct_non_terminal_list_without_count.txt";
    const char* outputFile = "listWithFlagAndIndex.txt";

    FILE* input1 = fopen(inputFile1, "r");
    FILE* input2 = fopen(inputFile2, "r");
    FILE* output = fopen(outputFile, "w");

    if (input1 == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 0;
    }

    char word[MAX_WORD_LENGTH];
    char listOfStrings[100][100];
    int index = 1;
    int count = 0;
    int flag = 0;
    int p;

    while (fgets(word, MAX_WORD_LENGTH, input1) != NULL) {

            word[strcspn(word, "\n")] = '\0';  // Remove newline character

            strncpy(listOfStrings[count], word, MAX_WORD_LENGTH);
            count++;

    }

    int m;
    int found = 0;
    for (int i = 0; i < count; i++ ){
        if(strcmp(listOfStrings[i],"epsilon")==0) {
            fprintf(output,"%d\t0\tepsilon\n",index);
            m = i;
            index++;
            found = 1;
        }
    }
    for (int i = 0; i < count; i++ ){

        if (i < m){
            // Write index column
            fprintf(output, "%d\t", index);

            //Write flag column for non-terminals
            fprintf(output,"1\t");

            fprintf(output, "%s\n", listOfStrings[i]);
        }
        else  if (i > m){
            // Write index column
            fprintf(output, "%d\t", index-found);

            //Write flag column for non-terminals
            fprintf(output,"1\t");

            fprintf(output, "%s\n", listOfStrings[i]);

        }
        index++;
    }

    while (fgets(word, MAX_WORD_LENGTH, input2) != NULL) {
    
        word[strcspn(word, "\n")] = '\0';  // Remove newline character

        // Write index column
        fprintf(output, "%d\t", index-found);

        //Write flag column for non-terminals
        fprintf(output,"2\t");

       fprintf(output, "%s\n", word);

        index++;
        count++;
    }

    fclose(input1);
    fclose(input2);
    fclose(output);

    printf("Output file created successfully.\n");

    return 0;
}
