#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Scanner.h"
#include "Tokens.h"
#include "Balanced.h"

#define MaxToken 100



int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    char* sourceCode = ReadFile(argv[1]);
    initScanner(sourceCode);

    printf("Tokenizing file: %s\n", argv[1]);

    Token token;
    do {
        token = scanToken();
        printf("Token: %d, Lexeme: %.*s, Line: %d\n", token.type, token.length, token.start, token.line);
    } while (token.type != Token_EOF);

    free(sourceCode);
    return 0;
}



