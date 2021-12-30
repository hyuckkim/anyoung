#pragma once
#include "types.h"

//포인터부터 시작해 '\0'이나 ' '까지 같은지 비교함.
int isMatch(const char* word1, const char* word2); 

//연산자 기호 하나를 주고 연산자의 우선순위를 반환함.
int getPriority(char op);

int logSize(int v);
int logScale(int v, int is);

//지정 포인터부터 시작해 null문자가 아닌 구간의 길이를 반환함.
int stringLength(const char* item, char name);

variable* operate(variable* a, variable* b, char op);

bool isOperator(char iv);

//띄어쓰기만 무시하며 다음문자가 연산자인지 확인한다.
int next_is_opperator(const char* po);

//LineFeed \n 문자를 NULL로 바꾼다. \n이 없으면 바꾸지 않는다.
void ChangeLFtoNULL(char* item);

//문자열을 item과 같게 새로 할당해 덮어쓴다.
char* setString(const char* item);

//factor의 인수 형식 중 맞는게 있으면 반환한다. ret에 글자의 길이를 넣는다.
bool isFair(const char* word, factor it, int* ret);