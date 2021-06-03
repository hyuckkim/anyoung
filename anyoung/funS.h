/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>

#define DEFNOW defs[defC]
#define IS_CLEARED DEFNOW.args != NULL && DEFNOW.argNameCount != NULL
void SetData(const char* name, int args, int options, bool useIndents)
{
    DEFNOW.name = setString(name);
    DEFNOW.argsCount = args; 
    DEFNOW.args = malloc(sizeof(char**) * args); 
    DEFNOW.argNameCount = malloc(sizeof(int) * args);

    DEFNOW.optionsCount = options;
    DEFNOW.options = malloc(sizeof(char*) * options);
    DEFNOW.useindent = useIndents;
}
void DefineInserted()
{
    defC++;
    if (defC >= defM) {
        defM *= 2;
        void* dTemp = realloc(defs, defM * sizeof(def));
        if (dTemp != NULL) defs = dTemp;
    }
}
void SetArgs(int o, int c, ...)
{
    va_list v;
    va_start(v, c);
    DEFNOW.argNameCount[o] = c;
    DEFNOW.args[o] = malloc(sizeof(char*) * c);
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
void annyCore_init()
{
    defs = malloc(sizeof(def));
    vars = malloc(sizeof(variable));
    varNames = malloc(sizeof(char*));
    
    SetData("말하기" ,1 ,1, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetOptions(1, "조용히");
    }
    DEFNOW.fun = Function_Say;
    DefineInserted();

    SetData("듣기", 1, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 1, "에");
    }
    DEFNOW.fun = Function_Listen;
    DefineInserted();

    SetData("표시하기", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "번");
    }
    DEFNOW.fun = Function_Print;
    DefineInserted();

    SetData("도움", 0, 0, false);
    DEFNOW.fun = Function_Help;
    DefineInserted();

    SetData("정하기", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
    }
    DEFNOW.useindent = false;
    DEFNOW.fun = Function_Set;
    DefineInserted();

    SetData("더하기", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Add;
    DefineInserted();

    SetData("빼기", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Minus;
    DefineInserted();

    SetData("곱하기", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Multi;
    DefineInserted();

    SetData("나누기", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    DEFNOW.fun = Function_Devide;
    DefineInserted();

    SetData("되풀이", 2, 0, true);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "로", "으로");
        SetArgs(1, 1, "번");
    }
    DEFNOW.fun = Function_Loop;
    DefineInserted();

    SetData("조건", 1, 0, true);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "면", "이면");
    }
    DEFNOW.fun = Function_If;
    DefineInserted();

    SetData("여기까지", 0, 0, rev);
    DefineInserted();

    SetData("아니면", 0, 0, false);
    DefineInserted();

    SetData("잘라내기", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 1, "에서");
        SetArgs(1, 2, "로", "으로");
    }
    DEFNOW.fun = Function_Cutstr;
    DefineInserted();

    SetData("동작", 1, 0, true);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "이라는", "라는");
    }
    DEFNOW.fun = Function_fun;
    DefineInserted();

    SetData("인수", 5, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
        SetArgs(2, 2, "와", "나");
        SetArgs(3, 2, "와", "나");
        SetArgs(4, 2, "와", "나");
    }
    DefineInserted();

    SetData("있는지", 2, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 1, "에");
        SetArgs(1, 2, "이", "가");
    }
    DEFNOW.fun = Function_valid;
    DefineInserted();

    SetData("읽어오기", 1, 0, false);
    if (IS_CLEARED)
    {
        SetArgs(0, 2, "을", "를");
    }
    DEFNOW.fun = Function_include;
    DefineInserted();
}