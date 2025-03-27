#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Scanner.h"
#include "Tokens.h"
#include "Balanced.h"

#define MaxToken 1024


void LexicalScannerTest(){
    char stringToken[MaxToken];
    Token Tokens[MaxToken];
    Token  currentToken;
    
    printf("Enter an Expression to be Tokenized: ");
    fgets(stringToken, MaxToken, stdin);
    printf("\n");
    printf("Token to be tokenized: %s \n", stringToken);

    int TokenCount = 0;
    initScanner(stringToken);

    while(currentToken.type != Token_ERROR && currentToken.type != Token_EOF && TokenCount < MaxToken){
        currentToken = scanToken();
        Tokens[TokenCount] = currentToken; // Get the next token
        if(currentToken.type != Token_EOF)
            printf("Token: %.*s \n", currentToken.length ,currentToken.start);
        switch(currentToken.type)
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
            case Token_IDENTIFIER: 
                printf("Token type: %s", "Token_IDENTIFIER");
            break;
            case Token_CHAR: 
                printf("Token type: %s", "Token_CHAR");
                break;
            case Token_STRING: 
                printf("Token type: %s", "Token_STRING");
                break;
            case Token_Number: 
                printf("Token type: %s", "Token_Number");
                break;
            case Token_EOF:
                printf("\nEnd of Token (EOF)\n");
                break;
            

            default:
                printf("\nToken type: %s\n", "Token_ERROR");
                printf("\n Error Message: %.*s\n", currentToken.length, currentToken.start);
                break;
            
        }
        printf("\n");
        TokenCount++;
    }

    if(isBalanced(Tokens))
        printf("BALANCED\n");
    else
        printf("Error! Not Balanced!\n");

    for(int i = 0; i < TokenCount; i++)
    {
        if(Tokens[i].type != Token_EOF)
            printf("Tokens: %.*s \n",  Tokens[i].length, Tokens[i].start);
    }
    

}