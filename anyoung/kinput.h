#include <conio.h>

typedef enum { sol, duo, tri, qua, funA, funB, LineBreak, BackSpace } textInfo;
void printMultibyteChar(textInfo thisInfo, char* utf8, char* nooNow);
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
char* noo[lineLength]; //sentence while \n. 
int iAge = 0;
void getSO(char* writeAt, char* various)
{
	int key_value = 0; //get solo char data by _getch()
	char nextValue = 0; //utf8 indexing data
	char stack = 0; //datas - nextValue.
	char utf8[4]; //array can utf8 4byte solo text

	char* nooNow = writeAt;
	textInfo thisInfo = sol; //how byte to use
	printf("%s", various);
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
			printMultibyteChar(thisInfo, utf8, nooNow);
			switch (thisInfo)
			{
			case funA:
				break;
			case funB:
				break;
			case LineBreak:
				nooNow[0] = '\0';
				break;
			case BackSpace:
				if (iAge > 0)
				{
					nooNow = noo[iAge - 1];
					noo[iAge - 1][0] = '\0';
					iAge -= 1;
				}
				printf("%s%s", various, writeAt);
				break;
			case sol:
				nooNow[0] = utf8[0];
				noo[iAge] = nooNow;
				nooNow += 1;
				iAge += 1;
				break;
			case duo:
				nooNow[0] = utf8[0];
				nooNow[1] = utf8[1];
				noo[iAge] = nooNow;
				nooNow += 2;
				iAge += 1;
				break;
			case tri:
				nooNow[0] = utf8[0];
				nooNow[1] = utf8[1];
				nooNow[2] = utf8[2];
				noo[iAge] = nooNow;
				nooNow += 3;
				iAge += 1;
				break;
			case qua:
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
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                                                                                          \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
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