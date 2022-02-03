#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "operator.h"
#include "types.h"
#include "usevariable.h"
#include "usefunction.h"
#include "kinput.h"

def* defs;
int defC = 0;
int defM = 1;
function* funLoopingNow = NULL;

extern function* LastF;
extern int ind;

#define DEFNOW defs[defC]
#define IS_CLEARED DEFNOW.args != NULL && DEFNOW.argNameCount != NULL
extern variable* vars;
extern char** varNames;
extern int varC;
extern int varM;
extern function* funLoopingNow;

extern int canInsert;

bool itCanInt(const char* chars)
{
    for (int i = 0; chars[i] != 0; i++)
        if (chars[i] > '9' || chars[i] < '0') return false;
    return true;
}
int getIntinStr(const char* chars)
{
    int result = 0;
    for (int i = 0; chars[i] != 0; i++)
    {
        result *= 10;
        result += chars[i] - '0';
    }
    return result;
}

int Function_User(function* fn)
{
    funLoopingNow = fn;
    for (int i = 0; i < fn->define->lineCount; i++)
    {
        anyFunction(fn->define->line[i]);
    }
    funLoopingNow = 0;
    return 0;
}
int Function_Help(function* fn)
{
    printf("\n흐름\n");
    printf("여기까지 \t\t\t흐름 함수를 어디까지 실행할지의 조건이 됩니다.\n\n");
    printf("[ㅁ 로/으로] ㅇ 번 되풀이 \t'여기까지' 까지의 함수를 ㅇ번 실행합니다. ㅁ에 동작 횟수를 0부터 기록합니다.\n");
    printf("ㅁ 면/이면 조건\t\t\tㅁ가 숫자고 0이 아니면 '여기까지' 까지의 함수를 실행합니다.\n");
    printf("아니면\t\t\t\t조건과 여기까지 사이에 넣어 함수를 실행할지를 반전합니다.\n\n");
    printf("ㅁ 이라는/라는 동작\t\tㅁ 라는 문자열로 함수를 정의합니다.\n");
    printf("ㅁ 을/를 [ㅇ 로/으로] 인수\t함수의 인수를 설정합니다. 'ㅂ 와/나' 로 여러 조사를 받게 할 수 있습니다.\n");
    printf("ㅁ 에 ㅇ 이 있는지\t\t\t인수로 ㅇ이 있으면 1, 없으면 0을 ㅁ에 출력합니다.\n");
    printf("ㅁ 을/를 읽어오기 \t\tㅁ이라는 이름의 안녕 파일을 읽어 실행합니다.\n");
    printf("\n데이터\n");
    printf("ㅁ 을/를 ㅇ으로/로 정하기\t변수 ㅁ의 값을 ㅇ로 지정합니다. ㅁ이 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 더하기\t\t변수 ㅁ의 값에 ㅇ를 더합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 빼기\t\t변수 ㅁ의 값에 ㅇ를 뺍니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 곱하기\t\t변수 ㅁ의 값에 ㅇ를 곱합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 나누기\t\t변수 ㅁ의  값에 ㅇ를 나눕니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("\n화면 입출력\n");
    printf("ㅁ 에 듣기\t\t\t화면에서 입력을 받아 변수 ㅁ에 전달합니다.\n");
    printf("ㅁ 을/를 [조용히] [ㅇ 번] 말하기ㅁ을 개행문자와 함께 출력합니다. '조용히' 와 사용되면 개행문자 없이 출력합니다.\n");
    printf("도움\t\t\t\t함수에 대한 도움말을 봅니다.\n");
    return 0;
}
int Function_Loop(function* fn)
{
    fn->moon = (char **) malloc(sizeof(char* ) * moonLength);
    canInsert = 1;
    fn->temp = 0;
    return 1;
}
int Function_If(function* fn)
{
    fn->moon = (char**) malloc(sizeof(char*) * moonLength);
    fn->factors[0].value = itisRValue(&fn->factors[0].value);
    if (fn->factors[0].value.type == iV && fn->factors[0].value.iValue != 0) // 0이 아닌 int value : true.
        canInsert = 1;
    else
        canInsert = 0; //조건문 시작할 때 조건 비교해서 틀리면 아예 메모리에 저장 안함.
    fn->temp = 0;
    return 1;
}
int Function_Loop_end(function* fn)
{
    fn->factors[0].value = itisLValue(&fn->factors[0].value);
    fn->factors[1].value = itisRValue(&fn->factors[1].value);
    ind--; //함수들을 모두 실행해야 되니 임시로 === 
    if (fn->factors[0].value.isMatched)
    {
        variable* v = fn->factors[0].value.vValue;
        v->iValue = 0;
        for (int i = 0; i < fn->factors[1].value.iValue; i++) //v번
        {
            for (int j = 0; j < fn->temp; j++) //각 함수 실행
                anyFunction(fn->moon[j]);
            v->iValue++;
        }
    }
    else
    {
        for (int i = 0; i < fn->factors[1].value.iValue; i++) //v번
        {
            for (int j = 0; j < fn->temp; j++) //각 함수 실행
                anyFunction(fn->moon[j]);
        }
    }   
    for (int i = 0; i < fn->temp; i++) {
        free(fn->moon[i]);
        fn->moon[i] = NULL;
    }
    ind++; // 임시로 함수 실행하는 거 끝났으니 === 
    return -1;
}
int Function_If_end(function* fn)
{
    variable* v = &fn->factors[0].value;
    ind--; //함수들을 모두 실행해야 되니 임시로 === 
    for (int j = 0; j < fn->temp; j++) //각 함수 실행
        anyFunction(fn->moon[j]);
    for (int i = 0; i < fn->temp; i++) {
        free(fn->moon[i]);
        fn->moon[i] = NULL;
    }
    ind++; // 임시로 함수 실행하는 거 끝났으니 === 
    return -1;
}
void SetData(const char* name, int args, int options, int useIndents, bool usecondits);
void DefineInserted();
int Function_fun(function* fn)
{
    fn->moon = (char **) malloc(sizeof(char*) * moonLength);
    canInsert = 1;
    fn->temp = 0;
    
    fn->factors[0].value = itisRValue(&fn->factors[0].value);
    SetData(fn->factors[0].value.sValue, 8, 8, false, false); //실제 인수 개수에 안맞추고 무조건 8개 8개 할당중임. 공간복잡도 이슈 생기면 여기 바꾸셈. 
    defs[defC].line = (char **) malloc(sizeof(char*) * 80);
    defs[defC].argsCount = 0;
    defs[defC].optionsCount = 0;
    defs[defC].lineCount = 0;
    defs[defC].fun = Function_User;
    return 1;
}
int Function_condition(function* fn)
{
    if (!isMatch(LastF->name, "동작")) return 0;
    if (!fn->factors[1].isMatched) // 조사가 없음 -> option으로 가야됨.
    {
        defs[defC].options[defs[defC].optionsCount] = setString(fn->factors[0].value.sValue);
        defs[defC].optionsCount++;
    }
    else //인수 하나 추가
    {
        int c = defs[defC].argsCount;
        int argCount = 0;
        defs[defC].argsName[c] = setString(fn->factors[0].value.sValue);

        for (argCount = 0; fn->factors[argCount + 1].isMatched; argCount++) 
        {} // 인수의 명칭 개수 구하기
        defs[defC].args[c] = (char **) malloc(sizeof(char**) * argCount);
        defs[defC].argNameCount[c] = argCount;

        for (int i = 0; i < argCount; i++)
            defs[defC].args[c][i] = setString(fn->factors[i + 1].value.sValue);

        defs[defC].argsCount++;
    }
    return 0;
}
int Function_fun_end(function* fn)
{
    if (fn->returnTo != 0) { //Todo : 기존 함수 삭제하고 새로운 함수 생성 가능하게?
        freeFunction(fn);
        return 0;
    }
    for (int i = 0; i < fn->temp; i++)
    {
        defs[defC].line[defs[defC].lineCount] = setString(fn->moon[i]);
        defs[defC].lineCount++;
    }
    DefineInserted();
    return -1;
}
int Function_end(function* fn)
{
    char* dName = LastF->name;
    if (isMatch(dName, "되풀이")) { Function_Loop_end(LastF);  return -1; }
    if (isMatch(dName, "조건"))   { Function_If_end(LastF);    return -1; }
    if (isMatch(dName, "동작"))   { Function_fun_end(LastF);   return -1; }
    return 0;
}
int Function_not(function* fn) {
    canInsert = 1 - canInsert;
    return 0;
}
int Function_sub(function* fn)
{
    return 0;
}

int Function_include(function* fn)
{
    variable value = fn->factors[0].value;
    itisRValue(&value);
    if (value.type != sV) return 0;

    FILE* stream;
    char chars[lineLength];
    if (fopen_s(&stream, value.sValue, "r") == 0 && stream != NULL)
    {
        while (fgets(chars, lineLength, stream) != NULL)
        {
            ChangeLFtoNULL(chars);
            anyFunction(chars);
        }
        fclose(stream);
    }
    return 0;
}
int Function_valid(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    for (int i = 0; i < funLoopingNow->define->argsCount; i++)
    {
        if (isMatch(value2.sValue, funLoopingNow->define->argsName[i]))
        {
            value1.vValue->iValue = funLoopingNow->factors[i].isMatched;
            value1.vValue->type = iV;
            return 0;
        }
    }
    for (int i = 0; i < funLoopingNow->define->optionsCount; i++)
    {
        if (isMatch(value2.sValue, funLoopingNow->define->options[i]))
        {
            //printf("%d", funLoopingNow->options[i].isMatched);
            value1.vValue->iValue = funLoopingNow->options[i].isMatched;
            value1.vValue->type = iV;
            return 0;
        }
    }
    return 0;
}
int Function_Set(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    switch (value2.type)
    {
    case iV:
        value1.vValue->type = iV;
        value1.vValue->iValue = value2.iValue;
        break;
    case sV:
        value1.vValue->type = sV;
        value1.vValue->sValue = setString(value2.sValue);
        break;
    }
    return 0;
}
int Function_Add(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue += value2.iValue;
    }
    return 0;
}
int Function_Minus(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue -= value2.iValue;
    }
    return 0;
}
int Function_Multi(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue *= value2.iValue;
    }
    return 0;
}
int Function_Devide(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue /= value2.iValue;
    }
    return 0;
}
int Function_Listen(function* fn)
{
    variable value = itisLValue(&fn->factors[0].value);
    char* cc = (char *) malloc(lineLength);
    getSO(cc, "");
    ChangeLFtoNULL(cc);

    if (itCanInt(cc))
    {
        value.vValue->iValue = getIntinStr(cc);
        value.vValue->type = iV;
    }
    else
    {
        value.vValue->sValue = setString(cc);
        value.vValue->type = sV;
    }
    return 0;
}
int Function_Cutstr(function* fn) // ~에서 ~로 [N글자만큼] 잘라내기
{
    variable newV = itisLValue(&fn->factors[1].value);
    variable oldV = itisLValue(&fn->factors[0].value);
    if (oldV.type != vV) return 0;
    if (oldV.vValue->type != sV) return 0;

    int fds = stringLength(oldV.vValue->sValue, 0);
    char* newStr = (char *) malloc(fds);

    size_t bts = getitsbyte(oldV.vValue->sValue[0]);
    char* dropStr = (char *) malloc(bts + 1);
    int i;
    for (i = 0; i < bts; i++) {
        dropStr[i] = oldV.vValue->sValue[i];
    }
    dropStr[i] = '\0';
    if (newV.vValue->type == sV) 
        free(newV.vValue->sValue);
    newV.vValue->type = sV;
    newV.vValue->sValue = dropStr;
    newStr = setString(&oldV.vValue->sValue[fds]);
    free(oldV.vValue->sValue);
    oldV.vValue->sValue = newStr;
    return 0;
}
int Function_Say(function* fn)
{
    variable value = itisRValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    bool loop = value2.isMatched;
    for (int i = 0; i < (loop ? value2.iValue : 1); i++)
    {
        if (value.type == iV)
            printf("%d", value.iValue);
        else if (value.type == sV)
            printf("%s", value.sValue);
    }
    if (!fn->options[0].isMatched)
    {
        printf("\n");
    }
    return 0;
}
int Function_Print(function* fn)
{
    variable value1 = itisRValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value2.isMatched)
    {
        for (int i = 0; i < value2.iValue; i++)
        {
            if (value1.type == iV)
                printf("%d", value1.iValue);
            else if (value1.type == sV)
                printf("%s", value1.sValue);
        }
    }
    else
    {
        if (value1.type == iV)
            printf("%d", value1.iValue);
        else if (value1.type == sV)
            printf("%s", value1.sValue);
    }
    printf("\n");
    return 0;
}
void SetData(const char* name, int args, int options, int useIndents, bool usecondits)
{
    DEFNOW.name = setString(name);
    DEFNOW.argsCount = args;
    DEFNOW.argsName = (char**)malloc(sizeof (char*) * args);
    DEFNOW.args = (char ***) malloc(sizeof(char**) * args);
    DEFNOW.argNameCount = (int *) malloc(sizeof(int) * args);

    DEFNOW.optionsCount = options;
    DEFNOW.options = (char **) malloc(sizeof(char*) * options);
    DEFNOW.useindent = useIndents;
    DEFNOW.usecondit = usecondits;
}
void SetArgs(int o, int c, ...)
{
    va_list v;
    va_start(v, c);
    DEFNOW.argNameCount[o] = c;
    DEFNOW.args[o] = (char **) malloc(sizeof(char*) * c);
    if (DEFNOW.args[o] != NULL)
        for (int i = 0; i < c; i++)
        {
            DEFNOW.args[o][i] = setString(va_arg(v, char*));
        }
}
void SetOptions(int c, ...)
{
    va_list v;
    va_start(v, c);
    if (DEFNOW.options != NULL)
    {
        for (int i = 0; i < c; i++)
        {
            DEFNOW.options[i] = setString(va_arg(v, char*));
        }
    }
}
//프로그램 실행에 필요한 기본 함수 정보들을 초기화한다.
int Anyoung_Init()
{
    defs = (def *) malloc(sizeof(def));
    vars = (variable *) malloc(sizeof(variable));
    if (defs == NULL || vars == NULL) return -1;
    varNames = (char **) malloc(sizeof(char*));

    SetData("말하기", 2, 1, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "번");
        SetOptions(1, "조용히");
    }
    DEFNOW.fun = Function_Say;
    DefineInserted();

    SetData("듣기", 1, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 1, "에");
    }
    DEFNOW.fun = Function_Listen;
    DefineInserted();

    SetData("도움", 0, 0, 0, false);
    DEFNOW.fun = Function_Help;
    DefineInserted();

    SetData("정하기", 2, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
    }
    DEFNOW.fun = Function_Set;
    DefineInserted();

    SetData("더하기", 2, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Add;
    DefineInserted();

    SetData("빼기", 2, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Minus;
    DefineInserted();

    SetData("곱하기", 2, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Multi;
    DefineInserted();

    SetData("나누기", 2, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Devide;
    DefineInserted();

    SetData("되풀이", 2, 0, 1, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "로", "으로");
        SetArgs(1, 1, "번");
    }
    DEFNOW.fun = Function_Loop;
    DefineInserted();

    SetData("조건", 1, 0, 1, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "면", "이면");
    }
    DEFNOW.fun = Function_If;
    DefineInserted();

    SetData("여기까지", 0, 0, -1, true);
    DEFNOW.fun = Function_end;
    DefineInserted();

    SetData("아니면", 0, 0, 0, true);
    DEFNOW.fun = Function_not;
    DefineInserted();

    SetData("잘라내기", 2, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 1, "에서");
        SetArgs(1, 2, "로", "으로");
    }
    DEFNOW.fun = Function_Cutstr;
    DefineInserted();

    SetData("동작", 1, 0, 1, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "이라는", "라는");
    }
    DEFNOW.fun = Function_fun;
    DefineInserted();

    SetData("인수", 5, 0, 0, true);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
        SetArgs(2, 2, "와", "나");
        SetArgs(3, 2, "와", "나");
        SetArgs(4, 2, "와", "나");
    }
    DEFNOW.fun = Function_condition;
    DefineInserted();

    SetData("있는지", 2, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 1, "에");
        SetArgs(1, 2, "이", "가");
    }
    DEFNOW.fun = Function_valid;
    DefineInserted();

    SetData("읽어오기", 1, 0, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
    }
    DEFNOW.fun = Function_include;
    DefineInserted();
    return 0;
}