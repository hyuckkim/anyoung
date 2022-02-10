#pragma once
#include "types.h"

//문자열을 판단해 함수를 실행할지 저장할지 결정한다.
void anyFunction(char* line);

//함수를 실제로 실행한다.
int useFunction(const char* line, def* define);

//사용이 끝난 함수를 해제한다.
void freeFunction(function* fun);

//새로 만든 함수의 구문을 저장한다.
int saveFunction(const char* line, int indent, function* saveTo);

//function* 형식의 변수를 할당해 반환한다.
function* initFunction(def* define, const char* str);

//문장의 글자별로 함수가 있는지 찾아 반환한다.
def* searchDefine(char* str);

// 문장 factor별로 잘라주기
void splitFactors(function fun, const char* str);

//선언 개수를 하나 추가하고 배열이 꽉 찼다면 배열 길이를 두배로 한다.
void insertDefine();