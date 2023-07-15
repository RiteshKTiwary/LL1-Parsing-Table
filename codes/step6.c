/* step-6 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

char strings[100][100];
char selectedStrings[100][100];
char remainingStrings[100][100];

static int n;
static int k;
int remainingCount=0;

int readStringsFromTwoFiles(const char* filename1, const char* filename2) {

    FILE* file1 = fopen(filename1, "r");
    if (file1 == NULL) {
        printf("Failed to open the file '%s'\n", filename1);
        return 0;
    }

    fscanf(file1, "%d", &n);
    //printf("%d\n",n);

    if (n <= 0 || n > MAX_STRINGS) {
        printf("Invalid number of strings. Exiting...\n");
        fclose(file1);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file1, "%s", strings[i]);
    }

    FILE* file2 = fopen(filename2, "r");
    if (file2 == NULL) {
        printf("Failed to open the file '%s'\n", filename2);
        return 0;
    }

    fscanf(file2, "%d",&k);
    //printf("%d\n",k);

    if (k <= 0 || k > n) {
        printf("Invalid value of k. Exiting...\n");
        fclose(file2);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        fscanf(file2, "%s", selectedStrings[i]);
    }

    fclose(file1);
    fclose(file2);
    return 1;
}

void getRemainingStrings() {

    for (int i = 0; i < n; i++) {
        int isMatch = 0;
        for (int j = 0; j < k; j++) {
            if (strcmp(strings[i], selectedStrings[j]) == 0) {
                isMatch = 1;
                break;
            }
        }

        if (!isMatch) {
            strcpy(remainingStrings[remainingCount++], strings[i]);
        }
    }
}

int main() {

    const char* fileName1 = "distinct_id_list.txt";
    const char* fileName2 = "distinct_non_terminal_list.txt";

    if (!readStringsFromTwoFiles(fileName1, fileName2)) {
        return 1;
    }

    getRemainingStrings();

    FILE *output_file = fopen("distinct_terminal_list.txt", "w");
    if (!output_file) {
        printf("Failed to open output file.\n");
        return 1;
    }
    //fprintf(output_file,"%d\n",remainingCount);
    for (int i = 0; i < remainingCount; i++) {
        fprintf(output_file,"%s\n", remainingStrings[i]);
    }

    return 0;
}
