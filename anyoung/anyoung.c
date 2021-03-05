#include <stdio.h>
#include "kinput.h"
#include "annyCore.c"

int main()
{
    char chars[80] = "hello 안녕";
    while (chars[0] != '\n' && chars[0] != '\0')
    {
        printf(">>> ");
        getSO(chars);
        anyFunction(chars);
    }

}
