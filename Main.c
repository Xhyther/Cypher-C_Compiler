#include <stdio.h>
#include "Scanner.h"

typedef enum 
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
    Token_PRINT,

    Token_EOF
}TokenType;

typedef struct {
    TokenType type;
    char *Lexeme;
    int line; 
}Token;

Token scanToken()
{
    scanner.start = scanner.current;

    if(isAtEnd())
        return makeToken(Token_EOF);

    return -1; //Make a function for returning error token
}

static bool isAtEnd(){
    return *scanner.current == "\0";
}

static token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.line = scanner.line;
    token.Lexeme = scanner.start;
    return token;
}

int main(int argc, const char *argv[])
{
    printf("Number of Arguments: %d\n", argc);
    if(argc > 0)
    {
        printf("Compiling: [%s]\n", argv[0]);
    }
    return 0;
}