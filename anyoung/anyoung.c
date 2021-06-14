/// 2021년 3월 ~ 
/// 김광혁이 만듦.
/// 사용 운영체제 : Windows 10 64bit 20H2 19042.867
/// UTF-8 사용 beta 기능 사용시에만 사용 가능함
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "types.h"
#include "kinput.h"
#include "annyCore.h"
#include "annyCore.c"

#define SHUTDOWN 3

int useFunction(const char* line, def* define);
int saveFunction(const char* line, int indent, function* saveTo);
int anyFunction(char* line);
void freeFunction(function* funNow);
extern def getdefbyStr(char* str);
extern int errorExcept;
extern function* initFunction(def* define, const char* str);
extern void splitFactors(function fun, const char* str);

def* defs;
int defC = 0;
int defM = 1;
variable* vars;
char** varNames;
int varC;
int varM = 1;

function* LastF;
int canInsert;
int ind = 0;

extern void annyCore_init();

int main(int argc, char** argv)
{
    annyCore_init();
    char chars[lineLength] = "default";
    int indent = 1;
    FILE* stream = NULL;
    
    int getBy, getIn;
    if (argc == 1)
    {
        anyFunction("말하기 \"어순에 상관없는 한글 스크립트 언어 안녕\"을");
        anyFunction("말하기 \"v0.20 실행중\"을");
        anyFunction("말하기 \"'도움'으로 명령어 확인\"을");
        getBy = 0;
    }
    else
    {
        if (fopen_s(&stream, argv[1], "r") != 0 || stream == NULL) {
            printf("파일을 여는 데 실패하였습니다.");
            return 0;
        }
        getBy = 1;
    }
    
    while (1)
    {
        if (getBy == 0) {
            if (indent == 1) getIn = getSO(chars, ">>> ");
            else getIn = getSO(chars, "... ");
            if (getIn != 0) break;
        }
        else {
            getIn = (int) fgets(chars, lineLength, stream);
            if (getIn == 0) break;
        }
        changeSpacetoNull(chars);

        indent = anyFunction(chars) + 1;
    }
    if (stream != NULL) fclose(stream);
    return 0;
}

int anyFunction(char* line)
{
    def defNow = getdefbyStr(line); // 함수 이름 인식
    if (errorExcept != 0) return 0; //인식 실패시 나감.
    switch (ind)
    {
    case 0:
        useFunction(line, &defNow);
        break;
    case 1:
        if (defNow.usecondit)
            useFunction(line, &defNow);
        else
            if (canInsert) 
                saveFunction(line, defNow.useindent, LastF);
        break;
    default:
        saveFunction(line, defNow.useindent, LastF);
        break;
    }
    return ind;
}
int useFunction(const char* line, def* define) {

    function* NewF = initFunction(define, line); //공간 할당
    if (NewF == NULL) return -1; //공간 할당 성공했는지 확인

    NewF->returnTo = LastF; // 스택 구현 
    splitFactors(*NewF, line); // 단어 자르기
    for (int i = 0; i < define->argsCount; i++) // 인수별로
    {
        if (!NewF->factors[i].isMatched) continue; // 없는 인수는 넘어감
        getValueinFactor(&NewF->factors[i]); // 인수 계산
        NewF->factors[i].value.isMatched = true;
    }
    ind += define->fun(NewF);
    if (ind == 0 || define->usecondit) freeFunction(NewF); // 함수 사용이 종료되면 삭제
    else LastF = NewF; // if문 안의 함수가 끝나면.

    return 0;
}
int saveFunction(const char* line, int indent, function* saveTo) {
    ind += indent;
    saveTo->moon[saveTo->temp] = setString(line);
    saveTo->temp++;
    return 0;
}
void freeFunction(function* funNow)
{
    if (funNow->factors != NULL)
        free(funNow->factors);
    free(funNow);
    funNow = NULL;
}

variable* getVariable(char* name)
{
    for (int i = 0; i < varC; i++)
    {
        if (isMatch(varNames[i], name)) return &vars[i];
    }
    return NULL;
}
void VariableInserted()
{
    varC++;
    if (varC >= varM) {
        varM *= 2;
        variable* vTemp = (variable*)realloc(vars, varM * sizeof(variable));
        if (vTemp != NULL) vars = vTemp;
        char** nTemp = (char**)realloc(varNames, varM * sizeof(char*));
        if (nTemp != NULL) varNames = nTemp;
    }
}
variable* makeVariable(char* name)
{
    varNames[varC] = setString(name);
    vars[varC].type = iV;
    vars[varC].iValue = 0;
    VariableInserted();
    return &vars[varC - 1];
}
variable* setVariable(variable* var)
{
    vars[varC] = *var;
    VariableInserted();
    return &vars[varC - 1];
}
function* funLoopingNow = 0;
variable* GetArgument(char* name)
{
    //functions[funC]->factors[0].value.sValue
    for (int i = 0; i < funLoopingNow->define->argsCount; i++)
    {
        if (isMatch(funLoopingNow->define->argsName[i], name))
        {
            if (funLoopingNow->factors[i].value.type == vV)
                return funLoopingNow->factors[i].value.vValue;
            return &funLoopingNow->factors[i].value;
        }
    }
    return NULL;
}
variable* getVar(char* name)
{
    variable* v = getVariable(name);
    if (v != NULL) return v;
    if (funLoopingNow != 0) v = GetArgument(name);
    if (v != NULL) return v;
    return makeVariable(name);
}

int errorExcept = 0;
def getdefbyStr(char* str) // 문장에서 함수 이름을 찾아 반환함.
{
    errorExcept = 0;
    for (int i = 0; str[i] != 0; i++) { //문자열의 문자마다
        if (str[i] == '"') i += stringLength(&str[i], '"'); //따옴표 있으면 문자열 영역이니까 넘어감.
        for (int j = 0; j < defC; j++) { //함수들마다
            //printf("%s / %s\n", &str[i], defs[j].name);
            if (isMatch(&str[i], defs[j].name)) return defs[j]; //함수 이름이 맞으면 반환.
        }
    }
    errorExcept = 1;
    return defs[0];
}
function* initFunction(def* define, const char* str) // 함수로 변수를 만들어 result 포인터를 바꾼다.
{
    function* result = (function*)malloc(sizeof(function));
    if (result == NULL) return NULL;
    result->define = define;
    result->name = define->name;
    result->factors = (factor*)malloc(sizeof(factor)
        * define->argsCount); //sizeof(포인터)는 동적할당 관계없이 무조건 4라서 Count를 따로만듦
    result->options = (factor*)malloc(sizeof(factor)
        * define->optionsCount);

    if (result->factors == NULL || result->options == NULL)
    {
        if (result->factors != NULL)
            free(result->factors);
        if (result->options != NULL)
            free(result->options);
        free(result);
        return NULL;
    }
    for (int i = 0; i < define->argsCount; i++)
    {
        result->factors[i].name = define->args[i];
        result->factors[i].nameCount = define->argNameCount[i];
        result->factors[i].isMatched = false;
        result->factors[i].value.isMatched = false;
    }
    for (int i = 0; i < define->optionsCount; i++)
    {
        result->options[i].name = define->options;
        result->options[i].nameCount = 1;
        result->options[i].isMatched = false;
        result->options[i].value.isMatched = false;
    }
    return result;
}
void splitFactors(function fun, const char* str) // 문장 factor별로 잘라주기
{
    int starti = 0;
    for (int i = 0; str[i] != 0; i++) {
        for (int j = 0; j < fun.define->argsCount; j++) {
            if (fun.factors[j].isMatched) continue;
            int nameIndex;
            if (isFair(&str[i], fun.factors[j], &nameIndex, 0) && !next_is_opperator(&str[i]))
            {
                fun.factors[j].startF = str + starti;
                fun.factors[j].endF = str + i;
                fun.factors[j].isMatched = true;
                fun.factors[j].value.isMatched = true;
                starti = i + nameIndex; //첫 단어 잘리는 부분 + 조사 (stringLengthSpace로 잘라서 스페이스바는 알아서 걸러짐)
                break;
            }
            else if (isMatch(fun.define->name, &str[i]))
            {
                starti = i + stringLength(fun.define->name, ' ');
            }
        }
        for (int j = 0; j < fun.define->optionsCount; j++) {
            if (fun.options[j].isMatched) continue;
            int nameIndex;
            if (isFair(&str[i], fun.options[j], &nameIndex, 0) && !next_is_opperator(&str[i]))
            {
                fun.options[j].isMatched = true;
                fun.options[j].value.isMatched = true;
                starti = i + nameIndex; //첫 단어 잘리는 부분 + 조사 (stringLengthSpace로 잘라서 스페이스바는 알아서 걸러짐)
            }
        }
    }
    //if (ss < fun.define.argsCount) printf("오류 발생. 인수 개수와 형식이 맞지 않습니다.\n");
}