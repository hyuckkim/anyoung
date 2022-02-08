#pragma once
#include "types.h"

typedef struct struct_stack stack;
#define stackLength 20

//긴 전체 문자열을 계산해 변수 하나가 되는 과정에서 만들어지는 스택.
struct struct_stack
{
    union {
        int iValue;
        char* sValue;
        char* vValue;
        char oValue;
    };
    type type; //none, iV, sV, vV, oV, eV
};

/// <summary>
/// Make word stack in Line input
/// </summary>
/// <param name="startP">pointer of line's start position</param>
/// <param name="endP">pointer of line's end position</param>
/// <param name="index">return only one int, return stack's length</param>
/// <returns>sliced pointer</returns>
stack* sliceFactorData(const char* startF, const char* endF, int* index);

//sliceFactorData에서 평가한 식을 계산해 변수로 나타낸다.
variable calcStackToVariable(stack* SliceData, int dataLength);

