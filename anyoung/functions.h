#pragma once
#include <stdio.h>
#include "annyCore.h"

void Function_Help()
{
    printf("\n데이터\n");
    printf("ㅁ을/를 ㅇ으로/로 정하기\t\t변수 ㅁ의 값을 ㅇ로 지정합니다. ㅁ이 없다면 새로 만듭니다.");
    printf("ㅁ을/를 ㅇ만큼 더하기\t\t변수 ㅁ의 값에 ㅇ를 더합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.");
    printf("ㅁ을/를 ㅇ만큼 빼기\t\t변수 ㅁ의 값에 ㅇ를 뺍니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.");
    printf("ㅁ을/를 ㅇ만큼 곱하기\t\t변수 ㅁ의 값에 ㅇ를 곱합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.");
    printf("ㅁ을/를 ㅇ만큼 나누기\t\t변수 ㅁ의  값에 ㅇ를 나눕니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.");
    printf("\n화면 입출력\n");
    printf("ㅁ 을/를 말하기 \t\tㅁ을 개행문자와 함께 출력합니다.\n");
    printf("ㅁ 을/를 ㅇ 번 표시하기 \tㅁ을 ㅇ번 출력합니다. ㅇ는 숫자여야 합니다.\n");
}
void Function_Set(variable value1, variable value2)
{
    if (value1.type == 2)
    {
        switch (value2.type)
        {
        case 0:
            value1.vValue->type = 0;
            value1.vValue->iValue = value2.iValue;
            break;
        case 1:
            value1.vValue->type = 1;
            value1.vValue->sValue = setString(value2.sValue);
            break;
        case 2:
            if (value2.vValue->type == 0)
            {
                value1.vValue->type = 0;
                value1.vValue->iValue = value2.vValue->iValue;
            }
            else if (value2.vValue->type == 1)
            {
                value1.vValue->type = 1;
                value1.vValue->sValue = setString(value2.vValue->sValue);
            }
            break;
        }
    }
}
void Function_Add(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue += value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue += value2.vValue->iValue;
        }
    }
}
void Function_Minus(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue -= value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue -= value2.vValue->iValue;
        }
    }
}
void Function_Multi(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue *= value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue *= value2.vValue->iValue;
        }
    }
}
void Function_Devide(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue /= value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue /= value2.vValue->iValue;
        }
    }
}
void Function_Say(variable value)
{
    if (value.type == 0)
        printf("%d\n", value.iValue);
    else if (value.type == 1)
        printf("%s\n", value.sValue);
    else
    {
        if(value.vValue->type == 0)
            printf("%d\n", value.vValue->iValue);
        else if (value.vValue->type == 1)
            printf("%s\n", value.vValue->sValue);
    }
}
void Function_Print(variable value1, variable value2)
{
    for (int i = 0; i < value2.iValue; i++)
    {
        if (value1.type == 0)
            printf("%d", value1.iValue);
        else if (value1.type == 1)
            printf("%s", value1.sValue);
        else
        {
            if (value1.vValue->type == 0)
                printf("%d", value1.vValue->iValue);
            else if (value1.vValue->type == 1)
                printf("%s", value1.vValue->sValue);
        }
    }
    printf("\n");
}