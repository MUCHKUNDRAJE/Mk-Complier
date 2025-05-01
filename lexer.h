#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

Token *tokenize(const char *src);
void printTokens(Token *head);
void freeTokens(Token *head);

#endif

