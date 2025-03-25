#include <stdio.h>
#include "Scanner.h"
#include "Tokens.h"

#define MaxToken 1000;


int main(int argc, const char *argv[])
{
    printf("Number of Arguments: %d\n", argc);
    if(argc > 0)
    {
        printf("Compiling: [%s]\n", argv[0]);
    }
    char stringToken[MaxToken];
    
    printf("Enter an Expression to be Tokenized: ");
    scanf(" %s", stringToken);
    printf("\n");
    printf("Token to be tokenized: %s \n", stringToken);
    


    return 0;
}