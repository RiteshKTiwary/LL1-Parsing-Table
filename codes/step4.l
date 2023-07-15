%{  /* Step 4 */
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>

    #define MAX_ROWS 100
    #define MAX_LENGTH 100

    int numProduction = 0;

%}

delim		[ \t\n]
ws		    {delim}+
producer    "-> "
endMarker   ";\n"
id          [A-Za-z]+[0-9]*               
%%

{endMarker}     {numProduction++;}
{producer}      {}
{ws}            {fprintf(yyout,"\n");}
{id}|\'.\'      {fprintf(yyout, "%s", yytext);}
%%
int yywrap(){}

int main() {
    
    FILE *input_file = fopen("outputs2.txt", "r");
    if (!input_file) {
        printf("Failed to open input file.\n");
        return 1;
    }
    
    FILE *output_file = fopen("Id_list.txt", "w");
    if (!output_file) {
        printf("Failed to open output file.\n");
        fclose(input_file);
        return 1;
    }

    yyin = input_file;
    yyout = output_file;
    
    yylex();

    // fprintf(output_file,"%d\n",numSymbol);
    // fprintf(output_file,"%d\n",numProduction);

    char words[MAX_ROWS][MAX_LENGTH];
    int num_rows = 0;

    fclose(input_file);
    fclose(output_file);

    FILE* input = fopen("outputs2.txt","r");
    if (!input) {
        printf("Failed to open input file.\n");
        return 1;
    }
    FILE* output = fopen("non_terminal_list.txt", "w");
    if (!output) {
        printf("Failed to open output file.\n");
        fclose(input);
        return 1;
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), input) != NULL && num_rows < MAX_ROWS) {
        // Extract the first word from each line
        sscanf(line, "%s", words[num_rows]);
        num_rows++;
    }
    // fprintf(output, "%d\n",num_rows);
    // Output the first word from each row
    for (int i = 0; i < num_rows; i++) {
        fprintf(output, "%s\n", words[i]);
    }

    fclose(input);
    fclose(output);

    printf("Input file has been updated. Please check the output file.\n\n\n");
    return 0;
}
