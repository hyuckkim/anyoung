#pragma once
#include <stdio.h>
#include <conio.h>

typedef enum { false, true } bool;
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
bool isValid()
{
	return true;
}
bool isSolByte(unsigned char byte)
{
	if ((byte >> 7) % 2 == 0)
		return true;
	return false;
}
bool isDuoByte(unsigned char byte)
{
	if (
		((byte >> 7) % 2 == 1)
		&& ((byte >> 6) % 2 == 1)
		&& ((byte >> 5) % 2 == 0))
		return true;
	return false;
}
bool isTriByte(unsigned char byte)
{
	if (
		((byte >> 7) % 2 == 1)
		&& ((byte >> 6) % 2 == 1)
		&& ((byte >> 5) % 2 == 1)
		&& ((byte >> 4) % 2 == 0))
		return true;
	return false;
}
bool isQuaByte(unsigned char byte)
{
	if (
		((byte >> 7) % 2 == 1)
		&& ((byte >> 6) % 2 == 1)
		&& ((byte >> 5) % 2 == 1)
		&& ((byte >> 4) % 2 == 1)
		&& ((byte >> 3) % 2 == 0))
		return true;
	return false;
}
void getSO(char* writeAt)
{
	int key_value = 0; //get solo char data by _getch()
	char nextValue = 0; //utf8 indexing data
	char stack = 0; //datas - nextValue.
	char utf8[4]; //array can utf8 4byte solo text

	char* noo[80]; //sentence while \n. 
	char* nooNow = writeAt;
	int iAge = 0;
	textInfo thisInfo = sol; //how byte to use
	while (key_value != '\n' && key_value != '\r')
	{
		key_value = _getch();
		if (stack == 0)
		{
			utf8[0] = key_value;
			if (key_value == 0) { thisInfo = funA; stack = 1; }
			else if (key_value == 224) { thisInfo = funB; stack = 1; }
			else if (key_value == '\n' || key_value == '\r') { thisInfo = LineBreak; stack = 0; }
			else if (key_value == '\b') { thisInfo = BackSpace; stack = 0; }
			else if (isSolByte(key_value)) { thisInfo = sol; stack = 0; }
			else if (isDuoByte(key_value)) { thisInfo = duo; stack = 1; }
			else if (isTriByte(key_value)) { thisInfo = tri; stack = 2; }
			else if (isQuaByte(key_value)) { thisInfo = qua; stack = 3; }
			else printf("error : %d", key_value);
		}
		else
		{
			nextValue++;
			utf8[nextValue] = key_value;
			stack--;
		}
		if (stack == 0)
		{
			switch (thisInfo)
			{
			case funA:
				printf("%d %d", utf8[0], utf8[1]);
				break;
			case funB:
				printf("%d %d", utf8[0], utf8[1]);
				break;
			case LineBreak:
				printf("\n");
				nooNow[0] = '\0';
				break;
			case BackSpace:
				if (iAge > 0)
				{
					printf("\b \b");
					nooNow = noo[iAge - 1];
					iAge -= 1;
				}
				break;
			case sol:
				printf("%c", utf8[0]);
				nooNow[0] = utf8[0];
				noo[iAge] = nooNow;
				nooNow += 1;
				iAge += 1;
				break;
			case duo:
				printf("%c%c", utf8[0], utf8[1]);
				nooNow[0] = utf8[0];
				nooNow[1] = utf8[1];
				noo[iAge] = nooNow;
				nooNow += 2;
				iAge += 1;
				break;
			case tri:
				printf("%c%c%c", utf8[0], utf8[1], utf8[2]);
				nooNow[0] = utf8[0];
				nooNow[1] = utf8[1];
				nooNow[2] = utf8[2];
				noo[iAge] = nooNow;
				nooNow += 3;
				iAge += 1;
				break;
			case qua:
				printf("%c%c%c%c", utf8[0], utf8[1], utf8[2], utf8[3]);
				nooNow[0] = utf8[0];
				nooNow[1] = utf8[1];
				nooNow[2] = utf8[2];
				nooNow[3] = utf8[3];
				noo[iAge] = nooNow;
				nooNow += 4;
				iAge += 1;
				break;
			}
			nextValue = 0;
		}
	}
}