#include <stdio.h>
#include <stdbool.h>
#include "Scanner.h"



typedef enum 
{
    //Single-Character Tokens
    Token_LEFT_PARENT,
    Token_RIGHT_PARENT,
    Token_LEFT_BRACE,
    Token_RIGHT_BRACE,
    Token_COMMA, //------------------
    Token_DOT, //---------------------
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
    Token_CHAR,
    Token_STRING,
    Token_Number,

    //Keywords
    Token_MAIN, // for Main function
    Token_IF,
    Token_ELSE,
    Token_WHILE,
    Token_FOR,
    Token_PRINT,

    Token_EOF,
    Token_ERROR
}TokenType;

typedef struct 
{
    TokenType type;
    const char* start;
    int length;
    int line;
}Token;





static bool isAtEnd()
{
    return *scanner.current == '\0' || *scanner.current =='\n';
}



static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token errorToken(const char* message)
{
    Token token;
    token.type = Token_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}


static char peek() 
{
    return *scanner.current;
}

  
static char peekNext()
{
    if (isAtEnd()) return '\0';
    return scanner.current[1];
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



static void skipWhitespace()
{
    for(;;){
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
              advance();
              break;
            case '\n':
              scanner.line++;
              advance();
              break;
            default:
              return;
          }
    }
}

static bool isDigit(char c)
{
     return c >= '0' && c <= '9';

}

static bool isAlpha(char c)
{
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_'));
}



static TokenType Keywords(const char* keyword, TokenType type) {
    int length = (int) strlen(keyword);
    if (scanner.current - scanner.start == length &&
        memcmp(scanner.start, keyword, length) == 0) {
        return type;
    }
    return Token_IDENTIFIER;
}


static Token identifier() {
    while (isAlpha(peek()) || isDigit(peek())) advance();

    switch (scanner.current[0])
    {
        case 'i': return makeToken(Keywords("if", Token_IF));
        case 'e': return makeToken(Keywords("else", Token_ELSE));
        case 'w': return makeToken(Keywords("while", Token_WHILE));
        case 'f': return makeToken(Keywords("for", Token_FOR));
        case 'p': return makeToken(Keywords("print", Token_PRINT));
        
    }

    return makeToken(Token_IDENTIFIER);
}




static Token integer()
{
    while(isDigit(peek()))
        advance();

    return makeToken(Token_Number);
}



Token scanToken()
{
    scanner.start = scanner.current;
    skipWhitespace();

    if(isAtEnd())
        return makeToken(Token_EOF);

    
   

    char c = advance();
    if (isDigit(c)) return integer();

    if(isAlpha(c))
    {
        return identifier();
       
    }

    switch(c){
        case '(' : return makeToken(Token_LEFT_PARENT);
        case ')' : return makeToken(Token_RIGHT_PARENT);
        case '{' : return makeToken(Token_LEFT_BRACE);
        case '}' : return makeToken(Token_RIGHT_BRACE);
        case ',' : return makeToken(Token_COMMA);
        case '.' : return makeToken(Token_DOT);
        case '-' : return makeToken(Token_MINUS);
        case '+' : return makeToken(Token_PLUS);
        case '*' : return makeToken(Token_STAR);
        case '/' : 
            if (peekNext() == '/')
            {
                while(peek() != '\n' &&!isAtEnd())
                advance();
                break;
            }
            else
                return makeToken(Token_SLASH);

        case '!':
            return makeToken(match('=') ? Token_BANG_EQUALS : Token_BANG);
        case '>':
            return makeToken(match('=') ? Token_GREATER_EQUAL : Token_GREATER); 
        case '<':
            return makeToken(match('=') ? Token_LESS_EQUAL : Token_LESS);     
        case '=':
            return makeToken(match('=') ? Token_EQUALITY : Token_ASSIGNMENT );

        case '\0':
            return makeToken(Token_EOF);
        
        default:
            return errorToken("Undefined token\n");

    }

    return errorToken("Unexpected character.");
}


