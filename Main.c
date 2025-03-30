#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Parser.h"
#include "Tester.h"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    char* sourceCode = ReadFile(argv[1]);

    initScanner(sourceCode);



    free(sourceCode);
    return 0;
}



