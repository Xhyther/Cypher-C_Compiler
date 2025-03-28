#pragma once

#include "Tokens.h"

typedef struct {
    Token current;
    Token previous;
}Parser;

Parser parser;