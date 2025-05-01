#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "ast.h"


char * readSourceFile(const char * filename)
{
    FILE *file = fopen(filename , "r");
    if (!file)
    {
        perror("could not Found File ");
        exit(EXIT_FAILURE);
    }
  
     fseek(file , 0 , SEEK_END);
     long fileSize = ftell(file);
     rewind(file);

     char * sourceCode = (char*) malloc(fileSize + 1);

     if (!sourceCode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    fread(sourceCode,1,fileSize,file);
    sourceCode[fileSize] = '\0';
    fclose(file);
    return sourceCode;
}

void writeSourceCode(const char *filename ,const char * code)
{
    FILE *file = fopen(filename,"w");

    if (!file) {
        perror("Could not open file to write");
        exit(EXIT_FAILURE);
    }

    fprintf(file,"  %s ", code);
    fclose(file);    
}



int main() {



    const char* fileName = "../main.muchku";

    char* sourceCode = readSourceFile(fileName);
       
    Token* tokens = tokenize(sourceCode);
     
    // printTokens(tokens);
    ASTNode* ast = parseTokens(tokens);
    
    char * generateCode = generateCCode(ast); 

    const char* outputfile = "output.c";
    writeSourceCode(outputfile, generateCode); 
    // printf("Output:\n ");
    system("gcc output.c -o output.exe");
    system(".\\output.exe");
   

    return 0;
}
