void operate(variable a, variable b, char op, variable *result)
{
    int tmp = 0;
    result->iValue = 0;
    result->sValue = 0;
    result->type = iV;
    if (a.type == vV)
    {
        a.type = a.vValue->type;
        if (a.type == iV) a.iValue = a.vValue->iValue;
        else if (a.type == sV) a.sValue = a.vValue->sValue;
    }
    if (b.type == vV)
    {
        b.type = b.vValue->type;
        if (b.type == iV) b.iValue = b.vValue->iValue;
        else if (b.type == sV) b.sValue = b.vValue->sValue;
    }
    switch (a.type)
    {
    case iV:
        switch (b.type)
        {
        case iV:
            //int and int
            switch (op)
            {
            case '+':
                result->type = iV;
                result->iValue = a.iValue + b.iValue;
                break;
            case '-':
                result->type = iV;
                result->iValue = a.iValue - b.iValue;
                break;
            case '*':
                result->type = iV;
                result->iValue = a.iValue * b.iValue;
                break;
            case '%':
                result->type = iV;
                result->iValue = a.iValue % b.iValue;
                break;
            case '/':
                result->type = iV;
                result->iValue = a.iValue / b.iValue;
                break;
            case '=':
                result->type = iV;
                result->iValue = a.iValue == b.iValue;
                break;
            case '>':
                result->type = iV;
                result->iValue = a.iValue > b.iValue;
                break;
            case '<':
                result->type = iV;
                result->iValue = a.iValue < b.iValue;
                break;
            }
            break;
        case sV:
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
                result->type = sV;
                break;
            case '-':
                //except error
                break;
            case '*':
                //except error
                break;
            case '%':
                //except error
                break;
            case '/':
                //except error
                break;
            case '=':
                break;
            case '>':
                break;
            case '<':
                break;
            }
            break;
        }
        break;
    case sV:
        switch (b.type)
        {
        case iV:
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
                result->type = sV;
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
                result->type = sV;
                break;
            case '%':
                //except error
                break;
            case '/':
                //except error
                break;
            case '=':
                break;
            case '>':
                break;
            case '<':
                break;
            }
            break;
        case sV:
            //string and string
            switch (op)
            {
            case '+':
                free(result->sValue); // (대충 글자 크기가 다르니 버리고 새로 만든다는 내용)
                result->sValue = malloc(sizeof(char) * (stringLength(a.sValue) + stringLength(b.sValue)) + 1);
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
                result->type = sV;
                break;
            case '-':
                //except error
                break;
            case '*':
                //except error
                break;
            case '%':
                //except error
                break;
            case '/':
                //except error
                break;
            case '=':
                result->type = iV;
                result->iValue = isMatch(a.sValue, b.sValue);
                break;
            case '>':
                break;
            case '<':
                break;
            }
            break;
        }
        break;
    }
}

variable* GetArgument(char* name);
function* funLoopingNow = 0;
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
                newStack[sts].type = iV;
            }
            else if (iv == '"')
            {
                inputMod = 2;
                sts++;
                newStack[sts].type = sV;
                newStack[sts].sValue = malloc(stringLengthQ(&result->startF[i]) + 1);
                if (newStack[sts].sValue == NULL) return;
                temp = 0;
            }
            else if (iv == '+' || iv == '-' || iv == '*' || iv == '%' || iv == '/' || iv == '(' || iv == ')' || iv == '=' || iv == '<' || iv == '>')
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
            else if (iv == '+' || iv == '-' || iv == '*' || iv == '%' || iv == '/' || iv == '(' || iv == ')' || iv == '=' || iv == '<' || iv == '>')
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
            if (iv == '+' || iv == '-' || iv == '*' || iv == '%' || iv == '/' || iv == '(' || iv == ')' || iv == '=' || iv == '<' || iv == '>')
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
    variable varStack[stackLength];
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
            varStack[varLast].type = iV;
            varStack[varLast].iValue = newStack[q].iValue;
            varLast++;
            break;
        case sV: //string 
            varStack[varLast].type = sV;
            varStack[varLast].sValue = newStack[q].sValue;
            varLast++;
            break;
        case vV: //variable 
            varStack[varLast].type = vV;
            varStack[varLast].vValue = getVariable(newStack[q].vValue);
            if (varStack[varLast].vValue == NULL && funLoopingNow != 0) varStack[varLast].vValue = GetArgument(newStack[q].vValue);
            if (varStack[varLast].vValue == NULL) varStack[varLast].vValue = makeVariable(newStack[q].vValue);
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

function* functions[stackLength];
int funC = 0;
int temp[stackLength] = { 0 };
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
    def defNow = getdefbyStr(line);
    if (ind == 0)
    {
        if (errorExcept != 0) return 0;
        functions[funC] = malloc(sizeof(function));
        if (functions[funC] == NULL) return 0;

        getfunbyDef(&defNow, line, functions[funC]);
        splitFactors(*functions[funC], line);
        for (int i = 0; i < defNow.argsCount; i++)
        {
            if (!functions[funC]->factors[i].isMatched) continue; // 없는 인수는 그냥 넘어간다.
            //sayAtoB(funNow.factors[i].startF, funNow.factors[i].endF);
            getValueinFactor(&functions[funC]->factors[i]);
            functions[funC]->factors[i].value.isMatched = true;
        }
        ind += defNow.fun(functions[funC]);
        if (ind == 0) freeFunction(functions[funC]);
    }
    else
    {
        //printf("%d %s, %d\n", ind, defNow.name, defNow.useindent);
        ///indent가 0이 아닐 때. 조건문, 반복문의 처리이다.
        ///여기의 핵심은 ind와 igd이다. ind는 indent의 줄임말로 깊이를 표시하고 igd는 ignored로 얼마만큼의 깊이를 무시할 것인지 표시한다.
        ///ind가 2이상이면 ind가 1이 될 때까지 다시 사용할 것이므로 모두 저장해야 한다. (맨 아래)
        ///ind가 1이면 저장해야 될 것만 (if가 사실인 것만) 저장해야 한다. 따라서 canInsert와 비교한다.
        ///무시된 문 중에도 여기까지를 사용하는 문이 있으므로 if가 거짓인 동안은 igd를 더해준다.
        if (ind == 1)
        {
            if (isMatch(defNow.name, "여기까지"))
            {
                if (igd == 0)
                {
                    ind--;
                    useFunction_end(functions[funC]);
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
                functions[funC]->moon[temp[funC]] = malloc(sizeof(char) * lineLength);
                for (int i = 0; line[i - 1] != 0; i++) functions[funC]->moon[temp[funC]][i] = line[i];
                temp[funC]++;
            }
            else igd += defNow.useindent;
        }
        else
        {
            ind += defNow.useindent;
            functions[funC]->moon[temp[funC]] = malloc(sizeof(char) * lineLength);
            for (int i = 0; line[i - 1] != 0; i++) functions[funC]->moon[temp[funC]][i] = line[i];
            temp[funC]++;
        }
    }
    return ind;
}
///Todo : 스파게티 정리 / 함수 / 다른 연산자 / 배열 / 구조체
//누가 http://www.no-smok.net/nsmk/%ED%95%9C%EA%B8%80%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D%EC%96%B8%EC%96%B4 ... 이미 생각해놨던 거다..