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
    Token_STAR,

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

    Token_EOF,
    Token_ERROR
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

static token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.line = scanner.line;
    token.Lexeme = scanner.start;
    return token;
}

static bool isAtEnd(){
    return *scanner.current == '\0';
}

static char advance(){
    scanner.current++;
    return scanner.current[-1];
}

static bool match(char expected)
{
    if(isAtEnd()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

 Token Tokenizer(char *source){
    char *c = source;
    c = advance();
    switch(c){
        case '(' : return makeToken(Token_LEFT_PARENT);
        case ')' : return makeToken(Token_RIGHT_PARENT);
        case '{' : return makeToken(Token_LEFT_BRACE);
        case '}' : return makeToken(Token_RIGHT_BRACE);
        case ',' : return makeToken(Token_COMMA);
        case '.' : return makeToken(Token_DOT);
        case '-' : return makeToken(Token_MINUS);
        case '+' : return makeToken(Token_PLUS);
        case '/' : return makeToken(Token_SLASH);
        case '*' : return makeToken(Token_STAR);

        case '!':
            return makeToken(match('=') ? Token_BANG_EQUALS : Token_BANG);
        case '<':
            return makeToken(match('=') ? Token_GREATER_EQUAL : Token_GREATER; 
        case '>':
            return makeToken(match('=') ? Token_LESS_EQUAL : Token_LESS;     
        case '=':
            return makeToken(match('=') ? Token_EQUALITY : );
        case ':'
            return makeToken(match('=') ? Token_ASSIGNMENT : );
        
         
        default:
            return makeToken(Token_ERROR);

    }


}