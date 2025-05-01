#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    TOKEN_LET, //1
    TOKEN_IDENTIFIER,//2
    TOKEN_ASSIGN,//3
    TOKEN_NUMBER,//4
    TOKEN_PRINT,//5
    TOKEN_LPAREN,//6
    TOKEN_STRING,     
    TOKEN_RPAREN,//7
    TOKEN_PLUS,
    TOKEN_SUB,
    TOKEN_MUl,
    TOKEN_LESS,
    TOKEN_GREAT,
    TOKEN_EQUAL,
    TOKEN_IS,
    TOKEN_THAN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_SEMICOLON,//8
    TOKEN_UNKNOWN//9
} TokenType;

typedef struct Token {
    TokenType type;
    char* value;
    struct Token* next;
} Token;

#endif // TOKENS_H
