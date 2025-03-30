#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Scanner.h"

#define MAXTOKEN 1024 + 1 //+1 for appending the EOF


typedef enum 
{
    //Single-Character Tokens
    Token_LEFT_PARENT,
    Token_RIGHT_PARENT,
    Token_LEFT_BRACKETS,
    Token_RIGHT_BRACKETS,
    Token_LEFT_BRACE,
    Token_RIGHT_BRACE,
    Token_SEMICOLON,
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



typedef struct
{
    Token tokens[MAXTOKEN];
    int counter;
}Token_List;


Token_List tokenList = {.counter = 0} ;



static bool isAtEnd()
{
    return *scanner.current == '\0';
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


static char current() 
{
    return *scanner.current;
}

  
static char Next()
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
        char c = current();
        if(isAtEnd()) return;
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


static TokenType isString()
{
    while (current() != '"' && !isAtEnd())
    {
        if(current() == '\n') scanner.line++;
        advance();
    }

    if (isAtEnd()) return Token_ERROR;
    
    advance();
    return Token_STRING;
    
}



static bool isAlpha(char c)
{
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_'));
}



static TokenType checkKeyword(int start, int length,
    const char* rest, TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }

  return Token_IDENTIFIER;
}

static TokenType identifierType() {
    switch (scanner.start[0]) {
        case 'm': return checkKeyword(1, 3, "ain", Token_MAIN);
        case 'i': return checkKeyword(1, 1, "f", Token_IF);
        case 'e': return checkKeyword(1, 3, "lse", Token_ELSE);
        case 'w': return checkKeyword(1, 4, "hile", Token_WHILE);
        case 'f': return checkKeyword(1, 2, "or", Token_FOR);
        case 'p': return checkKeyword(1, 4, "rint", Token_PRINT);
       
      }
    return Token_IDENTIFIER;
  }
  

static Token identifier() {
    while (isAlpha(current()) || isDigit(current())) advance();
    return makeToken(identifierType());
  }




static Token integer()
{
    while(isDigit(current()))
        advance();

    return makeToken(Token_Number);
}



Token scanToken()
{
    skipWhitespace();
    scanner.start = scanner.current;
    

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
        case '[' : return makeToken(Token_LEFT_BRACKETS);
        case ']' : return makeToken(Token_RIGHT_BRACKETS);
        case '{' : return makeToken(Token_LEFT_BRACE);
        case '}' : return makeToken(Token_RIGHT_BRACE);
        case ';' : return makeToken(Token_SEMICOLON);
        case ',' : return makeToken(Token_COMMA);
        case '.' : return makeToken(Token_DOT);
        case '-' : return makeToken(Token_MINUS);
        case '+' : return makeToken(Token_PLUS);
        case '*' : return makeToken(Token_STAR);

        //For comments or division
        case '/' : 
            if (Next() == '/')
            {
                while(current() != '\n' &&!isAtEnd())
                advance();
                break;
            }
            else
                return makeToken(Token_SLASH);
        
        //For strings
        case '"' :
            if (isString() == Token_ERROR)
                return errorToken("Strings must have a closng \" ");
            else
                return makeToken(Token_STRING);



        //For conditions
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


void addTokenToList(Token token)
{
    if (tokenList.counter < MAXTOKEN )
    {
        tokenList.tokens[tokenList.counter++] = token;
    }
    else
    {
        printf("Error! Token Overload\n");
        exit(1);
        
    }
    
}

void initLexer(const char* source)
{
    initScanner(source);
     
    Token token;
    do
    {
        token = scanToken();
        addTokenToList(token);

        //For testing
        printf("Lexeme: %.*s, Line: %d\n", token.length, token.start, token.line);

    }while(token.type != Token_EOF);

    Token EndOf = {Token_EOF, " ", 1, scanner.line};
    addTokenToList(EndOf);
}


