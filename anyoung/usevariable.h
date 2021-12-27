#pragma once
#include "types.h"
//name과 같은 이름의 변수가 있다면 반환한다.
variable* getVariable(char* name);

//변수 개수를 하나 추가하고 배열이 꽉 찼다면 배열 길이를 두배로 한다.
void VariableInserted();

//문자열에서 새로운 변수를 만들어 반환한다.
variable* makeVariable(char* name);

//현재 함수의 인수 중 이름이 맞는 것이 있다면 반환한다.
variable* GetArgument(char* name);

//해당 이름의 변수가 있다면 반환하고 없다면 새로 만든다.
variable* getVar(char* name);