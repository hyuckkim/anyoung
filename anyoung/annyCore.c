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
    variable valueStack[stackLength];
    int varLast = 0;
    char operatorStack[stackLength] = "\0";
    int operatorLast = 0;
    int prio;
    //https://penglog.tistory.com/99 센세 감사합니다
    for (int q = 0; q < sts + 1; q++)
    {
        switch (newStack[q].type)
        {
        case iV: //numberic
            valueStack[varLast].type = iV;
            valueStack[varLast].iValue = newStack[q].iValue;
            varLast++;
            break;
        case sV: //string 
            valueStack[varLast].type = sV;
            valueStack[varLast].sValue = newStack[q].sValue;
            varLast++;
            break;
        case vV: //variable 
            valueStack[varLast].type = vV;
            valueStack[varLast].vValue = getVar(newStack[q].vValue);
            varLast++;
            break;
        case oV: //operator
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
                    valueStack[varLast - 1] = operate(valueStack[varLast - 1], valueStack[varLast], operatorStack[operatorLast]);
                }
                operatorLast--; // 다 뺐으니까 '(' 없앰.
                break;
            case '{': // 일단 써놓고 '}' 나온 뒤에 사용
                operatorStack[operatorLast] = '{';
                operatorLast++;
                break;
            case '}': // 문자열 반복하면서 '{' 나올 때까지 연산
                while (operatorLast > 0 && operatorStack[operatorLast - 1] != '{')
                {
                    varLast--;
                    operatorLast--;
                    valueStack[varLast - 1] = operate(valueStack[varLast - 1], valueStack[varLast], operatorStack[operatorLast]);
                }
                operatorLast--; // 다 뺐으니까 '(' 없앰.
                valueStack[varLast - 1].type = vV;
                valueStack[varLast - 1].vValue = getVar(valueStack[varLast - 1].sValue);
                break;
            default:
                prio = getPriority(newStack[q].oValue);
                //지금 들어가는 거보다 우선순위 높은거 다 계산하고 들어감.
                while (operatorLast != 0 && prio <= getPriority(operatorStack[operatorLast - 1]))
                {
                    varLast--;
                    operatorLast--;
                    if (varLast <= 0 || operatorLast < 0) break; //오류 : 변수가 2개 이상 없거나 연산자가 1개 이상 없을 때
                    valueStack[varLast - 1] = operate(valueStack[varLast - 1], valueStack[varLast], operatorStack[operatorLast]);
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
        valueStack[varLast - 1] = operate(valueStack[varLast - 1], valueStack[varLast], operatorStack[operatorLast]);
    }
    result->value = valueStack[0];
    //printf("\n");
}

function* LastF;
int canInsert;
int ind = 0, igd = 0;
#include "functions.h"
#include "funS.h"
variable getFV(function* fun, int i)
{
    return fun->factors[i].value;
}
int useFunction_end(function* fn)
{
    char* dName = fn->name;
    if (isMatch(dName, "되풀이")) { Function_Loop_end(fn);  return 0; }
    if (isMatch(dName, "조건"))   { Function_If_end(fn);    return 0; }
    if (isMatch(dName, "동작"))   { Function_fun_end(fn);   return 0; }
    return -1;
}
void freeFunction(function* funNow)
{
    for (int i = 0; i < funNow->define->argsCount; i++)
    {
        if(funNow->factors[i].value.type == sV)
            free(funNow->factors[i].value.sValue);
    }
    free(funNow->factors);
    free(funNow);
}
int anyFunction(char* line)
{
    def defNow = getdefbyStr(line); // 함수 이름 인식
    if (ind == 0)
    {
        if (errorExcept != 0) return 0; //인식 실패시 나감.
        function* NewF = malloc(sizeof(function)); //공간 할당
        if (NewF == NULL) return 0; //공간 할당 성공했는지 확인

        NewF->returnTo = LastF; // 스택 구현 
        getfunbyDef(&defNow, line, NewF); // 인식한 함수 공간 만들기
        splitFactors(*NewF, line); // 단어 자르기
        for (int i = 0; i < defNow.argsCount; i++) // 인수별로
        {
            if (!NewF->factors[i].isMatched) continue; // 없는 인수는 넘어감
            getValueinFactor(&NewF->factors[i]); // 인수 계산
            NewF->factors[i].value.isMatched = true;
        }
        ind += defNow.fun(NewF); 
        if (ind == 0) freeFunction(NewF); // 함수 사용이 종료되면 삭제
        else LastF = NewF; //if 같은게 있으면 필요함.
    }
    else
    {
        if (ind == 1) //1단계 : 맞는 값만 넣어야 할 때
        {
            if (isMatch(defNow.name, "여기까지"))
            {
                if (igd == 0)
                {
                    ind--;
                    useFunction_end(LastF);
                }
                else igd--;
            }
            else if (isMatch(defNow.name, "아니면"))
            {
                canInsert = 1 - canInsert;
            }
            else if (canInsert == 1)
            {
                ind += defNow.useindent;
                LastF->moon[LastF->temp] = setString(line);
                LastF->temp++;
            }
            else igd += defNow.useindent;
        }
        else //2단계 이상 : 텍스트 형식으로 아무 값이나 넣어야 할 때
        {
            ind += defNow.useindent;
            LastF->moon[LastF->temp] = setString(line);
            LastF->temp++;
        }
    }
    return ind;
}