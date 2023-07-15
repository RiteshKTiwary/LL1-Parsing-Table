#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

char idList[100][100];

typedef struct data{
    int index;
    int flag;
    char id[MAX_SIZE];
} Data;

int productionRule[20][20];

int maxFirst = 20;
int maxFollow = 20;
int maxProd = 10;
int totalSymbols;
int numNonTerminals;
int numTerminals;
int numProductions;
int firstSet[50][20];
int followSet[40][20]; 
int parseTable[40][40][20];

int change(int variable){
    return variable * 2;
}

void findUnion(int symbol, int size1, int arr1[], int size2, int arr2[], int size3, int arr3[]) {
    int i, j;
    int count = 0;
    
    for (i = 1; i < size1; i++) {
        arr3[i] = arr1[i];
        if (arr1[i] <= totalSymbols+1) {
            count++;
        }
    }
    
    for (i = 1; i < size2; i++) {
        int found = 0;
        for (j = 1; j < size1; j++) {
            if (arr2[i] == arr1[j]) {
                found = 1;
                break;
            }
        }
        
        if (found == 0) {
            for (j = 1; j < size3; j++) {
                if (arr3[j] > totalSymbols+1) {
                    arr3[j] = arr2[i];
                    count++;
                    break;
                }
            }
        }
    }
    
    arr3[0] = count;
}

void calculateFirstSetIterative() {
    int i, j, symbol;
    int k = 0;

    // Initialize the First set matrix
    for (i = 0; i < totalSymbols; i++) {
        firstSet[i+1][0] = 0;
        for (j = 1; j < maxFirst; j++) {
            firstSet[i+1][j] = totalSymbols+3;
        }
    }
    //FIRST(terminal/epsilon) = {terminal/epsilon}
    for(symbol = 1; symbol <= numTerminals; symbol++){
        //each row of first set has first element as count of first set element of that symbol
        firstSet[symbol][0] = 1;

        firstSet[symbol][1] = symbol;
    }

    int numFirstElements = 1;
    int changes = 0;

    //Calculating FIRST set for Non Terminals iteratively
    for (int s = 0; s < numProductions; s++){

        for(symbol = numTerminals+1; symbol<= totalSymbols; symbol++){

            for(j = 0; j < numProductions; j++){

                if(symbol == productionRule[j][0]){

                    if(productionRule[j][1] > 0){

                        if (productionRule[j][2] <= numTerminals){

                            if(firstSet[symbol][0] == 0){
                                firstSet[symbol][numFirstElements++]=productionRule[j][2];
                                firstSet[symbol][0] ++;
                                changes = 1;
                            } 
                            else if (firstSet[symbol][0] > 0)
                            //finding union with FIRST set of the symbol to add in set
                            for (int m = 0; m < maxFirst; m++){
                                int found = 0;

                                for(int n = 1; n <= numFirstElements; n++){
                                    if (firstSet[symbol][n] == productionRule[j][2]){
                                        found = 1;
                                        break;
                                    }
                                }

                                if(found == 0){
                                    firstSet[symbol][numFirstElements++]=productionRule[j][2];
                                    firstSet[symbol][0]++;
                                    changes = 1;
                                }
                            }
                        }
                         //if in the production rule LHS have non-Terminal as first
                        if (productionRule[j][2] > numTerminals){
                        
                            //take union of FIRST sets of symbol and that non terminal after sorting
                            int pre = firstSet[symbol][0];
                            findUnion(symbol, maxFirst, firstSet[symbol], maxFirst, firstSet[productionRule[j][2]], maxFirst, firstSet[symbol]);
                            if(firstSet[symbol][0]!=pre) changes = 1;
                        }
                    }
                }
            }      
        }
        if (changes == 0) break;
    }
}


void calculateFollowSetIterative(){
    int i, j, symbol;
    int k = 0;

    // Initialize the Follow set matrix
    for (i = numTerminals+1; i <= totalSymbols; i++) {
        followSet[i][0] = 0;  // to give count number of elements in follow set
        for (j = 1; j < maxFollow; j++) {
            followSet[i][j] = totalSymbols+3; //rest other with value greater than total Symbols
        }
    }

    // to add EOF in followSet of start symbol
    followSet[numTerminals+1][0] = 1;
    followSet[numTerminals+1][1] = totalSymbols + 1;

    int changes = 0;
    // 1. In RHS of Production Rule, if T is followed by a NT
   for (i = 0; i < numProductions; i++){
        if (productionRule[i][1] > 1){
            for (j = 2; j <= productionRule[i][1]; j++) {
                if (productionRule[i][j] > numTerminals && productionRule[i][j+1] <= numTerminals && productionRule[i][j+1] != 0){
                    if (followSet[productionRule[i][j]][0] == 0){
                        followSet[productionRule[i][j]][0] = 1;
                        followSet[productionRule[i][j]][1] = productionRule[i][j+1];
                        changes = 1;
                    }
                    else if (followSet[productionRule[i][j]][0] > 0){
                        int found = 0; 
                        for (int k = 1; k < followSet[productionRule[i][j]][0]+1; k++){
                            if (productionRule[i][j+1] == followSet[productionRule[i][j]][k]){
                                found = 1;
                                break;
                            }
                        }
                        if (found == 0){
                            followSet[productionRule[i][j]][0]++;
                            followSet[productionRule[i][j]][followSet[productionRule[i][j]][0]] = productionRule[i][j+1];
                            changes = 1;
                        }
                    }
                }
            }
        }
   }

   changes = 0;

    // 2. In RHS of Production Rule, if NT' is followed by a NT
    for (int s = 0; s < maxFollow; s++){
        for (i = 0; i < numProductions; i++){
            if (productionRule[i][1] > 1){
                for (j = 2; j <= productionRule[i][1]; j++) {
                    if (productionRule[i][j] > numTerminals && productionRule[i][j+1] > numTerminals) {
                        int foundEpsilon = 0;
                        for (int k = j+1; k <= productionRule[i][1]+1; k++){
                            int p;
                            for (int m = 1; m < maxFirst; m++){
                                if (firstSet[productionRule[i][k]][m] == 1){
                                    p = m;
                                    foundEpsilon = 1;
                                    break;
                                }
                            }
                            // case 1:
                            if (foundEpsilon != 0){
                                int pre = followSet[productionRule[i][j]][0];
                                findUnion (productionRule[i][j], maxFollow, followSet[productionRule[i][j]], p, firstSet[productionRule[i][k]], maxFollow, followSet[productionRule[i][j]]);
                                if (followSet[productionRule[i][j]][0] != pre) changes = 1;

                                // sub-case 1:
                                if (k == productionRule[i][1]+1){
                                    int pre = followSet[productionRule[i][j]][0];
                                    findUnion(productionRule[i][j], maxFollow, followSet[productionRule[i][j]], maxFollow, followSet[productionRule[i][0]], maxFollow, followSet[productionRule[i][j]]);
                                    if (followSet[productionRule[i][j]][0] != pre) changes = 1;
                                }
                            }


                            // case 2:
                            if (foundEpsilon == 0){
                                int pre = followSet[productionRule[i][j]][0];
                                findUnion(productionRule[i][j], maxFollow, followSet[productionRule[i][j]], maxFirst, firstSet[productionRule[i][k]], maxFollow, followSet[productionRule[i][j]]);
                                if (followSet[productionRule[i][j]][0] != pre) changes = 1;
                            }
                        }
                    }

                }
            }
            // case 3:
            if (productionRule[i][productionRule[i][1]+1] > numTerminals){
                int pre = followSet[productionRule[i][productionRule[i][1]+1]][0];
                findUnion(productionRule[i][productionRule[i][1]+1], maxFollow, followSet[productionRule[i][productionRule[i][1]+1]], maxFollow, followSet[productionRule[i][0]], maxFollow, followSet[productionRule[i][productionRule[i][1]+1]]);
                if (followSet[productionRule[i][k]][0] != pre) changes = 1;
            }
        }
        if (changes == 0) break;
    }
}

void createParseTable(){

    int symT,symNT,i,j,k;
    // Initialize table
    for (i = numTerminals+1; i <= totalSymbols; i++){
        for (j = 1; j <= numTerminals+1; j++){
            for (k = 0; k < maxProd; k++){
                parseTable[i][j][k] = 0;
            }
        }
    }

    // case 1
    for (i = 0; i < numProductions; i++){
        if (productionRule[i][2] > 1 && productionRule[i][2] <= numTerminals){
            for (int m = 0; m < maxProd; m++){
                parseTable[productionRule[i][0]][productionRule[i][2]][m] = productionRule[i][m];
            }
        }
    }

    // case 2
    for (i = 0; i < numProductions; i++){
        if (productionRule[i][2] == 1){
            for (j = 1; j <= followSet[productionRule[i][0]][0]; j++){
                if (followSet[productionRule[i][0]][j] != totalSymbols+1){
                    for (int m = 0; m < maxProd; m++){
                        parseTable[productionRule[i][0]][followSet[productionRule[i][0]][j]][m] = productionRule[i][m];
                    }
                }
                else {
                    for (int m = 0; m < maxProd; m++){
                        parseTable[productionRule[i][0]][numTerminals+1][m] = productionRule[i][m];
                    }
                }
            }
        }
    }

    // case 3
    for (i = 0; i < numProductions; i++){
        if (productionRule[i][2] > numTerminals){
            int foundEpsilon = 0;
            int p;
            for (int k = 1; k < maxFirst; k++){
                if (firstSet[productionRule[i][2]][k] == 1) {
                    foundEpsilon = 1;
                    p = k;
                    break;
                }
            }
            if (foundEpsilon == 0){
                for (j = 1; j <= firstSet[productionRule[i][0]][0]; j++){
                    for (int m = 0; m < maxProd; m++){
                        parseTable[productionRule[i][0]][firstSet[productionRule[i][0]][j]][m] = productionRule[i][m];
                    }
                }
            }

            else if (foundEpsilon != 0 && p > 1){
                for (j = 1; j < p; j++){
                    for (int m = 0; m < maxProd; m++){
                        parseTable[productionRule[i][0]][firstSet[productionRule[i][0]][j]][m] = productionRule[i][m];
                    }
                }
            }
        }
    }
}


int main (){
    FILE *inputFile1 = fopen("count.txt","r");
    if (inputFile1 == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    fscanf(inputFile1, "%d", &totalSymbols);
    fscanf(inputFile1, "%d", &numNonTerminals);
    fscanf(inputFile1, "%d", &numProductions);

    FILE *inputFile = fopen("modified.txt","r");
    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    for (int i = 0; i < numProductions; i++) {
        for (int j = 0; j < 2; j++){
            fscanf(inputFile, "%d", &productionRule[i][j]);
        }
        if(productionRule[i][1] == 0){
            fscanf(inputFile, "%d", &productionRule[i][2]);
        }

        for (int j = 2; j < productionRule[i][1] + 2;j++){
            fscanf(inputFile, "%d", &productionRule[i][j]);
        }
    }
    // Close the input file
    fclose(inputFile);

    numTerminals  = totalSymbols-numNonTerminals;

    calculateFirstSetIterative();

    // for (int i = 1; i <= totalSymbols; i++){
    //     printf("%d ", i);
    //     for (int j = 0; j < maxFirst; j++){
    //         if(firstSet[i][j]<=totalSymbols){
    //             printf("%d ", firstSet[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }

    // printf("\n\n");


    calculateFollowSetIterative();

    // for (int i = numTerminals+1; i <= totalSymbols; i++){
    //     printf("%d ", i);
    //     for (int j = 0; j < maxFollow; j++){
    //         if(followSet[i][j]<=totalSymbols+2){
    //             printf("%d ", followSet[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }

    FILE* listFile = fopen("listWithFlagAndIndex.txt", "r");
    if (listFile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    Data* data = (Data*)malloc(totalSymbols+1 * sizeof(Data));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(listFile);
        return 1;
    }

    for (int i = 0; i < totalSymbols; i++) {
        fscanf(listFile, "%d %d %s", &data[i].index, &data[i].flag, data[i].id);
        strcpy(idList[i+1],data[i].id);
    }

    fclose(listFile);

     FILE* output1 = fopen("firstSet.txt","w");
    if (output1 == NULL) {
        printf("Failed to open the output1 file.\n");
        return 1;
    }

    fprintf(output1,"First Set:\n");
    for (int i = 1; i <= totalSymbols; i++){
        fprintf(output1,"FIRST(%s) = { ",idList[i]);
        for (int j = 1; j < maxFirst; j++){
            if(firstSet[i][j]<=totalSymbols){
                fprintf(output1,"%s ",idList[firstSet[i][j]]);
            }
        }
        fprintf(output1,"}\n");
    }
    
    fclose(output1);

    FILE* output2 = fopen("followSet.txt","w");
    if (output2 == NULL) {
        printf("Failed to open the output2 file.\n");
        return 1;
    }

    fprintf(output2,"Follow Set:\n");
    strcpy(idList[totalSymbols+1],"EOF");

    for (int i = numTerminals+1; i <= totalSymbols; i++){
        fprintf(output2,"FOLLOW(%s) = { ",idList[i]);
        for (int j = 1; j < maxFollow; j++){
            if(followSet[i][j]<totalSymbols+2){
                fprintf(output2,"%s ",idList[followSet[i][j]]);
            }
        }
        fprintf(output2,"}\n");
    }

    fclose(output2);

    createParseTable();

    // for (int i = 2; i <= numTerminals; i++){
    //     printf("\t\t%d",i);
    // }
    // printf ("\t\t%d",totalSymbols+1);
    // printf("\n");

    // for (int i = numTerminals+1; i <= totalSymbols; i++){
    //     printf ("%d\t",i);
    //     for (int j = 2; j <= numTerminals + 1; j++){

    //         for (int k = 0; k < maxProd; k++){  
    //             if (parseTable[i][j][k] == 0) printf(" ");
    //            else printf("%d ",parseTable[i][j][k] );
    //         }
    //         printf("\t");
    //     }
    //     printf("\n");
    // }

    FILE* grammarOutput = fopen("LL1_Parse_Table.txt","w");
    if (grammarOutput == NULL){
        printf("Error to give Output of Grammar\n");
        return 1;
    }

    for (int i = numTerminals+1; i <= totalSymbols; i++){
        for (int j = 1; j <= numTerminals + 1; j++){
            if (parseTable[i][j][0] == 0) continue;
            else if (parseTable[i][j][0] != 0){
                if (j == numTerminals+1) fprintf (grammarOutput,"{ %s EOF }:\t",idList[i]);
                else fprintf (grammarOutput,"{ %s %s }:\t",idList[i],idList[j]);
                for (int k = 0; k < maxProd; k++){
                    if (parseTable[i][j][1] != 0 && k == 1) fprintf(grammarOutput,"-> ");
                    //else if (parseTable[i][j][k] == 0) fprintf(grammarOutput," ");
                    else    fprintf(grammarOutput,"%s ",idList[parseTable[i][j][k]] );
                }
            }
            fprintf(grammarOutput,"\n");
        }
    } 

    fclose(grammarOutput);

    printf("firstSet.txt , followSet.txt and LL1_parse_table.txt has been created.\n");
}