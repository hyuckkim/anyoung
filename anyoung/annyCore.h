#pragma once
#include "types.h"

stack* InitFactorSliceData(const char* startF, const char* endF, int* index);

//(시작지점 startF와 종료지점 endF로 표현되는) 라인 문자열의 일부를 계산해 나타낸다.
variable findArginFactor(const char* textStartF, const char* textEndF);