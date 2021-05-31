#pragma once
#include <stdio.h>
#include <stdlib.h>

int isMatch(char* word1, char* word2) //포인터부터 시작해 '\0'이나 ' '까지 같은지 비교함.
{
    int i = 0;
    while (1)
    {
        if (word1[i] != word2[i]) return 0;
        i++;
        if (word1[i] == '\0' || word1[i] == ' ' || word1[i] == '\t') goto breakByFirst;
        if (word2[i] == '\0' || word2[i] == ' ' || word1[i] == '\t') goto breakBySecond;
    }
breakByFirst:
    if (word2[i] == '\0' || word2[i] == ' ' || word1[i] == '\t') return 1;
    else return 0;
breakBySecond:
    if (word1[i] == '\0' || word1[i] == ' ' || word1[i] == '\t') return 1;
    else return 0;
}
int getPriority(char op) //연산자 기호 하나를 주고 연산자의 우선순위를 반환함.
{
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    if (op == '=' || op == '<' || op == '>') return 0;
    return -1;
}
int logSize(int v)
{
    int res = 1;
    for (int i = v; i >= 10; i /= 10, res++) {}
    return res;
}
int logScale(int v, int is)
{
    int in = 1;
    for (int i = 0; i < is; i++) in *= 10;
    return (v / in) % 10; //is번 자리수를 가장 앞으로 당기고 1의 자리수만 반환.
}
int stringLength(const char* item, char name) //지정 포인터부터 시작해 null문자가 아닌 구간의 길이를 반환함.
{
    int i;
    for (i = 0; item[i] != 0 && item[i] != name; i++) {}
    return i + 1;
}

int OperatorII(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '%':
        return a % b;
    case '/':
        return a / b;
    case '=':
        return a == b;
    case '>':
        return a > b;
    case '<':
        return a < b;
    default:
        printf("error except in OperatorII by %d %c %d", a, op, b);
        return 0;
    }
}
char* OperatorIS(int a, char* b, char op)
{
    if (op == '+')
    {
        char* result = malloc(sizeof(char) * (stringLength(b, 0) + logSize(a)) + 1);
        int tmp = 0;
        if (result != NULL)
        {
            for (int i = logSize(a) - 1; i >= 0; i--, tmp++)
            {
                result[tmp] = logScale(a, i) + '0';
            }
            for (int i = 0; b[i] != 0; i++, tmp++)
            {
                result[tmp] = b[i];
            }
            result[tmp] = '\0';
        }
        return result;
    }
    else
    {
        printf("error except in OperatorIS by %d %c %s", a, op, b);
        return NULL;
    }
}
char* OperatorSI(char* a, int b, char op)
{
    if (op == '+')
    {
        char* result = malloc(sizeof(char) * (stringLength(a, 0) + logSize(b)) + 1);
        int tmp = 0;
        if (result != NULL)
        {
            for (int i = 0; a[i] != 0; i++, tmp++)
            {
                result[tmp] = a[i];
            }
            for (int i = logSize(b) - 1; i >= 0; i--, tmp++)
            {
                result[tmp] = logScale(b, i) + '0';
            }
            result[tmp] = '\0';
        }
        return result;
    }
    else if (op == '*')
    {
        char* result = malloc(sizeof(char) * (stringLength(a, 0) * b) + 1);
        int tmp = 0;
        if (result != NULL)
        {
            for (int j = 0; j < b; j++)
            {
                for (int i = 0; a[i] != 0; i++, tmp++)
                {
                    result[tmp] = a[i];
                }
            }
            result[tmp] = '\0';
        }
        return result;
    }
    else
    {
        printf("error except in OperatorSI by %s %c %d", a, op, b);
        return NULL;
    }
}

variable operate(variable a, variable b, char op)
{
    int tmp = 0;
    variable result;

    result.iValue = 0;
    result.sValue = NULL;
    result.type = iV;

    bool isAPure = true;
    if (a.type == vV)
    {
        isAPure = false;
    avValue:
        a.type = a.vValue->type;
        if (a.type == iV) a.iValue = a.vValue->iValue;
        else if (a.type == sV) a.sValue = a.vValue->sValue;
        else if (a.type == vV)
        {
            a.vValue = a.vValue->vValue;
            goto avValue;
        }
    }
    bool isBPure = true;
    if (b.type == vV)
    {
        isBPure = false;
    bvValue:
        b.type = b.vValue->type;
        if (b.type == iV) b.iValue = b.vValue->iValue;
        else if (b.type == sV) b.sValue = b.vValue->sValue;
        else if (b.type == vV)
        {
            b.vValue = b.vValue->vValue;
            goto bvValue;
        }
    }
    switch (a.type)
    {
    case iV:
        switch (b.type)
        {
        case iV:
            result.type = iV;
            result.iValue = OperatorII(a.iValue, b.iValue, op);
            break;
        case sV:
            result.type = sV;
            result.sValue = OperatorIS(a.iValue, b.sValue, op);
            break;
        }
        break;
    case sV:
        switch (b.type)
        {
        case iV:
            result.type = sV;
            result.sValue = OperatorSI(a.sValue, b.iValue, op);
            break;
        case sV:
            //string and string
            switch (op)
            {
            case '+':
                result.sValue = malloc(sizeof(char) * (stringLength(a.sValue, 0) + stringLength(b.sValue, 0)) + 1);
                if (result.sValue != NULL)
                {
                    for (int i = 0; a.sValue[i] != 0; i++, tmp++)
                    {
                        result.sValue[tmp] = a.sValue[i];
                    }
                    for (int i = 0; b.sValue[i] != 0; i++, tmp++)
                    {
                        result.sValue[tmp] = b.sValue[i];
                    }
                    result.sValue[tmp] = '\0';
                }
                result.type = sV;
                break;
            case '=':
                result.type = iV;
                result.iValue = isMatch(a.sValue, b.sValue);
                break;
            }
            break;
        }
        break;
    }
    if (isAPure && a.type == sV) free(a.sValue);
    if (isBPure && b.type == sV) free(b.sValue);
    return result;
}
bool isOperator(char iv)
{
    return iv == '+'
        || iv == '-'
        || iv == '*'
        || iv == '%'
        || iv == '/'
        || iv == '('
        || iv == ')'
        || iv == '='
        || iv == '<'
        || iv == '>'
        || iv == '{'
        || iv == '}';
}