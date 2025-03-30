#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tokens.h"


//Core Parser Function Declarations
static void parseProgram();
static void parseBlock();
static void parseStatements();
static void parseAssignment();
static void parseValue();


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

static Token peek()
{
    return parser.tokens[parser.current];
}

static Token peekNext()
{
    return parser.tokens[parser.current + 1];
}

static bool _match(TokenType type)
{
    return peek().type == type;
    
}

static Token forward()
{
    return parser.tokens[parser.current++];
}


static bool typeMatch(TokenType type)
{
    if ( peek().type == type)
    {
        forward();
        return true;
    }
    
    return false;
}


static bool atEnd()
{
    return peek().type == Token_EOF;
}


static Token consume(TokenType type, char* Message)
{
    if (typeMatch(type))
    {
        return parser.tokens[parser.current-1];
    }

    error(Message);
    exit(1);
    
}

static void parseProgram()
{
    consume(Token_MAIN, "Expected Main function!");
    parseBlock();

    printf("Compiling Success!\n!");
}

static void parseBlock()
{
    consume(Token_LEFT_BRACE, "Expected a \' { \'.");
    int depth = 1; //for every left brace ++
    while (!atEnd())
    {
        if (peek().type == Token_RIGHT_BRACE )
        {
            depth--;
            consume(Token_RIGHT_BRACE, "Expected a closing brace: \' } \'.");
            if(depth == 0 && peekNext().type == Token_EOF) return;
        } else if (peek().type == Token_LEFT_BRACE) 
            depth++;
        
        parseStatements();
        
    }

    if (depth != 0)
    {
        error("Unmatched '{': Missing '}'");
        exit(1);
    }
     
    
    
    
}

static void parseStatements()
{
    switch (peek().type)
    {
    case Token_IDENTIFIER:
        parseAssignment();
        break;

    case Token_IF:
        parserConditonal();
        break;

    case Token_PRINT:
        /* code */
        break;

    case Token_FOR:
        /* code */
        break;
    

    default:
        forward();
       break;
    }
   
}
/////////////////////////////////USEE FORWARDDDD NOT ADVANCEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

static void parseAssignment()
{
    consume(Token_IDENTIFIER, " Expected an Identifier");
    consume(Token_ASSIGNMENT, "Expected = (assignment operator)");
    parseValue();
    consume(Token_SEMICOLON, "Expected a semi colon at every end of statement");
}

static void parseValue()
{
   if (!(typeMatch(Token_Number)  || typeMatch(Token_STRING) || typeMatch(Token_IDENTIFIER)))
   {
        error("Not A valid value!");
   }
   
    
}

