#pragma once
#include <stdbool.h>

#define lineLength 240
#define moonLength 40

typedef struct struct_def def;
typedef struct struct_variable variable;
typedef struct struct_factor factor;
typedef struct struct_function function;
typedef enum { //int, string, variable, operator, enum
    none, //아무것도 없는 상태
    iV, //int Value. 숫자.
    sV, //string Value. 문자열.
    vV, //Variable Value. 다른 변수를 참조하는 중.
    oV, //Operator Value. 연산자.
} type; 

//함수의 정의.
struct struct_def
{
    char* name;

    char*** args; //여러개의 인수, 여러개의 얻는 방법, 여러개의 문자
    int argsCount; //args 개수
    char** argsName; //args 이름들.
    int* argNameCount; //arg별 인수 개수

    char** options; //'매우' 같은 단어들.
    int optionsCount;

    char** line; //실행되면 실제로 작동하는 문자열들. 기본 함수에서는 무시됨.
    int lineCount; //

    int useindent; //평범한 함수가 아니라 문 (if, for, while ...)이면 1. 문 끝내기에 -1이 있음.
    bool usecondit; //조건문인지. '인수', '아니면', '여기까지' 등등.
    int (*fun) (function*);
};

//최종적으로 할당되는 변수.
struct struct_variable
{
    union {
        int iValue;
        char* sValue;
        variable* vValue;
    };
    type type; //none, iV, sV, vV, oV
    bool isMatched; //0이면 Null이라고 생각하면 될듯.
};

//한 인수의 전체 문자열.
struct struct_factor
{
    char** name; // 조사 처리 여기서. 조사가 여러개가 같이 있을 수 있음.
    int nameCount;
    const char* startF;
    const char* endF;
    variable value;
    bool isMatched; // 기본 0, 매치되고 나면 1.
};
//코드 한 줄.
struct struct_function
{
    char* name;
    factor* factors;
    factor* options;
    def* define;
    char** line;
    int linecount;
    function* returnTo;
};