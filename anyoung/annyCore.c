#include "operator.h"

stack* InitFactorSliceData(const char* startF, const char* endF, int* index)
{
    stack* result = (stack*)malloc(sizeof(stack) * stackLength);
    if (result == NULL) return NULL;

    int sts = -1, temp = 0;
    char inputMod = 0; //0 : 기본 1 : numbericValue 2 : stringValue 3 : variable
    for (int i = 0; i < endF - startF; i++)
    {
        char iv = startF[i];
        //printf("%c", iv);
        switch (inputMod)
        {
        case 0:
            if (iv >= '0' && iv <= '9')
            {
                inputMod = 1;
                sts++;
                result[sts].iValue = iv - '0';
                result[sts].type = iV;
            }
            else if (iv == '"')
            {
                inputMod = 2;
                sts++;
                result[sts].type = sV;
                int num = stringLength(&startF[i + 1], '"') + 1;
                if (num == 1) return NULL;
                result[sts].sValue = malloc(num);
                if (result[sts].sValue == NULL) return NULL;
                temp = 0;
            }
            else if (isOperator(iv))
            {
                sts++;
                result[sts].type = oV;
                result[sts].oValue = iv;
            }
            else if (iv == ' ' || iv == '\t') {} //아무 특정 입력도 없을 때 띄어쓰기는 딱히 상관 없음.
            else //변수.
            {
                inputMod = 3;
                sts++;
                result[sts].type = vV;
                result[sts].vValue = malloc(sizeof(char) * lineLength);
                if (result[sts].vValue == NULL) return NULL;
                for (int i = 0; i < lineLength; i++) result[sts].vValue[i] = '\0';
                temp = 0;
                result[sts].vValue[temp] = iv;
                temp++;
            }
            break;
        case 1:
            if (iv >= '0' && iv <= '9')
            {
                result[sts].iValue *= 10;
                result[sts].iValue += iv - '0';
            }
            else if (isOperator(iv))
            {
                sts++;
                result[sts].type = oV;
                result[sts].oValue = iv;
                inputMod = 0;
            }
            else if (iv == ' ' || iv == '\t')
            {
                inputMod = 0;
            }
            else {} //구문 오류!
            break;
        case 2:
            if (iv == '"')
            {
                result[sts].sValue[temp] = '\0';
                inputMod = 0;
            }
            else
            {
                result[sts].sValue[temp] = iv;
                temp++;
            }
            break;
        case 3:
            if (isOperator(iv))
            {
                sts++;
                result[sts].type = oV;
                result[sts].oValue = iv;
                inputMod = 0;
            }
            else if (iv == ' ' || iv == '\t')
            {
                inputMod = 0;
            }
            else
            {
                result[sts].sValue[temp] = iv;
                temp++;
            }
            break;
        }
    }
    sts += 1;
    *index = sts;
    return result;
}
static variable* valueStack[stackLength] = { NULL };
static int varCount = 0;
static char operatorStack[stackLength] = "\0";
static int opCount = 0;

void pushValue(stack* item)
{
    if (valueStack[varCount] != NULL) 
        printf("Stack에서 오류가 발생했습니다 : 1\n");
    variable* v = (variable*)malloc(sizeof(variable));
    if (v == NULL) return;
    switch (item->type) {
    case iV:
        v->iValue = item->iValue;
        break;
    case sV:
        v->sValue = setString(item->sValue);
        break;
    case vV:
        v->vValue = getVar(item->vValue);
        break;
    }
    v->type = item->type;
    valueStack[varCount] = v;
    varCount++;
}
void pushValuePo(variable* point)
{
    if (valueStack[varCount] != NULL)
        printf("Stack에서 오류가 발생했습니다 : 2\n");
    valueStack[varCount] = point;
    varCount++;
}
variable popValue()
{
    varCount--;
    variable v = *valueStack[varCount];
    free(valueStack[varCount]);
    valueStack[varCount] = NULL;

    return v;
}
void pushOperator(stack* item)
{
    if (operatorStack[opCount] != '\0') 
        printf("Stack에서 오류가 발생했습니다 : 3\n");
    operatorStack[opCount] = item->oValue;
    opCount++;
}
char popOperator()
{
    opCount--;
    char c = operatorStack[opCount];
    operatorStack[opCount] = '\0';

    return c;
}

//(시작지검 startF와 종료지점 endF로 표현되는) 라인 문자열의 일부를 계산해 나타낸다.
variable getValueinFactor(const char* textStartF, const char* textEndF)
{
    int dataCount;
    stack* SliceData = InitFactorSliceData(textStartF, textEndF, &dataCount);
    
    int prio;
    varCount = 0;
    opCount = 0;
    //https://penglog.tistory.com/99 센세 감사합니다

    for (int q = 0; q < dataCount; q++) //각 스택에 대해 반복
    {
        if (varCount >= stackLength) { // 스택에 값이 너무 많으면 
            printf("error except in getValueInFactor");
            break;
        }
        stack dataNow = SliceData[q];
        if (dataNow.type == oV)
        {
            switch (dataNow.oValue)
            {
            case '(': // 일단 써놓고 ')' 나온 뒤에 사용
            case '{': // 일단 써놓고 '}' 나온 뒤에 사용
                pushOperator(&dataNow);
                break;
            case ')': // 문자열 반복하면서 '(' 나올 때까지 연산
                while (opCount > 0 && varCount > 1 && operatorStack[opCount - 1] != '(')
                {
                    variable b = popValue(), a = popValue();
                    char o = popOperator();
                    pushValuePo(operate(&a, &b, o));
                    if (a.type == sV) free(a.sValue);
                    if (b.type == sV) free(b.sValue);
                }
                popOperator(); // '(' 없앰.
                break;
            case '}': // 문자열 반복하면서 '{' 나올 때까지 연산
                while (opCount > 0 && varCount > 1 && operatorStack[opCount - 1] != '(')
                {
                    variable b = popValue(), a = popValue();
                    char o = popOperator();
                    pushValuePo(operate(&a, &b, o));
                    if (a.type == sV) free(a.sValue);
                    if (b.type == sV) free(b.sValue);
                }
                popOperator(); // '{' 없앰.
                valueStack[varCount - 1]->type = vV;
                valueStack[varCount - 1]->vValue = getVar(valueStack[varCount - 1]->sValue);
                break;
            default:
                prio = getPriority(dataNow.oValue);
                //지금 들어가는 거보다 우선순위 높은거 다 계산하고 들어감.
                while (opCount != 0 && prio <= getPriority(operatorStack[opCount - 1]))
                {
                    variable b = popValue(), a = popValue();
                    char o = popOperator();
                    pushValuePo(operate(&a, &b, o));
                    if (a.type == sV) free(a.sValue);
                    if (b.type == sV) free(b.sValue);
                }
                pushOperator(&dataNow);
                break;
            }
        }
        else
        {
            pushValue(&dataNow);
        }
    }
    while (varCount > 1 && opCount > 0) //남은 문자 계산
    {
        variable b = popValue(), a = popValue();
        char o = popOperator();
        pushValuePo(operate(&a, &b, o));
        if (a.type == sV) free(a.sValue);
        if (b.type == sV) free(b.sValue);
    }
    free(SliceData);
    return popValue();
}
