#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tokens.h"


typedef struct {
    Token *tokens;
    int current;
}Parser;

Parser parser;



void initParser()
{
    parser.current = 0;
    parser.tokens = tokenList.tokens;
    
}

static void error(char* Message)
{
    printf("Error at Line: %d, Error: %s \n", parser.tokens[parser.current].line, Message);
}

static bool AtEnd()
{
    return parser.tokens[parser.current].type == Token_EOF;
}

static Token forward()
{
    return parser.tokens[parser.current++];
}

static Token peek()
{
    return parser.tokens[parser.current];
}


static bool TypeMatch(TokenType type)
{
    if ( parser.tokens[parser.current].type == type)
    {
        forward();
        return true;
    }
    
    return false;
}

static Token consume(TokenType type, char* Message)
{
    if (TypeMatch(type))
    {
        return parser.tokens[parser.current-1];
    }

    error(Message);
    exit(1);
    
}