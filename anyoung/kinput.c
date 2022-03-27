#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

#include "kinput.h"

#define SHUTDOWN 3
typedef enum { sol, duo, tri, qua, funA, funB, LineBreak, BackSpace } textInfo;

void printBit(unsigned char a)
{
	printf("%d %d %d %d %d %d %d %d",
		(a >> 7) % 2,
		(a >> 6) % 2,
		(a >> 5) % 2,
		(a >> 4) % 2,
		(a >> 3) % 2,
		(a >> 2) % 2,
		(a >> 1) % 2,
		(a >> 0) % 2);
}
bool isSolByte(unsigned char byte)
{
	if ((byte | 0b01111111) == 0b01111111)  //negative 
		return true;
	return false;
}
bool isDuoByte(unsigned char byte)
{
	if ((byte | 0b11011111) == 0b11011111  //negative
		&& (byte & 0b11000000) == 0b11000000) //positive
		return true;
	return false;
}
bool isTriByte(unsigned char byte)
{
	if ((byte | 0b11101111) == 0b11101111  //negative
		&& (byte & 0b11100000) == 0b11100000) //positive
		return true;
	return false;
}
bool isQuaByte(unsigned char byte)
{
	if ((byte | 0b11110111) == 0b11110111  //negative
		&& (byte & 0b11110000) == 0b11110000) //positive
		return true;
	return false;
}
int getitsbyte(unsigned char byte)
{
	if (isSolByte(byte))
		return 1;
	if (isDuoByte(byte))
		return 2;
	if (isTriByte(byte))
		return 3;
	if (isQuaByte(byte))
		return 4;
	return -1;
}
char* conversation[240]; //each multibyte texts in line.

void printMultibyteChar(textInfo thisInfo, char* utf8, char* nooNow);
int verifyKey(int key_value, textInfo* thisInfo);
int setNextUTF8Text(textInfo thisInfo, char* nooNow, char* utf8);
char* getSO(char* writeAt, const char* various)
{
	int key_value = 0; //get solo char data by _getch()
	char nextValue = 0; //utf8 indexing data
	char stack = 0; //datas - nextValue.
	char utf8[4] = "\0"; //array can utf8 4byte solo text

	char* nooNow = writeAt;
	textInfo thisInfo = sol; //how byte to use
	printf("%s", various);
	while (key_value != '\n' && key_value != '\r')
	{
		key_value = _getch();
		if (stack == 0)
		{
			utf8[0] = key_value;
			stack = verifyKey(key_value, &thisInfo);
			if (stack == -1) return NULL;
		}
		else
		{
			nextValue++;
			utf8[nextValue] = key_value;
			stack--;
		}
		if (stack == 0)
		{
			printMultibyteChar(thisInfo, utf8, nooNow);
			nooNow += setNextUTF8Text(thisInfo, nooNow, utf8);
			if (thisInfo == BackSpace) {
				printf("%s%s", various, writeAt);
			}
			nextValue = 0;
		}
	}
	return writeAt;
}
int verifyKey(int key_value, textInfo* thisInfo) {
	if (key_value == 0) { *thisInfo = funA; return 1; }
	if (key_value == SHUTDOWN) return -1;
	if (key_value == 224) { *thisInfo = funB; return 1; }
	if (key_value == '\n' || key_value == '\r') { *thisInfo = LineBreak; return 0; }
	if (key_value == '\b') { *thisInfo = BackSpace; return 0; }
	if (isSolByte(key_value)) { *thisInfo = sol; return 0; }
	if (isDuoByte(key_value)) { *thisInfo = duo; return 1; }
	if (isTriByte(key_value)) { *thisInfo = tri; return 2; }
	if (isQuaByte(key_value)) { *thisInfo = qua; return 3; }
	return -1;
}
void printMultibyteChar(textInfo thisInfo, char* utf8, char* nooNow)
{
	switch (thisInfo)
	{
	case funA:
	case funB:
		break;
	case LineBreak:
		printf("\n");
		break;
	case BackSpace:
		printf("\
\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\
                                                                                          \
\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		//'\b' * 80 + ' ' * 80 + '\b' * 80
		break;
	case sol:
		printf("%c", utf8[0]);
		break;
	case duo:
		printf("%c%c", utf8[0], utf8[1]);
		break;
	case tri:
		printf("%c%c%c", utf8[0], utf8[1], utf8[2]);
		break;
	case qua:
		printf("%c%c%c%c", utf8[0], utf8[1], utf8[2], utf8[3]);
		break;
	}
}
int setNextUTF8Text(textInfo thisInfo, char* writePos, char* utf8)
{
	static int iAge = 0;
	switch (thisInfo)
	{
	case LineBreak:
		writePos[0] = '\n';
		writePos[1] = '\0';
	case funA:
	case funB:
		return 0;
	case BackSpace:
		if (iAge > 0)
		{
			iAge -= 1;
			conversation[iAge][0] = '\0';
			return conversation[iAge] - writePos;
		}
		else
		{
			return 0;
		}
	case sol:
		writePos[0] = utf8[0];
		conversation[iAge] = writePos;
		iAge += 1;
		return 1;
	case duo:
		writePos[0] = utf8[0];
		writePos[1] = utf8[1];
		conversation[iAge] = writePos;
		iAge += 1;
		return 2;
	case tri:
		writePos[0] = utf8[0];
		writePos[1] = utf8[1];
		writePos[2] = utf8[2];
		conversation[iAge] = writePos;
		iAge += 1;
		return 3;
	case qua:
		writePos[0] = utf8[0];
		writePos[1] = utf8[1];
		writePos[2] = utf8[2];
		writePos[3] = utf8[3];
		conversation[iAge] = writePos;
		iAge += 1;
		return 4;
	}
}