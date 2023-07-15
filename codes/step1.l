%{
    /*Step 1 */

    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>

    #define MAX_LENGTH 100

    void updateLexOutput(const char* lexOutput, const char *outputFile) {
        FILE* input = fopen(lexOutput, "r");
        FILE* output = fopen(outputFile, "w");

        if (input == NULL || output == NULL) {
            printf("Failed to open the files.\n");
            return;
        }

        char previousLine[MAX_LENGTH] = "";
        char currentLine[MAX_LENGTH];

        while (fgets(currentLine, MAX_LENGTH, input) != NULL) {
            // Remove the newline character at the end of the line
            currentLine[strcspn(currentLine, "\n")] = '\0';

            // Check if the line contains a producer
            char* producerPtr = strchr(currentLine, '-');
            if (producerPtr != NULL) {
                strcpy(previousLine, currentLine);
                fprintf(output, "%s\n", previousLine);
            } else {
                fprintf(output, "%s -> %s\n", previousLine, currentLine);
            }
        }

        fclose(input);
        fclose(output);
    }
%}

delim		[ \t\n]
ws		    {delim}+
producer    "->"
orProduction {ws}*"|"{ws}*
endMarker   {ws}*";"{ws}
id          [A-Za-z]+[0-9]*
%%

{ws}                {fprintf(yyout," ");}
{producer}          {fprintf(yyout, "%s",yytext);}
{orProduction}      {fprintf(yyout, " ;\n");}
{endMarker}         {fprintf(yyout, " ;\n");}
{id}                {fprintf(yyout, "%s",yytext);}
\'.\'               {fprintf(yyout, "%c",yytext[1]);}

%%
int yywrap(){}

int main() {
    
    FILE *input_file = fopen("grammar1.txt", "r");
    if (!input_file) {
        printf("Failed to open input file.\n");
        return 1;
    }
    
    FILE *output_file = fopen("outputs2.txt", "w");
    if (!output_file) {
        printf("Failed to open output file.\n");
        fclose(input_file);
        return 1;
    }
    
    yyin = input_file;
    yyout = output_file;
    
    yylex();
    
    const char* lexOutput = "grammar1.txt";
    const char* outputFile = "reservedOutput.txt";

    updateLexOutput(lexOutput, outputFile);
    
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}
