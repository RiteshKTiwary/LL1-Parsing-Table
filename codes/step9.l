%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_SIZE 100
    int idCount = 0;
    int n;
    char idList[100][100];
    typedef struct data{
        int index;
        int flag;
        char id[MAX_SIZE];
    } Data;

%}

delim       [ \n\t]
ws          {delim}+
end_marker  " ;"
producer    "-> "
id1          [A-Za-z]+[0-9]*
id2          [@#$%^&*-_+=<>?/]


%%
{producer}              {}
{end_marker}            {}
{id1}|{id2}|\[|\]|\(|\)|\{|\}|\\|\||\:|\"|\'      {
                            for (int j = 1; j <= n; j++){
                                 if(strcmp(yytext,idList[j])==0){
                                     fprintf(yyout,"%d ",j);
                                     break;
                                 }
                            };
                            idCount++;
                        }
\n                      { fprintf(yyout," %d\n", idCount-1); idCount = 0; } // numRHS = total - 1
.                       {}


%%
int yywrap(){}

int main() {

    FILE* idListFile = fopen("distinct_id_list.txt", "r");
    if (idListFile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    fscanf(idListFile, "%d", &n);

    fclose(idListFile);


    FILE* listFile = fopen("listWithFlagAndIndex.txt", "r");
    if (listFile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    Data* data = (Data*)malloc(n * sizeof(Data));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(listFile);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fscanf(listFile, "%d %d %s", &data[i].index, &data[i].flag, data[i].id);
        strcpy(idList[i+1],data[i].id);
    }

    fclose(listFile);
    
    FILE *graFile = fopen("outputs2.txt", "r");
    if (graFile == NULL) {
         printf("Error opening input file.");
        return 0;
    }

    FILE *graIntFile = fopen("convertedToInt.txt", "w");
    if (graIntFile == NULL) {
         printf("Error opening output file.");
         fclose(graFile);
        return 0;
    }
    yyin = graFile;
    yyout = graIntFile;

    yylex();

    fclose(graFile);
    fclose(graIntFile);

    free(data);  // Free the allocated memory
    return 0;
}