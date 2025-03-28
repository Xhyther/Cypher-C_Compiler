#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    const char *start;
    const char *current;
    int line;

} Scanner;

Scanner scanner;


void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;

}

static char* ReadFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Not enough memory to read file\n");
        exit(1);
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);
    return buffer;
}
