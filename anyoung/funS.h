/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>

#define dd defs[defC]
#define ddl(x) defs[defC].argsCount = x; defs[defC].args = malloc(sizeof(char**) * x); defs[defC].argNameCount = malloc(sizeof(int) * x);
#define ddr(x) defs[defC].optionsCount = x; defs[defC].options = malloc(sizeof(char*) * x);
#define AddFun \
    defC++; \
    if (defC >= defM) { \
        oldBuffer = defs; \
        defM *= 2; \
        realloc(defs, defM * sizeof(def)); \
        free(oldBuffer); \
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
    dd.name = setString("말하기");
    ddl(1);
    ddr(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetOptions(1, "조용히");
    }
    dd.useindent = false;
    dd.fun = Function_Say;
    defC++;

    dd.name = setString("듣기");
    ddl(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 1, "에");
    }
    dd.useindent = false;
    dd.fun = Function_Listen;
    defC++;

    dd.name = setString("표시하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "번");
    }
    dd.useindent = false;
    dd.fun = Function_Print;
    defC++;

    dd.name = setString("도움");
    dd.argsCount = 0;
    dd.useindent = 0;
    dd.fun = Function_Help;
    defC++;

    dd.name = setString("정하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
    }
    dd.useindent = false;
    dd.fun = Function_Set;
    defC++;

    dd.name = setString("더하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = false;
    dd.fun = Function_Add;
    defC++;

    dd.name = setString("빼기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = false;
    dd.fun = Function_Minus;
    defC++;

    dd.name = setString("곱하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = false;
    dd.fun = Function_Multi;
    defC++;

    dd.name = setString("나누기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = false;
    dd.fun = Function_Devide;
    defC++;

    dd.name = setString("되풀이");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "로", "으로");
        SetArgs(1, 1, "번");
    }
    dd.useindent = true;
    dd.fun = Function_Loop;
    defC++;

    dd.name = setString("조건");
    ddl(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "면", "이면");
    }
    dd.useindent = true;
    dd.fun = Function_If;
    defC++;

    dd.name = setString("여기까지");
    ddl(0);
    dd.useindent = rev;
    defC++;

    dd.name = setString("아니면");
    ddl(0);
    dd.useindent = false;
    defC++;

    dd.name = setString("동작");
    ddl(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "이라는", "라는");
    }
    dd.useindent = true;
    dd.fun = Function_fun;
    defC++;

    dd.name = setString("인수"); 
    ddl(5);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
        SetArgs(2, 2, "와", "나");
        SetArgs(3, 2, "와", "나");
        SetArgs(4, 2, "와", "나");
    }
    dd.useindent = false;
    defC++;

    dd.name = setString("있는지");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 1, "에");
        SetArgs(1, 2, "이", "가");
    }
    dd.useindent = false;
    dd.fun = Function_valid;
    defC++;

    dd.name = setString("읽어오기");
    ddl(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
    }
    dd.useindent = false;
    dd.fun = Function_include;
    defC++;
}