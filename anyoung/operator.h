#pragma once
#include "types.h"

//포인터부터 시작해 '\0'이나 ' '까지 같은지 비교함.
int isMatch(const char* word1, const char* word2); 

//연산자 기호 하나를 주고 연산자의 우선순위를 반환함.
int getPriority(char op); 


int logSize(int v);
int logScale(int v, int is);

int stringLength(const char* item, char name); //지정 포인터부터 시작해 null문자가 아닌 구간의 길이를 반환함.


int OperatorII(int a, int b, char op);
char* OperatorIS(int a, char* b, char op);
char* OperatorSI(char* a, int b, char op);

variable* operate(variable* a, variable* b, char op);
bool isOperator(char iv);

int next_is_opperator(const char* po);

//LineFeed \n 문자를 NULL로 바꾼다. \n이 없으면 바꾸지 않는다.
void ChangeLFtoNULL(char* item);

char* setString(const char* item);

bool isFair(const char* word, factor it, int* ret);