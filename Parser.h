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
static void parseConditonal();
static void parseElse();
static void parseExpression();
static bool parseOperations();
static void parsePrint();
static void parserFor();



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
    exit(1);
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

    printf("Compiling Success!\n\n\n\n!");
}

static void parseBlock()
{
    consume(Token_LEFT_BRACE, "Expected a '{'.");
    int depth = 1;  // Reset for every block

    while (!atEnd())
    {
        if (peek().type == Token_RIGHT_BRACE)
        {
            depth--;
            consume(Token_RIGHT_BRACE, "Expected a closing brace \'}\'.");
            if (depth == 0) return;
        }
        else if (peek().type == Token_LEFT_BRACE) 
        {
            depth++;
            forward();  // Consume '{' when detected
        }
        else
        {
            parseStatements();
        }
    }

    if (depth != 0)
    {
        error("Unmatched '{': Missing '}'.");
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
        parseConditonal();
        break;

    case Token_PRINT:
        parsePrint();
        break;

    case Token_FOR:
        parserFor();
        break;
    case Token_EOF:
        forward();
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
   if (!(typeMatch(Token_Number) || typeMatch(Token_STRING) || typeMatch(Token_IDENTIFIER)))
   {
        error("Not A valid value!");
   }
   else
   {
        if (parseOperations())
        {
            parseValue();
        }
        return;
   }


   
}


static void parseConditonal()
{
    consume(Token_IF, "Expected 'if' keyword");
    parseValue();
    parseExpression();
    parseValue();
    parseBlock();

    if (peek().type == Token_ELSE) // Fix: Check `peek()`, not `peekNext()`
    {
        parseElse();
    }
}



static void parseElse()
{
    consume(Token_ELSE, "Expected 'else' keyword");
    parseBlock();
}

static void parseExpression()
{
    if (!(typeMatch(Token_BANG_EQUALS) || typeMatch(Token_EQUALITY) || typeMatch(Token_GREATER) || typeMatch(Token_GREATER_EQUAL) || typeMatch(Token_LESS) || typeMatch(Token_LESS_EQUAL)))
    {
        error("Not A valid expression!");
    }
    
}

static bool parseOperations()
{
    if (_match(Token_PLUS) || _match(Token_MINUS) || _match(Token_SLASH) || _match(Token_STAR))
    {
        consume(peek().type, "Invalid Opeartion");
        return true;
    }
    
    return false;
}


static void parsePrint()
{
    consume(Token_PRINT, "Expected the keyword Print");
    if (peek().type == Token_IDENTIFIER )
    {
        consume(Token_IDENTIFIER, "Expected a proper Identifer Value");
    }
    else parseValue();

    consume(Token_SEMICOLON, "Expected a semicolon at the end of expression");
}

static void parserFor()
{
    consume(Token_FOR, "Expected the \"for\" keyword");
    
    // Initialization (optional variable assignment)
    if (peek().type == Token_IDENTIFIER)
    {
        if (peekNext().type == Token_ASSIGNMENT)
        {
            parseAssignment();  // Handle variable initialization
        } 
        else 
        {
            consume(Token_IDENTIFIER, "Expected a variable for loop condition");
            consume(Token_SEMICOLON, "Expected a semicolon after initialization");
        }
    }

    

    // Condition
    consume(Token_IDENTIFIER, "Expected a variable for loop condition");
    parseExpression();
    if ((peekNext().type == Token_IDENTIFIER))
        consume(Token_IDENTIFIER, "Expected a variable for loop comparison");
    else
        parseValue();
    
    consume(Token_SEMICOLON, "Expected a semicolon after condition");

    // Update step (identifier expected, followed by an update operation)
    consume(Token_IDENTIFIER, "Expected an identifier for the loop update");
    if (peek().type == Token_INCREMENT || peek().type == Token_DECREMENT)
    {
        forward();  // Consume `i++` or `i--`
    }
    else 
    {
        error("Expected increment (++) or decrement (--) operation in for loop");
    }

    // Loop Body
    parseBlock();  // Parse the block containing loop statements
}


