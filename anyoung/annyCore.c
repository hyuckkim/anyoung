#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "annyCore.h"

void operate(variable a, variable b, char op, variable *result)
{
    int tmp = 0;
    result->iValue = 0;
    result->sValue = 0;
    result->type = 0;
    if (a.type == 2)
    {
        a.type = a.vValue->type;
        if (a.type == 0) a.iValue = a.vValue->iValue;
        else if (a.type == 1) a.sValue = a.vValue->sValue;
    }
    if (b.type == 2)
    {
        b.type = b.vValue->type;
        if (b.type == 0) b.iValue = b.vValue->iValue;
        else if (b.type == 1) b.sValue = b.vValue->sValue;
    }
    switch (a.type)
    {
    case 0:
        switch (b.type)
        {
        case 0:
            //int and int
            switch (op)
            {
            case '+':
                result->type = 0;
                result->iValue = a.iValue + b.iValue;
                break;
            case '-':
                result->type = 0;
                result->iValue = a.iValue - b.iValue;
                break;
            case '*':
                result->type = 0;
                result->iValue = a.iValue * b.iValue;
                break;
            case '/':
                result->type = 0;
                result->iValue = a.iValue / b.iValue;
                break;
            }
            break;
        case 1:
            //int and string
            switch (op)
            {
            case '+':
                free(result->sValue); // (대충 글자 크기가 다르니 버리고 새로 만든다는 내용)
                result->sValue = malloc(sizeof(char) * (stringLength(b.sValue) + logSize(a.iValue)) + 1);
                if (result->sValue != NULL)
                {
                    for (int i = logSize(a.iValue) - 1; i >= 0; i--, tmp++)
                    {
                        result->sValue[tmp] = logScale(a.iValue, i) + '0';
                    }
                    for (int i = 0; b.sValue[i] != 0; i++, tmp++)
                    {
                        result->sValue[tmp] = b.sValue[i];
                    }
                    result->sValue[tmp] = '\0';
                }
                result->type = 1;
                break;
            case '-':
                //except error
                break;
            case '*':
                //except error
                break;
            case '/':
                //except error
                break;
            }
            break;
        }
        break;
    case 1:
        switch (b.type)
        {
        case 0:
            //string and int
            switch (op)
            {
            case '+':
                free(result->sValue); // (대충 글자 크기가 다르니 버리고 새로 만든다는 내용)
                result->sValue = malloc(sizeof(char) * (stringLength(a.sValue) + logSize(b.iValue)) + 1);
                if (result->sValue != NULL)
                {
                    for (int i = 0; a.sValue[i] != 0; i++, tmp++)
                    {
                        result->sValue[tmp] = a.sValue[i];
                    }
                    for (int i = logSize(b.iValue) - 1; i >= 0; i--, tmp++)
                    {
                        result->sValue[tmp] = logScale(b.iValue, i) + '0';
                    }
                    result->sValue[tmp] = '\0';
                }
                result->type = 1;
                break;
            case '-':
                //except error
                break;
            case '*':
                free(result->sValue); // (대충 글자 크기가 다르니 버리고 새로 만든다는 내용)
                result->sValue = malloc(sizeof(char) * (stringLength(a.sValue) * b.iValue) + 1);
                if (result->sValue != NULL)
                {
                    for (int j = 0; j < b.iValue; j++)
                    {
                        for (int i = 0; a.sValue[i] != 0; i++, tmp++)
                        {
                            result->sValue[tmp] = a.sValue[i];
                        }
                    }
                    result->sValue[tmp] = '\0';
                }
                result->type = 1;
                break;
            case '/':
                //except error
                break;
            }
            break;
        case 1:
            //string and string
            switch (op)
            {
            case '+':
                free(result->sValue); // (대충 글자 크기가 다르니 버리고 새로 만든다는 내용)
                result->sValue = malloc(sizeof(char) * (stringLength(a.sValue) + logSize(b.iValue)) + 1);
                if (result->sValue != NULL)
                {
                    for (int i = 0; a.sValue[i] != 0; i++, tmp++)
                    {
                        result->sValue[tmp] = a.sValue[i];
                    }
                    for (int i = 0; b.sValue[i] != 0; i++, tmp++)
                    {
                        result->sValue[tmp] = b.sValue[i];
                    }
                    result->sValue[tmp] = '\0';
                }
                result->type = 1;
                break;
            case '-':
                //except error
                break;
            case '*':
                //except error
                break;
            case '/':
                //except error
                break;
            }
            break;
        }
        break;
    }
}
void getValueinFactor(factor* result) //배열 아님!!
{
    stack newStack[20];
    int sts = -1, temp = 0;
    char inputMod = 0; //0 : 기본 1 : numbericValue 2 : stringValue 3 : variable
    for (int i = 0; i < result->endF - result->startF; i++)
    {
        char iv = result->startF[i];
        //printf("%d ", i);
        switch (inputMod)
        {
        case 0:
            if (iv >= '0' && iv <= '9')
            {
                inputMod = 1;
                sts++;
                newStack[sts].iValue = iv - '0';
                newStack[sts].type = 1;
            }
            else if (iv == '"')
            {
                inputMod = 2;
                sts++;
                newStack[sts].type = 2;
                newStack[sts].sValue = malloc(stringLengthQ(&result->startF[i]) + 1);
                if (newStack[sts].sValue == NULL) return;
                temp = 0;
            }
            else if (iv == '+' || iv == '-' || iv == '*' || iv == '/' || iv == '(' || iv == ')')
            {
                sts++;
                newStack[sts].type = 4;
                newStack[sts].oValue = iv;
            }
            else if (iv == ' ') { } //아무 특정 입력도 없을 때 띄어쓰기는 딱히 상관 없음.
            else //변수.
            {
                inputMod = 3;
                sts++;
                newStack[sts].type = 3;
                newStack[sts].sValue = malloc(sizeof(char) * 240);
                if (newStack[sts].sValue == NULL) return;
                for (int i = 0; i < 240; i++) newStack[sts].sValue[i] = '\0';
                temp = 0;
                newStack[sts].sValue[temp] = iv;
                temp++;
            } 
            break;
        case 1:
            if (iv >= '0' && iv <= '9')
            {
                newStack[sts].iValue *= 10;
                newStack[sts].iValue += iv - '0';
            }
            else if (iv == '+' || iv == '-' || iv == '*' || iv == '/' || iv == '(' || iv == ')')
            {
                sts++;
                newStack[sts].type = 4;
                newStack[sts].oValue = iv;
                inputMod = 0;
            }
            else if (iv == ' ')
            {
                inputMod = 0;
            }
            else { } //구문 오류!
            break;
        case 2:
            if (iv == '"')
            {
                newStack[sts].sValue[temp] = '\0';
                inputMod = 0;
            }
            else
            {
                newStack[sts].sValue[temp] = iv;
                temp++;
            }
            break;
        case 3:
            if (iv == '+' || iv == '-' || iv == '*' || iv == '/' || iv == '(' || iv == ')')
            {
                sts++;
                newStack[sts].type = 4;
                newStack[sts].oValue = iv;
                inputMod = 0;
            }
            else if (iv == ' ')
            {
                inputMod = 0;
            }
            else
            {
                newStack[sts].sValue[temp] = iv;
                temp++;
            }
            break;
        }
    }
    variable varStack[20];
    int varLast = 0;
    char operatorStack[20] = "\0";
    int operatorLast = 0;
    int prio;
    //https://penglog.tistory.com/99 센세 감사합니다
    for (int q = 0; q < sts + 1; q++)
    {
        switch (newStack[q].type)
        {
        case 1: //numberic
            varStack[varLast].type = 0;
            varStack[varLast].iValue = newStack[q].iValue;
            varLast++;
            break;
        case 2: //string 
            varStack[varLast].type = 1;
            varStack[varLast].sValue = newStack[q].sValue;
            varLast++;
            break;
        case 3: //variable 
            varStack[varLast].type = 2;
            varStack[varLast].vValue = getVariable(newStack[q].sValue);
            if (varStack[varLast].vValue == NULL) varStack[varLast].vValue = makeVariable(newStack[q].sValue);
            varLast++;
            break;
        case 4: //operator
            switch (newStack[q].oValue)
            {
            case '(': // 일단 써놓고 ')' 나온 뒤에 사용
                operatorStack[operatorLast] = '(';
                operatorLast++;
                break;
            case ')': // 문자열 반복하면서 '(' 나올 때까지 연산
                while (operatorLast > 0 && operatorStack[operatorLast - 1] != '(')
                {
                    varLast--;
                    operatorLast--;
                    operate(varStack[varLast - 1], varStack[varLast], operatorStack[operatorLast], &varStack[varLast - 1]);
                }
                operatorLast--; // 다 뺐으니까 '(' 없앰.
                break;
            default:
                prio = getPriority(newStack[q].oValue);
                //지금 들어가는 거보다 우선순위 높은거 다 계산하고 들어감.
                while (operatorLast != 0 && prio <= getPriority(operatorStack[operatorLast - 1]))
                {
                    varLast--;
                    operatorLast--;
                    if (varLast <= 0 || operatorLast < 0) break; //오류 : 변수가 2개 이상 없거나 연산자가 1개 이상 없을 때
                    operate(varStack[varLast - 1], varStack[varLast], operatorStack[operatorLast], &varStack[varLast - 1]);
                }
                operatorStack[operatorLast] = newStack[q].oValue;
                operatorLast++;
                break;
            }
            break;
        }
    }
    while (varLast > 0 && operatorLast > 0) //남은 문자 계산
    {
        varLast--;
        operatorLast--;
        operate(varStack[varLast - 1], varStack[varLast], operatorStack[operatorLast], &varStack[varLast - 1]);
    }
    result->value = varStack[0];
    //printf("\n");
}

#include "functions.h"
void annyCore_init()
{
#include "funS.txt"
}
variable getFV(function* fun, int i)
{
    return fun->factors[i].value;
}
int useFunction(function* fn)
{
    char* dName = fn->define.name;
    if (isMatch(dName, "되풀이"))      { Function_Loop     (fn);                         return 1; }

    if (isMatch(dName, "말하기"))      { Function_Say      (getFV(fn, 0));               return 0; }
    if (isMatch(dName, "표시하기"))    { Function_Print    (getFV(fn, 0), getFV(fn, 1)); return 0; }
    if (isMatch(dName, "도움"))        { Function_Help     ();                           return 0; }

    if (isMatch(dName, "정하기"))      { Function_Set      (getFV(fn, 0), getFV(fn, 1)); return 0; }
    if (isMatch(dName, "더하기"))      { Function_Add      (getFV(fn, 0), getFV(fn, 1)); return 0; }
    if (isMatch(dName, "빼기"))        { Function_Minus    (getFV(fn, 0), getFV(fn, 1)); return 0; }
    if (isMatch(dName, "곱하기"))      { Function_Multi    (getFV(fn, 0), getFV(fn, 1)); return 0; }
    if (isMatch(dName, "나누기"))      { Function_Devide   (getFV(fn, 0), getFV(fn, 1)); return 0; }

    return -1;
}
void freeFunction(function* funNow)
{
    for (int i = 0; i < funNow->define.argsCount; i++)
    {
        if(funNow->factors[i].value.type == 1)
            free(funNow->factors[i].value.sValue);
    }
    free(funNow->factors);
    free(funNow);
}
function* functions[20];
int funC = 0;
int temp[20] = { 0 };
int ind = 0;
int anyFunction(char* line)
{
    def defNow = getdefbyStr(line);
    if (ind == 0)
    {
        if (errorExcept != 0) return 0;
        functions[funC] = malloc(sizeof(function));
        if (functions[funC] == NULL) return 0;

        getfunbyDef(defNow, line, functions[funC]);
        splitFactors(*functions[funC], line);
        for (int i = 0; i < defNow.argsCount; i++)
        {
            if (functions[funC]->factors[i].isMatched == 0) continue; // 없는 인수는 그냥 넘어간다.
            //sayAtoB(funNow.factors[i].startF, funNow.factors[i].endF);
            getValueinFactor(&functions[funC]->factors[i]);
            functions[funC]->factors[i].value.isMatched = 1;
        }
        ind += useFunction(functions[funC]);
        if (ind == 0) freeFunction(functions[funC]);
    }
    else
    {
        if (isMatch(defNow.name, "여기까지"))
        {
            ind--;
            if (ind == 0)
            {
                funC++;
                //printf("%d %d ", functions[funC]->factors[1].value.iValue, temp);
                variable* v = functions[funC - 1]->factors[0].value.vValue;
                v->iValue = 0;
                for (int i = 0; i < functions[funC - 1]->factors[1].value.iValue; i++)
                {
                    for (int j = 0; j < temp[funC - 1]; j++)
                    {
                        //printf("%s %d\n", functions[funC]->moon[j], ind);
                        anyFunction(functions[funC - 1]->moon[j]);
                    }
                    v->iValue++;
                }
                funC--;
                for (int i = 0; i < temp[funC]; i++)
                    free(functions[funC]->moon[i]);
                free(functions[funC]);
                temp[funC] = 0;;
            }
            else
            {
                ind += defNow.useindent;
                functions[funC]->moon[temp[funC]] = malloc(sizeof(char) * 240);
                for (int i = 0; line[i - 1] != 0; i++) functions[funC]->moon[temp[funC]][i] = line[i];
                temp[funC]++;
            }
        }
        else
        {
            ind += defNow.useindent;
            functions[funC]->moon[temp[funC]] = malloc(sizeof(char) * 240);
            for (int i = 0; line[i - 1] != 0; i++) functions[funC]->moon[temp[funC]][i] = line[i];
            temp[funC]++;
        }
    }
    return ind;
}
///Todo : 예제 만들기 / 스파게티 정리 / 조건문