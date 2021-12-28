#pragma once
#include "types.h"

/// <summary>
/// Make word stack in Line input
/// </summary>
/// <param name="startP">pointer of line's start position</param>
/// <param name="endP">pointer of line's end position</param>
/// <param name="index">return only one int, return stack's length</param>
/// <returns>sliced pointer</returns>
stack* InitFactorSliceData(const char* startF, const char* endF, int* index);

//(시작지점 startF와 종료지점 endF로 표현되는) 라인 문자열의 일부를 계산해 나타낸다.
variable findArginFactor(const char* textStartF, const char* textEndF);