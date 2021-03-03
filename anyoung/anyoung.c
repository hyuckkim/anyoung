#include <stdio.h>
#include "kinput.h"
int main()
{
    char chars[80] = "hello 안녕";
    unsigned char a;
    int i = 0;
    int j = 0;
    while (chars[0] != '\n' && chars[0] != '\0')
    {
        for (i = 0; i < sizeof(chars) / sizeof(char); j++)
        {
            a = chars[i];
            printBit(a);
            if (a == '\n')
            {
                printf(" \\n");
                break;
            }
            else if (a == '\0')
            {
                printf(" \\0");
                break;
            }
            else if ((a >> 7) % 2 == 0)
            {
                printf(" 1byte %c", chars[i]);
            }
            else if (
                ((a >> 7) % 2 == 1)
                && ((a >> 6) % 2 == 1)
                && ((a >> 5) % 2 == 0))
            {
                printf(" 2byte %c%c", chars[i], chars[i + 1]);
            }
            else if (
                ((a >> 7) % 2 == 1)
                && ((a >> 6) % 2 == 1)
                && ((a >> 5) % 2 == 1)
                && ((a >> 4) % 2 == 0))
            {
                printf(" 3byte %c%c%c", chars[i], chars[i + 1], chars[i + 2]);
            }
            else if (
                ((a >> 7) % 2 == 1)
                && ((a >> 6) % 2 == 1)
                && ((a >> 5) % 2 == 1)
                && ((a >> 4) % 2 == 1)
                && ((a >> 3) % 2 == 0))
            {
                printf(" 4byte %c%c%c%c", chars[i], chars[i + 1], chars[i + 2], chars[i + 3]);
            }
            i += 1;
            printf("\n");
        }
        printf("\n>>> ");
        getSO(chars);
    }

}
