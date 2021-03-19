typedef struct struct_def //함수의 정의.
{
    char* name;
    char*** args; //여러개의 인수, 여러개의 얻는 방법, 여러개의 문자
    int argsCount; //args 개수
    int* argNameCount; //arg별 인수 개수
    char** line; //실행되면 실제로 작동하는 문자열들. 기본 함수에서는 무시됨.
} def;
typedef struct struct_variable //최종적으로 할당되는 변수.
{
    int iValue;
    char* sValue;
    struct struct_variable* vValue;
    char type; //0 : int 1 : string 2 : variable.
} variable;
typedef struct struct_stack //긴 전체 문자열을 계산해 변수 하나가 되는 과정에서 만들어지는 스택.
{
    int iValue;
    char* sValue;
    char oValue;
    char type; // 0 : none 1 : num 2 : string 3 : variable 4 : operator
} stack;
typedef struct struct_factor //한 인수의 전체 문자열.
{
    char** name; // 조사 처리 여기서. 조사가 여러개가 같이 있을 수 있음.
    int nameCount;
    char* startF;
    char* endF;
    variable value;
    char isMatched; // 기본 0, 매치되고 나면 1.
} factor;
typedef struct struct_function //코드 한 줄.
{
    char* name;
    factor* factors;
    def define;
} function;