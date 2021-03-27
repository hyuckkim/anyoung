#define lineLength 240
#define moonLength 40
#define stackLength 20

typedef enum {false, true, rev = -1} bool;
typedef enum {none, iV, sV, vV, oV} type;

typedef struct struct_def //함수의 정의.
{
    char* name;
    char*** args; //여러개의 인수, 여러개의 얻는 방법, 여러개의 문자
    int argsCount; //args 개수
    int* argNameCount; //arg별 인수 개수
    char** line; //실행되면 실제로 작동하는 문자열들. 기본 함수에서는 무시됨.
    bool useindent; //평범한 함수가 아니라 문 (if, for, while ...)이면 1.
} def;
typedef struct struct_variable //최종적으로 할당되는 변수.
{
    union {
        int iValue;
        char* sValue;
        struct struct_variable* vValue;
    };
    type type; //none, iV, sV, vV, oV (예전엔 0이 int 1이 string 2가 Value였음)
    bool isMatched; //0이면 Null이라고 생각하면 될듯.
} variable;
typedef struct struct_stack //긴 전체 문자열을 계산해 변수 하나가 되는 과정에서 만들어지는 스택.
{
    union {
        int iValue;
        char* sValue;
        char* vValue;
        char oValue;
    };
    type type; //none, iV, sV, vV, oV
} stack;
typedef struct struct_factor //한 인수의 전체 문자열.
{
    char** name; // 조사 처리 여기서. 조사가 여러개가 같이 있을 수 있음.
    int nameCount;
    char* startF;
    char* endF;
    variable value;
    bool isMatched; // 기본 0, 매치되고 나면 1.
} factor;
typedef struct struct_function //코드 한 줄.
{
    char* name;
    factor* factors;
    def define;
    char** moon;
} function;