#ifndef AST_H
#define AST_H

typedef enum {
    AST_LET_STATEMENT,
    AST_PRINT_STATEMENT,
    AST_PRINT_STRING,
    AST_PRINT_STRING_EXPRESSION,
    AST_PRINT_EXPRESSION ,
    AST_SUB_STATEMENT,
    AST_STRING,
    AST_MUL_STATEMENT,
    AST_IF_STATEMENT,
    AST_ADD_STATEMENT,
    AST_ELSE_STATEMENT
} ASTNodeType;

typedef enum {
    TYPE_INT,
    TYPE_STRING
} DataType;


typedef struct ASTNode {
    ASTNodeType type;
    DataType dataType; 
    char* identifier;
    char* value;
    char* value2;
    char * String;
    char* left;   
    char* right;  
    struct ASTNode* next;
    struct ASTNode* body;
    struct ASTNode* elsebody ;  

} ASTNode;

#endif
