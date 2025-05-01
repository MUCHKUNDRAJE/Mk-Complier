#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "tokens.h"

ASTNode* parseTokens(Token* tokens);

#endif
