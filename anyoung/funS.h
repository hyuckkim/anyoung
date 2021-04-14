/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>

#define dd defs[defC]
#define ddl(x) defs[defC].argsCount = x; defs[defC].args = malloc(sizeof(char**) * x); defs[defC].argNameCount = malloc(sizeof(int) * x);
#define ddr(x) defs[defC].optionsCount = x; defs[defC].options = malloc(sizeof(char*) * x);
void SetData(const char* name, int args, int options, bool useIndents)
{
    dd.name = setString(name);
    ddl(args);
    ddr(options);
    dd.useindent = useIndents;
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
    dd.argNameCount[o] = c;
    dd.args[o] = malloc(sizeof(char*) * c);
    if (dd.args[o] != NULL)
        for (int i = 0; i < c; i++)
        {
            dd.args[o][i] = setString(va_arg(v, char*));
        }
}
void SetOptions(int c, ...)
{
    va_list v;
    va_start(v, c);
    if (dd.options != NULL)
    {
        for (int i = 0; i < c; i++)
        {
            dd.options[i] = setString(va_arg(v, char*));
        }
    }
}
void annyCore_init()
{
    defs = malloc(sizeof(def));
    vars = malloc(sizeof(variable));
    varNames = malloc(sizeof(char*));
    
    SetData("말하기" ,1 ,1, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetOptions(1, "조용히");
    }
    dd.fun = Function_Say;
    DefineInserted();

    SetData("듣기", 1, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 1, "에");
    }
    dd.fun = Function_Listen;
    DefineInserted();

    SetData("표시하기", 2, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "번");
    }
    dd.fun = Function_Print;
    DefineInserted();

    SetData("도움", 0, 0, false);
    dd.fun = Function_Help;
    DefineInserted();

    SetData("정하기", 2, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
    }
    dd.useindent = false;
    dd.fun = Function_Set;
    DefineInserted();

    SetData("더하기", 2, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.fun = Function_Add;
    DefineInserted();

    SetData("빼기", 2, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.fun = Function_Minus;
    DefineInserted();

    SetData("곱하기", 2, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.fun = Function_Multi;
    DefineInserted();

    SetData("나누기", 2, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.fun = Function_Devide;
    DefineInserted();

    SetData("되풀이", 2, 0, true);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "로", "으로");
        SetArgs(1, 1, "번");
    }
    dd.fun = Function_Loop;
    DefineInserted();

    SetData("조건", 1, 0, true);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "면", "이면");
    }
    dd.fun = Function_If;
    DefineInserted();

    SetData("여기까지", 0, 0, rev);
    DefineInserted();

    SetData("아니면", 0, 0, false);
    DefineInserted();

    SetData("동작", 1, 0, true);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "이라는", "라는");
    }
    dd.fun = Function_fun;
    DefineInserted();

    SetData("인수", 5, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
        SetArgs(2, 2, "와", "나");
        SetArgs(3, 2, "와", "나");
        SetArgs(4, 2, "와", "나");
    }
    DefineInserted();

    SetData("있는지", 2, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 1, "에");
        SetArgs(1, 2, "이", "가");
    }
    dd.fun = Function_valid;
    DefineInserted();

    SetData("읽어오기", 1, 0, false);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
    }
    dd.fun = Function_include;
    DefineInserted();
}