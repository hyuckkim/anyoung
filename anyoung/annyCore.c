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
	if (isMatch(robs[0], "안녕 "))
		printf("안녕 단어로 시작하는 말을 했구나!\n");
	if (isMatch(robs[1], "친구 "))
		printf("친구 단어가 두 번째 단어로 오는 말을 했구나!\n");
	if (isMatch(robs[robCount - 1], "반갑네 "))
		printf("반갑네로 끝나는 말을 했구나!\n");
	lNow = line;
}