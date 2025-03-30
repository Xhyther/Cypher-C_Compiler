#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Parser.h"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    char* sourceCode = ReadFile(argv[1]);

    initLexer(sourceCode);
    initParser();
    parseProgram();



    free(sourceCode);
    return 0;
}



