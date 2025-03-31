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
    printf(RED"Error at Line:" RESET  BLU" %d,"RESET  GRN"Error: %s \n"RESET, parser.tokens[parser.current].line, Message);
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
    consume(Token_MAIN, "Syntax Error: Expected 'main' function declaration.");
    parseBlock();

    printf(GRN"\n\n\nCompiling Success!!\n"RESET);
}

static void parseBlock()
{
    consume(Token_LEFT_BRACE, "Syntax Error: Expected '{' to begin block.");
    int depth = 1;  // Reset for every block

    while (!atEnd())
    {
        if (peek().type == Token_RIGHT_BRACE)
        {
            depth--;
            consume(Token_RIGHT_BRACE, "Syntax Error: Expected '}' to close block.");
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
    consume(Token_IDENTIFIER, "Syntax Error: Expected an identifier.");
    consume(Token_ASSIGNMENT, "Syntax Error: Expected '=' (assignment operator).");
    parseValue();
    consume(Token_SEMICOLON, "Syntax Error: Expected a semicolon ';' at the end of the statement.");
}

static void parseValue()
{
   if (!(typeMatch(Token_Number) || typeMatch(Token_STRING) || typeMatch(Token_IDENTIFIER)))
   {
        error("Syntax Error: Invalid value.");
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
    consume(Token_IF, "Syntax Error: Expected 'if' keyword.");
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
    consume(Token_ELSE, "Syntax Error: Expected 'else' keyword.");
    parseBlock();
}

static void parseExpression()
{
    if (!(typeMatch(Token_BANG_EQUALS) || typeMatch(Token_EQUALITY) || typeMatch(Token_GREATER) || typeMatch(Token_GREATER_EQUAL) || typeMatch(Token_LESS) || typeMatch(Token_LESS_EQUAL)))
    {
        error("Syntax Error: Invalid condition expression.");
    }
    
}

static bool parseOperations()
{
    if (_match(Token_PLUS) || _match(Token_MINUS) || _match(Token_SLASH) || _match(Token_STAR))
    {
        consume(peek().type, "Syntax Error: Expected a valid arithmetic operator.");
        return true;
    }
    
    return false;
}


static void parsePrint()
{
    consume(Token_PRINT, "Syntax Error: Expected 'print' keyword.");
    if (peek().type == Token_IDENTIFIER )
    {
        consume(Token_IDENTIFIER, "Syntax Error: Expected a valid identifier for printing.");
    }
    else parseValue();

    consume(Token_SEMICOLON, "Syntax Error: Expected a semicolon ';' at the end of the statement.");
}

static void parserFor()
{
    consume(Token_FOR, "Syntax Error: Expected 'for' keyword.");
    
    // Initialization (optional variable assignment)
    if (peek().type == Token_IDENTIFIER)
    {
        if (peekNext().type == Token_ASSIGNMENT)
        {
            parseAssignment();  // Handle variable initialization
        } 
        else 
        {
            consume(Token_IDENTIFIER, "Syntax Error: Expected a valid loop variable.");
            consume(Token_SEMICOLON, "Syntax Error: Expected a semicolon ';' after loop initialization.");
        }
    }

    

    // Condition
    consume(Token_IDENTIFIER, "Syntax Error: Expected a valid loop variable.");
    parseExpression();
    if ((peekNext().type == Token_IDENTIFIER))
        consume(Token_IDENTIFIER, "Syntax Error: Expected a valid loop variable.");
    else
        parseValue();
    
    consume(Token_SEMICOLON, "Syntax Error: Expected a semicolon ';' after loop condition.");

    // Update step (identifier expected, followed by an update operation)
    consume(Token_IDENTIFIER, "Syntax Error: Expected an identifier for loop update.");
    if (peek().type == Token_INCREMENT || peek().type == Token_DECREMENT)
    {
        forward();  // Consume `i++` or `i--`
    }
    else 
    {
        error("Syntax Error: Expected '++' or '--' for loop update.");
    }

    // Loop Body
    parseBlock();  // Parse the block containing loop statements
}

