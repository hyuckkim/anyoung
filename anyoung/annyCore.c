#include "operator.h"

variable* GetArgument(char* name);
void getValueinFactor(factor* result) //배열 아님
{
    stack newStack[20];
    int sts = -1, temp = 0;
    char inputMod = 0; //0 : 기본 1 : numbericValue 2 : stringValue 3 : variable
    for (int i = 0; i < result->endF - result->startF; i++)
    {
        char iv = result->startF[i];
        //printf("%c", iv);
        switch (inputMod)
        {
        case 0:
            if (iv >= '0' && iv <= '9')
            {
                inputMod = 1;
                sts++;
                newStack[sts].iValue = iv - '0';
                newStack[sts].type = iV;
            }
            else if (iv == '"')
            {
                inputMod = 2;
                sts++;
                newStack[sts].type = sV;
                newStack[sts].sValue = malloc(stringLength(&result->startF[i], '"') + 1);
                if (newStack[sts].sValue == NULL) return;
                temp = 0;
            }
            else if (isOperator(iv))
            {
                sts++;
                newStack[sts].type = oV;
                newStack[sts].oValue = iv;
            }
            else if (iv == ' ' || iv == '\t') { } //아무 특정 입력도 없을 때 띄어쓰기는 딱히 상관 없음.
            else //변수.
            {
                inputMod = 3;
                sts++;
                newStack[sts].type = vV;
                newStack[sts].vValue = malloc(sizeof(char) * lineLength);
                if (newStack[sts].vValue == NULL) return;
                for (int i = 0; i < lineLength; i++) newStack[sts].vValue[i] = '\0';
                temp = 0;
                newStack[sts].vValue[temp] = iv;
                temp++;
            } 
            break;
        case 1:
            if (iv >= '0' && iv <= '9')
            {
                newStack[sts].iValue *= 10;
                newStack[sts].iValue += iv - '0';
            }
            else if (isOperator(iv))
            {
                sts++;
                newStack[sts].type = oV;
                newStack[sts].oValue = iv;
                inputMod = 0;
            }
            else if (iv == ' ' || iv == '\t')
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
            if (isOperator(iv))
            {
                sts++;
                newStack[sts].type = oV;
                newStack[sts].oValue = iv;
                inputMod = 0;
            }
            else if (iv == ' ' || iv == '\t')
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
    sts += 1;

    // =============================== 구분선 ==============================

    variable* valueStack[stackLength];
    int varCount = 0;
    char operatorStack[stackLength] = "\0";
    int opCount = 0;
    int prio;
    //https://penglog.tistory.com/99 센세 감사합니다

    for (int q = 0; q < sts; q++) //각 스택에 대해 반복
    {
        if (varCount >= stackLength) { // 스택에 값이 너무 많으면 
            printf("error except in getValueInFactor");
            break;
        }
        if (newStack[q].type == oV)
        {
            switch (newStack[q].oValue)
            {
            case '(': // 일단 써놓고 ')' 나온 뒤에 사용
                operatorStack[opCount] = '(';
                opCount++;
                break;
            case ')': // 문자열 반복하면서 '(' 나올 때까지 연산
                while (opCount > 0 && operatorStack[opCount - 1] != '(')
                {
                    varCount--;
                    opCount--;
                    variable* temp = operate(valueStack[varCount - 1], valueStack[varCount], operatorStack[opCount]);
                    if (temp != NULL)
                    {
                        free(valueStack[varCount - 1]);
                        free(valueStack[varCount]);
                        valueStack[varCount - 1] = temp;
                        valueStack[varCount] = NULL;
                    }
                }
                opCount--; // 다 뺐으니까 '(' 없앰.
                break;
            case '{': // 일단 써놓고 '}' 나온 뒤에 사용
                operatorStack[opCount] = '{';
                opCount++;
                break;
            case '}': // 문자열 반복하면서 '{' 나올 때까지 연산
                while (opCount > 0 && operatorStack[opCount - 1] != '{')
                {
                    varCount--;
                    opCount--;
                    variable* temp = operate(valueStack[varCount - 1], valueStack[varCount], operatorStack[opCount]);
                    if (temp != NULL)
                    {
                        free(valueStack[varCount - 1]);
                        free(valueStack[varCount]);
                        valueStack[varCount - 1] = temp;
                        valueStack[varCount] = NULL;
                    }
                }
                opCount--; // 다 뺐으니까 '(' 없앰.
                valueStack[varCount - 1]->type = vV;
                valueStack[varCount - 1]->vValue = getVar(valueStack[varCount - 1]->sValue);
                break;
            default:
                prio = getPriority(newStack[q].oValue);
                //지금 들어가는 거보다 우선순위 높은거 다 계산하고 들어감.
                while (opCount != 0 && prio <= getPriority(operatorStack[opCount - 1]))
                {
                    varCount--;
                    opCount--;
                    if (varCount <= 0 || opCount < 0) break; //오류 : 변수가 2개 이상 없거나 연산자가 1개 이상 없을 때
                    variable* temp = operate(valueStack[varCount - 1], valueStack[varCount], operatorStack[opCount]);
                    if (temp != NULL)
                    {
                        free(valueStack[varCount - 1]);
                        free(valueStack[varCount]);
                        valueStack[varCount - 1] = temp;
                        valueStack[varCount] = NULL;
                    }
                }
                operatorStack[opCount] = newStack[q].oValue;
                opCount++;
                break;
            }
        }
        else
        {
            valueStack[varCount] = setFactor(newStack[q]);
            varCount++;
        }
    }
    while (varCount > 1 && opCount > 0) //남은 문자 계산
    {
        // 예를 들어서 개수가 3개 남아서 varCount가 3일때 1 빼서 2로 만들고 1번 2번 가지고.
        varCount--;
        opCount--;
        variable* temp = operate(valueStack[varCount - 1], valueStack[varCount], operatorStack[opCount]);
        if (temp != NULL)
        {
            free(valueStack[varCount - 1]);
            free(valueStack[varCount]);
            valueStack[varCount - 1] = temp;
            valueStack[varCount] = NULL;
        }
    }
    result->value = *valueStack[0];
    //printf("\n");
}
