#include <stdio.h>



int isBalanced(Token *t)
{
    int top = 0, i = 0;

    while(t[i].type != Token_EOF && top >= 0)
    {
        if(t[i].type == Token_LEFT_PARENT) top++;
        else if (t[i].type == Token_RIGHT_PARENT) top--;
        i++;
    }

    if(!top) return 1;
    return 0;
}