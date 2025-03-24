#include <stdio.h>


enum TokenType 
{
    //Single-Character Tokens
    Token_LEFT_PARENT,
    Token_RIGHT_PARENT,
    Token_LEFT_BRACE,
    Token_RIGHT_BRACE,
    Token_COMMA,
    Token_DOT,
    Token_MINUS,
    Token_PLUS,
    Token_SLASH,
    Token_START,

    //One or Two-Character Tokens
    Token_BANG,
    Token_BANG_EQUALS,
    Token_ASSIGNMENT,
    Token_EQUALITY,
    Token_GREATER,
    Token_GREATER_EQUAL,
    Token_LESS,
    Token_LESS_EQUAL,
    
    //Literals
    Token_IDENTIFIER,
    Token_STRING,
    Token_Number,

    //Keywords
    Token_LET,
    Token_IF,
    Token_ELSE,
    Token_DO,
    Token_WHILE,
    Token_FOR,
    Token_PRINT
};

int main(void)
{
    printf("Hello World!");
    return 0;
}