#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "tokens.h"

Token *createToken(TokenType type, const char *value)
{
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

void addToken(Token **head, Token *newToken)
{
    if (*head == NULL)
    {
        *head = newToken;
    }
    else
    {
        Token *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newToken;
    }
}

int isKeyWord(const char *word)
{
    return strcmp(word, "let") == 0 || strcmp(word, "print") == 0;
}

Token *tokenize(const char *src)
{
    Token *head = NULL;
    int i = 0;
    int len = strlen(src);
    char buffer[256];

    while (i < len)
    {
        if (isspace(src[i]))
        {
            i++;
            continue;
        }

        if (isalpha(src[i]))
        {
            int j = 0;
            while (isalnum(src[i]))
            {
                buffer[j++] = src[i++];
            }
            buffer[j] = '\0';
            if (strcmp(buffer, "let") == 0)
                addToken(&head, createToken(TOKEN_LET, buffer));
            else if (strcmp(buffer, "print") == 0)
                addToken(&head, createToken(TOKEN_PRINT, buffer));
            else if(strcmp(buffer, "if") == 0)   {
                addToken(&head, createToken(TOKEN_IF, buffer));
            } 
            else if(strcmp(buffer, "is") == 0)   {
                addToken(&head, createToken(TOKEN_IS, buffer));
            }   else if(strcmp(buffer, "than") == 0)   {
                addToken(&head, createToken(TOKEN_THAN, buffer));
            }   
            else if(strcmp(buffer, "more") == 0)   {
                addToken(&head, createToken(TOKEN_GREAT, buffer));
            }  
            else if(strcmp(buffer, "less") == 0)   {
                addToken(&head, createToken(TOKEN_LESS, buffer));
            }
            else if(strcmp(buffer, "else") == 0)   {
                addToken(&head, createToken(TOKEN_ELSE, buffer));
            } 
            else if(strcmp(buffer, "for") == 0)   {
                addToken(&head, createToken(TOKEN_FOR, buffer));
            } else if(strcmp(buffer, "starts") == 0)   {
                addToken(&head, createToken(TOKEN_START, buffer));
            } else if(strcmp(buffer, "form") == 0)   {
                addToken(&head, createToken(TOKEN_FORM, buffer));
            } else if(strcmp(buffer, "to") == 0)   {
                addToken(&head, createToken(TOKEN_TO, buffer));
            }
            else
                addToken(&head, createToken(TOKEN_IDENTIFIER, buffer));
            continue; 
        }

        if (isdigit(src[i]))
        {
            int j = 0;
            while (isdigit(src[i]))
            {
                buffer[j++] = src[i++];
            }
            buffer[j] = '\0';
            addToken(&head, createToken(TOKEN_NUMBER, buffer));
            continue;
        }

        if (src[i] == '"') {
            i++; 
            int j = 0;
            while (i < len && src[i] != '"') {
                buffer[j++] = src[i++];
            }
            buffer[j] = '\0';
            i++; // skip closing quote
            addToken(&head, createToken(TOKEN_STRING, buffer));
            continue;
        }
        

        switch (src[i])
        {
        case '=':
            addToken(&head, createToken(TOKEN_ASSIGN, "="));
            break;
        case '(':
            addToken(&head, createToken(TOKEN_LPAREN, "("));
            break;
        case ')':
            addToken(&head, createToken(TOKEN_RPAREN, ")"));
            break;
        case ';':
            addToken(&head, createToken(TOKEN_SEMICOLON, ";"));
            break;
        case '+':
           addToken(&head , createToken(TOKEN_PLUS, "+"));
        break;
        case '-':
        addToken(&head , createToken(TOKEN_SUB, "-"));
        break; 
        case '*':
        addToken(&head , createToken(TOKEN_MUl, "*"));
        break;     
        default:
            buffer[0] = src[i];
            buffer[1] = '\0';
            addToken(&head, createToken(TOKEN_UNKNOWN, buffer));
        }
        i++;
    }
    return head;
}

void printTokens(Token *head)
{
    Token *temp = head;
    while (temp != NULL)
    {
        printf("Token Type: %d, Value: %s\n", temp->type, temp->value);
        temp = temp->next;
    }
}

void freeTokens(Token *head)
{
    Token *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}