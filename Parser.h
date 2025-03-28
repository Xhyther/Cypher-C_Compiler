#pragma once

#include "Tokens.h"

typedef struct {
    Token currentToken;
    Token prevToken;
    bool hasError;
    bool panicFlag;
    const char *errorMessage;
}Parser;

Parser parser;

static void error(const char* message){
    errorAt(&parser.prevToken, message);
}

static void errorAtCurrent(const char* message){
    errorAt(&parser.currentToken, message);
}

static void errorAt(Token* token, const char* message){
    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type == Token_EOF) fprintf(stderr, " at end");
    else if (token->type == Token_ERROR) {} //Basiclly Ignore
    else fprintf(stderr, " at '%.*s'", token->length, token->start);

  fprintf(stderr, ": %s\n", message);
  parser.hasError = true;
}

static void advanceParser(){
    parser.prevToken = parser.currentToken;

    for (;;)
    {
        parser.currentToken = scanToken();
        if (parser.currentToken.type != Token_ERROR) break;
        
    }
    
}

