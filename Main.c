#include <stdio.h>
#include "Scanner.h"
#include "Tokens.h"

#define MaxToken 1000

void LexicalScannerTest();

int main(int argc, const char *argv[])
{
    
    printf("Number of Arguments: %d\n", argc);
    if(argc > 0)
    {
        printf("Compiling: [%s]\n", argv[0]);
    }

    LexicalScannerTest();
    


    return 0;
}


void LexicalScannerTest(){
    char stringToken[MaxToken];
    Token Tokens[MaxToken];
    
    printf("Enter an Expression to be Tokenized: ");
    fgets(stringToken, MaxToken, stdin);
    printf("\n");
    printf("Token to be tokenized: %s \n", stringToken);

    int TokenCount = 0;
    initScanner(stringToken);

    do {
        printf("Debug: Current Token Count = %d\n", TokenCount);
        Tokens[TokenCount] = Tokenizer(); // Get the next token
        printf("Token: %s\n", Tokens[TokenCount].Lexeme);
        switch(Tokens[TokenCount].type)
        {
            case Token_LEFT_PARENT: 
                printf("Token type: %s", "Token_LEFT_PARENT"); 
                break;
            case Token_RIGHT_PARENT: 
                printf("Token type: %s", "Token_RIGHT_PARENT");
                break;
            case Token_LEFT_BRACE: 
                printf("Token type: %s", "Token_LEFT_BRACE");
                break;
            case Token_RIGHT_BRACE: 
                printf("Token type: %s", "Token_RIGHT_BRACE");
                break;
            case Token_COMMA: 
                printf("Token type: %s", "Token_COMMA");
                break;
            case Token_DOT: 
                printf("Token type: %s", "Token_DOT");
                break;
            case Token_MINUS: 
                printf("Token type: %s", "Token_MINUS");
                break;
            case Token_PLUS:
                printf("Token type: %s", "Token_PLUS");
                break;
            case Token_SLASH: 
                printf("Token type: %s", "Token_SLASH");
                break;
            case Token_STAR: 
                printf("Token type: %s", "Token_STAR");
                break;
        
            //One or Two-Character Tokens
            case Token_BANG: 
                printf("Token type: %s", "Token_BANG");         
                break;
            case Token_BANG_EQUALS: 
                printf("Token type: %s", "Token_BANG_EQUALS");
                break;
            case Token_ASSIGNMENT: 
                printf("Token type: %s", "Token_ASSIGNMENT");
                break;
            case Token_EQUALITY: 
                printf("Token type: %s", "Token_EQUALITY");
                break;
            case Token_GREATER: 
                printf("Token type: %s", "Token_GREATER");
                break;
            case Token_GREATER_EQUAL: 
                printf("Token type: %s", "Token_GREATER_EQUAL");
                break;
            case Token_LESS: 
                printf("Token type: %s", "Token_LESS");
                break;
            case Token_LESS_EQUAL: 
                printf("Token type: %s", "Token_LESS_EQUAL");
                break;

            
        }
    } while (Tokens[TokenCount++].type != Token_EOF && TokenCount < MaxToken - 1);
    
    
}