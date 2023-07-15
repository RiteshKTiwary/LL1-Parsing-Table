%{
    #include<stdio.h>
    int numProduction = 0;

%}
endMarker   ";\n"             
%%

{endMarker}     {numProduction++;}
.|\n            {}
%%
int yywrap(){}

int main() {

    FILE* input = fopen("distinct_id_list.txt","r");
    if (!input) {
        printf("Failed to open input file1.\n");
        return 1;
    }
    FILE* output = fopen("count.txt", "w");
    if (!output) {
        printf("Failed to open output file.\n");
        fclose(input);
        return 1;
    }
    int a;
    fscanf(input,"%d",&a);
    fprintf(output,"%d\n",a);
    fclose(input);
    fclose(output);

    FILE* input1 = fopen("distinct_non_terminal_list.txt","r");
    if (!input1) {
        printf("Failed to open input file2.\n");
        return 1;
    }
    FILE* output1 = fopen("count.txt", "a");
    if (!output1) {
        printf("Failed to open output file.\n");
        fclose(input);
        return 1;
    }
    int b;
    fscanf(input1,"%d",&b);
    fprintf(output1,"%d\n",b);
    fclose(input1);
    fclose(output1);
    
    FILE *input_file = fopen("outputs2.txt", "r");
    if (!input_file) {
        printf("Failed to open input file.\n");
        return 1;
    }
    
    FILE *output_file = fopen("count.txt", "a");
    if (!output_file) {
        printf("Failed to open output file.\n");
        fclose(input_file);
        return 1;
    }

    yyin = input_file;
    
    yylex();

    fprintf(output_file,"%d\n",numProduction);

    fclose(input_file);
    fclose(output_file);

    printf("Input file has been updated. Please check the output file.\n\n\n");
    return 0;
}
