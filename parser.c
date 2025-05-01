#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "ast.h"
#include "datatype.h"

ASTNode* createASTNode(ASTNodeType type, const char* id, const char* value, const char* value2, DataType dataType) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->identifier = id ? strdup(id) : NULL;
    node->value = value ? strdup(value) : NULL;
    node->value2 = value2 ? strdup(value2) : NULL;
    node->left = NULL;
    node->right = NULL;
    node->dataType = dataType;
    node->next = NULL;
    node->body = NULL;

    return node;
}

ASTNode* parseTokens(Token* tokens) {
    ASTNode* head = NULL;
    ASTNode* current = NULL;

    while (tokens != NULL) {
        if (tokens->type == TOKEN_LET) {
            tokens = tokens->next; // Identifier
            char* id = tokens->value;
            tokens = tokens->next; // '='
            tokens = tokens->next;

            ASTNode* letNode = NULL;

            if (tokens->type == TOKEN_STRING) {
                letNode = createASTNode(AST_LET_STATEMENT, id, tokens->value, NULL, TYPE_STRING);
                insertSymbol(id, STRING);
                tokens = tokens->next;
            } else if (tokens->type == TOKEN_NUMBER && tokens->next && tokens->next->type == TOKEN_SUB) {
                char* val1 = tokens->value;
                tokens = tokens->next->next;
                letNode = createASTNode(AST_SUB_STATEMENT, id, val1, tokens->value, TYPE_INT);
                insertSymbol(id, INT);
                tokens = tokens->next;
            }
            else if (tokens->type == TOKEN_NUMBER && tokens->next && tokens->next->type == TOKEN_MUl) {
                char* val1 = tokens->value;
                tokens = tokens->next->next;
                letNode = createASTNode(AST_MUL_STATEMENT, id, val1, tokens->value, TYPE_INT);
                insertSymbol(id, INT);
                tokens = tokens->next;
            } else if (tokens->type == TOKEN_NUMBER && tokens->next && tokens->next->type == TOKEN_PLUS) {
                char* val1 = tokens->value;
                tokens = tokens->next->next;
                letNode = createASTNode(AST_ADD_STATEMENT, id, val1, tokens->value, TYPE_INT);
                insertSymbol(id, INT);
                tokens = tokens->next;
            }
             else {
                letNode = createASTNode(AST_LET_STATEMENT, id, tokens->value, NULL, TYPE_INT);
                insertSymbol(id, INT);
                tokens = tokens->next;
            }

            if (!head) head = letNode;
            else current->next = letNode;
            current = letNode;
        } else if (tokens->type == TOKEN_PRINT) {
            tokens = tokens->next; // (
            tokens = tokens->next;

            ASTNode* printNode = NULL;

            if (tokens->type == TOKEN_STRING) {
                char* strVal = tokens->value;
                tokens = tokens->next;

                if (tokens && tokens->type == TOKEN_PLUS && tokens->next && tokens->next->type == TOKEN_IDENTIFIER) {
                    tokens = tokens->next;
                    char* id = tokens->value;

                    if (lookupType(id) == STRING)
                        printNode = createASTNode(AST_PRINT_STRING_EXPRESSION, NULL, NULL, NULL, TYPE_STRING);
                    else
                        printNode = createASTNode(AST_PRINT_EXPRESSION, NULL, NULL, NULL, TYPE_INT);

                    printNode->left = strdup(strVal);
                    printNode->right = strdup(id);
                    tokens = tokens->next;
                } else {
                    printNode = createASTNode(AST_PRINT_STRING, NULL, strVal, NULL, TYPE_STRING);
                }
            } else if (tokens->type == TOKEN_IDENTIFIER) {
                printNode = createASTNode(AST_PRINT_STATEMENT, tokens->value, NULL, NULL, TYPE_INT);
                tokens = tokens->next;
            }

            if (!head) head = printNode;
            else current->next = printNode;
            current = printNode;
        } else if (tokens->type == TOKEN_IF) {
            tokens = tokens->next; // identifier
            const char* id1 = tokens->value;
            tokens = tokens->next; // is
            tokens = tokens->next; // more/less
            char* condition = tokens->value;
            tokens = tokens->next; // then
            tokens = tokens->next; // value
            const char* id2 = tokens->value;

            const char* operator = strcmp(condition, "more") == 0 ? ">" : "<";

              
            tokens = tokens->next;
            tokens = tokens->next;

            ASTNode* ifNode = createASTNode(AST_IF_STATEMENT, id1, operator, id2, TYPE_INT);
            if (tokens->type == TOKEN_PRINT) {
                
                ASTNode* printNode = NULL;
                tokens = tokens->next;
                tokens = tokens->next;
                if (tokens->type == TOKEN_IDENTIFIER) {
                    printNode = createASTNode(AST_PRINT_STATEMENT, tokens->value, NULL, NULL, TYPE_INT);
                    tokens = tokens->next;
                } else if (tokens->type == TOKEN_STRING) {
                    printNode = createASTNode(AST_PRINT_STRING, NULL, tokens->value, NULL, TYPE_STRING);
                    tokens = tokens->next;
                }
            
                ifNode->body = printNode;
            }

            tokens = tokens->next; // Move to inner LET or PRINT

            // Support only one inner statement for now
          
            if (!head) head = ifNode;
            else current->next = ifNode;
            current = ifNode;
        }else if (tokens->type == TOKEN_ELSE) {
            tokens = tokens->next;

            ASTNode* elseNode = createASTNode(AST_ELSE_STATEMENT, NULL, NULL, NULL, TYPE_INT);
            tokens = tokens->next;
           
            if (tokens->type == TOKEN_PRINT) {
                tokens = tokens->next; // (
                tokens = tokens->next;
                ASTNode* printNode = NULL;

                if (tokens->type == TOKEN_IDENTIFIER) {
                    printNode = createASTNode(AST_PRINT_STATEMENT, tokens->value, NULL, NULL, TYPE_INT);
                    tokens = tokens->next;
                } else if (tokens->type == TOKEN_STRING) {
                    printNode = createASTNode(AST_PRINT_STRING, NULL, tokens->value, NULL, TYPE_STRING);
                    tokens = tokens->next;
                }

                elseNode->body = printNode;
            }

            // Attach to the last IF
            
                // orphan else; treat as separate node
                if (!head) head = elseNode;
                else current->next = elseNode;
                current = elseNode;
            
        }


        if (tokens) tokens = tokens->next;
    }

    return head;
}
