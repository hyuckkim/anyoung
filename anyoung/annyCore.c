#pragma once
#include <stdio.h>

char* lNow; //one sentence
char* lCTs[20]; // sentence lNow's words.
int lengthOfL = 0; // sentence's word count.

char* newWord(char* line, int now)
{
	int choose = 0;
	for (int i = 0; 1; i++)
	{
		if (choose == now) return &line[i];
		if (line[i] == ' ' && line[i + 1] != ' ') choose += 1;
		if (line[i] == '\0') return 0;
	}
}
int isMatch(char* word1, char* word2)
{
	int i = 0;
	while (1)
	{
		if (word1[i] != word2[i]) return 0;
		i++;
		if (word1[i] == '\0' || word1[i] == ' ') goto breakByFirst;
		if (word2[i] == '\0' || word2[i] == ' ') goto breakBySecond;
	}
breakByFirst:
	if (word2[i] == '\0' || word2[i] == ' ') return 1;
	else return 0;
breakBySecond:
	if (word1[i] == '\0' || word1[i] == ' ') return 1;
	else return 0;
}
void function_analysis(char* line, char* lastW)
{
    unsigned char a;
    int i = 0;
    while(line + i != lastW - 1)
    {
        a = line[i];
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
            printf(" 1byte %c", line[i]);
        }
        else if (
            ((a >> 7) % 2 == 1)
            && ((a >> 6) % 2 == 1)
            && ((a >> 5) % 2 == 0))
        {
            printf(" 2byte %c%c", line[i], line[i + 1]);
        }
        else if (
            ((a >> 7) % 2 == 1)
            && ((a >> 6) % 2 == 1)
            && ((a >> 5) % 2 == 1)
            && ((a >> 4) % 2 == 0))
        {
            printf(" 3byte %c%c%c", line[i], line[i + 1], line[i + 2]);
        }
        else if (
            ((a >> 7) % 2 == 1)
            && ((a >> 6) % 2 == 1)
            && ((a >> 5) % 2 == 1)
            && ((a >> 4) % 2 == 1)
            && ((a >> 3) % 2 == 0))
        {
            printf(" 4byte %c%c%c%c", line[i], line[i + 1], line[i + 2], line[i + 3]);
        }
        i += 1;
        printf("\n");
    }
    printf("\n");
}
void function_say(char* line, char* lastW)
{
    int i = 0;
    while (line + i != lastW - 1)
    {
        printf("%c", line[i]);
        i++;
    }
    printf("\n");
}
void anyFunction(char* line)
{
	char* robs[20];
	int robCount;
	int lengthOfRobs;
	for (int i = 0; i < 20; i++)
	{
		robs[i] = newWord(line, i);
		if (robs[i] == 0)
		{
			robCount = i;
			lengthOfRobs = i + 1;
			break;
		}
	}
	if (isMatch(robs[robCount - 1], "분석 "))
		function_analysis(robs[0], robs[robCount - 1]);
    if (isMatch(robs[robCount - 1], "말하기 "))
        function_say(robs[0], robs[robCount - 1]);
	lNow = line;
}
