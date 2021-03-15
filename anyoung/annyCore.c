#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct struct_variable
{
    int iValue;
    char* sValue;
} variable;
typedef struct struct_factor
{
    char** name; // 조사 처리 여기서. 조사가 여러개가 같이 있을 수 있음.
    int nameCount;
    char* startF;
    char* endF; //문장에서의 함수 시작점과 끝점.
    variable value;
    char isMatched; // 기본 0, 매치되고 나면 1.
} factor;
typedef struct struct_function
{
    char* name;
    factor* factors;
} function;
typedef struct struct_def
{
    char* name;
    char*** args; //여러개의 인수, 여러개의 얻는 방법, 여러개의 문자
    int argsCount; //args 개수
    int* argNameCount; //arg별 인수 개수
    char** line; //실행되면 실제로 작동하는 문자열들. 기본 함수에서는 무시됨.
} def;
typedef struct struct_stack
{
    int iValue;
    char* sValue;
    char* vValue;
    char oValue;
    char type; // 0 : none 1 : num 2 : string 3 : variable 4 : operator
} stack;
int stringSize(char* item)
{
    int i;
    for (i = 0; item[i] != 0; i++) { }
    return i + 1;
}
int stringSizespace(char* item)
{
    int i;
    for (i = 0; item[i] != 0 && item[i] != ' '; i++) {}
    return i + 1;
}
char* setString(char* item)
{
    char* str = malloc(stringSize(item));
    for (int i = 0; item[i] != 0; i++)
    {
        str[i] = item[i];
    }
    str[stringSize(item) - 1] = '\0';
    return str;
}
int isMatch(char* word1, char* word2)
{
	int i = 0;
	while (1)
	{
		if (word1[i] != word2[i]) return 0;
		i++;
		if (word1[i] == '\0' || word1[i] == ' ') goto breakByFirst;
		if (word2[i] == '\0' || word2[i] == ' ') goto breakBySecond;
	}
breakByFirst:
	if (word2[i] == '\0' || word2[i] == ' ') return 1;
	else return 0;
breakBySecond:
	if (word1[i] == '\0' || word1[i] == ' ') return 1;
	else return 0;
}
int next_is_opperator(char* po)
{
    int i = 0;
    while (1)
    {
        i += 1;
        switch (po[i])
        {
        case ' ':
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            return 1;
        case '\0':
            return 0;
        default:
            return 0;
        }
    }
}
def defines[80];
char defineCount = 0;
def getdefbyStr(char* str) // 이름으로 함수 이름만 만들기
{
    // printf("str 실행중...");
    //문자열마다 있는지 보기.
    for (int i = 0; str[i] != 0; i++)
    {
        for (int j = 0; j < defineCount; j++)
        {
            // printf("%d : %s / %s\n", i, &str[i], defines[j].name);
            if (isMatch(&str[i], defines[j].name))
            {
                // printf("찾았다!");
                return defines[j];
            }
        }
    }
    printf("오류 발생. 문장에 맞는 함수를 찾지 못했습니다.");
    return defines[0];
}
function getfunbyDef(def define, char* str) // 함수로 객체만 만들기
{
    function *fp = malloc(sizeof(function));
    function f = *fp;
    f.name = define.name;
    f.factors = malloc(sizeof(factor)
        * define.argsCount); //일단 argument의 개수만큼 받으려고 한건데... Todo : 수 다시받기
    return f;
}
int isFair(char* word, factor it, int* ret) //int로 사용한 위치 반환함.
{
    for (int i = 0; i < it.nameCount; i++)
    {
        //printf("%s / %s\n", word, it.name[i]);
        if (isMatch(word, it.name[i]))
        {
            *ret = stringSizespace(word);
            return 1;
        }
    }
    return 0;
}
void sayAtoB(char* A, char* B)
{
    for (char* i = A; i < B; i++)
    {
        printf("%c", *i);
    }
    printf("\n");
}
factor* getFactors(def define, function fun, char* str) // 문장 factor별로 잘라주기
{
    factor* fac = malloc(define.argsCount);
    for(int i = 0; i < define.argsCount; i++)
    {
        fac[i].name = define.args[i];
        fac[i].nameCount = define.argNameCount[i];
        fac[i].isMatched = 0;
    }
    int starti = 0;
    int ss = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        for (int j = 0; j < define.argsCount; j++)
        {
            //printf("루프 사용...%d : %d\n", j, fac[j].isMatched);
            if (fac[j].isMatched) continue;
            int nameIndex;
            if (isFair(&str[i], fac[j], &nameIndex))
            {
                //printf("if 조건!\n");
                fac[j].startF = str + starti;
                fac[j].endF = str + i;
                fac[j].isMatched = 1;
                //sayAtoB(fac[j].startF, fac[j].endF);
                ss++;
                starti = i + nameIndex; //첫 단어 잘리는 부분 + 조사 (stringSizeSpace로 잘라서 스페이스바는 알아서 걸러짐)
                break;
            }
            else if (isMatch(define.name, &str[i]))
            {
                starti = i + stringSizespace(define.name);
            }
        }
    }
    if (ss == 0) printf("오류 발생. 인수 개수와 형식이 맞지 않습니다.\n");
    return fac;
}
int searchToQ(char* po)
{
    for (int i = 1; po[i] != '\0'; i++) // 시작하는 따옴표를 반환하는 것을 막기 위해 1부터.
    {
        if (po[i] == '"') return i;
    }
    return -1;
}
void getValueinFactor(factor* fac)
{
    stack newStack[20];
    int sts = -1, temp = 0;
    char inputMod = 0; //0 : 기본 1 : numbericValue 2 : stringValue 3 : variable
    for (int i = 0; i < fac->endF - fac->startF; i++)
    {
        char iv = fac->startF[i];
        printf("%d ", i);
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
                newStack[sts].sValue = malloc(searchToQ(&fac->startF[i]));
                temp = 0;
            }
            else if (iv == '+' || iv == '-' || iv == '*' || iv == '/')
            {
                sts++;
                newStack[sts].type = 4;
                newStack[sts].oValue = iv;
            }
            else if (iv == ' ') { } //아무 특정 입력도 없을 때 띄어쓰기는 딱히 상관 없음.
            else { } //아무 지정 문자열도 아님. 문제 있음.
            break;
        case 1:
            if (iv >= '0' && iv <= '9')
            {
                newStack[sts].iValue *= 10;
                newStack[sts].iValue += iv - '0';
            }
            else if (iv == '+' || iv == '-' || iv == '*' || iv == '/')
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
            else {} //아무 지정 문자열도 아님. 문제 있음.
            break;
        case 2:
            if (iv == '"')
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
    for (int i = 0; i < sts + 1; i++)
    {
        printf("%d\t", newStack[i].type);
    }
    printf("\n");
    //Todo : 스택 반복 돌리며 합쳐야됨. \
    핸드폰에 티스토리 블로그 찾아놓은거 보면서 최대한 합쳐보자. \
    변수 타입 구분 잘 하고. 
}
void Function_Say(char* text)
{
    printf("%s\n", text);
}
void annyCore_init()
{
    printf("어순에 상관없는 한글 프로그래밍 언어 안녕\nv0.1 실행중\n'도움'으로 명령어 확인(아직 안됨)\n");
    defines[defineCount].name = setString("말하기");
    defines[defineCount].argsCount = 1;
    defines[defineCount].argNameCount = malloc(sizeof(int) * 1);
    defines[defineCount].args = malloc(sizeof(char**) * 1);
    defines[defineCount].args[0] = malloc(sizeof(char*) * 2);
    defines[defineCount].argNameCount[0] = 2;
    defines[defineCount].args[0][0] = setString("을");
    defines[defineCount].args[0][1] = setString("를");
    defineCount++;
    defines[defineCount].name = setString("표시하기");
    defines[defineCount].argsCount = 2;
    defines[defineCount].argNameCount = malloc(sizeof(int) * 1);
    defines[defineCount].args = malloc(sizeof(char**) * 2);
    defines[defineCount].args[0] = malloc(sizeof(char*) * 2);
    defines[defineCount].argNameCount[0] = 2;
    defines[defineCount].args[0][0] = setString("과");
    defines[defineCount].args[0][1] = setString("와");
    defines[defineCount].args[1] = malloc(sizeof(char*) * 2);
    defines[defineCount].argNameCount[1] = 2;
    defines[defineCount].args[1][0] = setString("을");
    defines[defineCount].args[1][1] = setString("를");
    defineCount++;
}
void anyFunction(char* line)
{
    def defNow = getdefbyStr(line);
    function funNow = getfunbyDef(defNow, line);
    funNow.factors = getFactors(defNow, funNow, line);
    for (int i = 0; i < defNow.argsCount; i++)
    {
        sayAtoB(funNow.factors[i].startF, funNow.factors[i].endF);
        getValueinFactor(&funNow.factors[i]);
    }
    //printf("%s", funNow.factors[0].startF);
    //if (isMatch(funNow.name, "말하기")) Function_Say(funNow.factors->value.sValue);
}
