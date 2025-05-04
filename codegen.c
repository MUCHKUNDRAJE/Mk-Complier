#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

void generateStatement(char* buffer, ASTNode* node) {
    char line[512];

    switch (node->type) {
        case AST_LET_STATEMENT:
            if (node->dataType == TYPE_STRING)
                snprintf(line, sizeof(line), "    char %s[] = \"%s\";\n", node->identifier, node->value);
            else
                snprintf(line, sizeof(line), "    int %s = %s;\n", node->identifier, node->value);
            break;
        case AST_PRINT_STATEMENT:
            snprintf(line, sizeof(line), "    printf(\"%%d\\n\", %s);\n", node->identifier);
            break;
        case AST_PRINT_STRING:
            snprintf(line, sizeof(line), "    printf(\"%%s\\n\", \"%s\");\n", node->value);
            break;
        case AST_PRINT_EXPRESSION:
            snprintf(line, sizeof(line), "    printf(\"%%s%%d\\n\", \"%s\", %s);\n", node->left, node->right);
            break;
        case AST_PRINT_STRING_EXPRESSION:
            snprintf(line, sizeof(line), "    printf(\"%%s%%s\\n\", \"%s\", %s);\n", node->left, node->right);
            break;
        case AST_SUB_STATEMENT:
            snprintf(line, sizeof(line), "    int %s = %s - %s;\n", node->identifier, node->value, node->value2);
            break;
        case AST_MUL_STATEMENT:
            snprintf(line, sizeof(line), "    int %s = %s * %s;\n", node->identifier, node->value, node->value2);
            break;
        case AST_ADD_STATEMENT:
            snprintf(line, sizeof(line), "    int %s = %s + %s;\n", node->identifier, node->value, node->value2);
            break;    
        case AST_IF_STATEMENT:
            snprintf(line, sizeof(line), "    if (%s %s %s) {\n", node->identifier, node->value, node->value2);
            strcat(buffer, line);
            if (node->body) {
                char innerLine[512];
                switch (node->body->type) {
                    case AST_PRINT_STATEMENT:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%d\\n\", %s);\n", node->body->identifier);
                        break;
                    case AST_PRINT_STRING:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s\\n\", \"%s\");\n", node->body->value);
                        break;
                    case AST_PRINT_EXPRESSION:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s%%d\\n\", \"%s\", %s);\n", node->body->left, node->body->right);
                        break;
                    case AST_PRINT_STRING_EXPRESSION:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s%%s\\n\", \"%s\", %s);\n", node->body->left, node->body->right);
                        break;
                    default:
                        innerLine[0] = '\0';
                }
                strcat(buffer, innerLine);
            }
            strcat(buffer, "    }\n");
        
        
            return;
            case AST_ELSE_STATEMENT:
            snprintf(line, sizeof(line), "    else {\n");
            strcat(buffer, line);
            if (node->body) { 
                char innerLine[512];
                switch (node->body->type) {
                    case AST_PRINT_STATEMENT:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%d\\n\", %s);\n", node->body->identifier);
                        break;
                    case AST_PRINT_STRING:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s\\n\", \"%s\");\n", node->body->value);
                        break;
                    case AST_PRINT_EXPRESSION:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s%%d\\n\", \"%s\", %s);\n", node->body->left, node->body->right);
                        break;
                    case AST_PRINT_STRING_EXPRESSION:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s%%s\\n\", \"%s\", %s);\n", node->body->left, node->body->right);
                        break;  
                    default:
                        innerLine[0] = '\0'; // Empty
                }
                strcat(buffer, innerLine);
            }
            strcat(buffer, "    }\n");
            return;

            case AST_FOR_STATEMENT:
            snprintf(line, sizeof(line), "    for(int i = %s ; i <= %s ; i++){\n" , node->value, node->value2);
            strcat(buffer, line);
            if (node->body) { 
                char innerLine[512];
                switch (node->body->type) {
                    case AST_PRINT_STATEMENT:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%d\\n\", %s);\n", node->body->identifier);
                        break;
                    case AST_PRINT_STRING:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s\\n\", \"%s\");\n", node->body->value);
                        break;
                    case AST_PRINT_EXPRESSION:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s%%d\\n\", \"%s\", %s);\n", node->body->left, node->body->right);
                        break;
                    case AST_PRINT_STRING_EXPRESSION:
                        snprintf(innerLine, sizeof(innerLine), "        printf(\"%%s%%s\\n\", \"%s\", %s);\n", node->body->left, node->body->right);
                        break;  
                    default:
                        innerLine[0] = '\0'; // Empty
                }
                strcat(buffer, innerLine);
            }
            strcat(buffer, "    }\n");
            return;

            
        default:    
            return;
    }

    strcat(buffer, line);
}

char* generateCCode(ASTNode* ast) {
    size_t bufferSize = 4096;
    char* buffer = malloc(bufferSize);
    if (!buffer) {
        perror("Allocation failed");
        exit(1);
    }

    strcpy(buffer, "#include <stdio.h>\n\nint main() {\n");

    ASTNode* current = ast;
    while (current) {
        generateStatement(buffer, current);
        current = current->next;
    }

    strcat(buffer, "    return 0;\n}\n");
    return buffer;
}
