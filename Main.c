#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Parser.h"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    char* sourceCode = ReadFile(argv[1]);

    clock_t start_time = clock(); 
    initLexer(sourceCode);
    initParser();
    parseProgram();

    clock_t end_time = clock();  // End timer
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Parsing completed in" BLU" %.6f seconds.\n"RESET, elapsed_time);

    free(sourceCode);
    return 0;
}



