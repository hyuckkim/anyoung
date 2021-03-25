/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>

#define dd defs[defC]
#define ddl(x) defs[defC].argsCount = x; defs[defC].args = malloc(sizeof(char**) * x); defs[defC].argNameCount = malloc(sizeof(int) * x);
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
void annyCore_init()
{
    dd.name = setString("말하기");
    ddl(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("듣기");
    ddl(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 1, "에");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("표시하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "번");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("도움");
    dd.argsCount = 0;
    dd.useindent = 0;
    defC++;

    dd.name = setString("정하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 2, "로", "으로");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("더하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("빼기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("곱하기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("나누기");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "을", "를");
        SetArgs(1, 1, "만큼");
    }
    dd.useindent = 0;
    defC++;

    dd.name = setString("되풀이");
    ddl(2);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        SetArgs(0, 2, "로", "으로");
        SetArgs(1, 1, "번");
    }
    dd.useindent = 1;
    defC++;

    dd.name = setString("조건");
    ddl(1);
    if (dd.args != NULL && dd.argNameCount != NULL)
    {
        dd.argNameCount[0] = 1;
        dd.args[0] = malloc(sizeof(char*) * 1);
        if (dd.args[0] != NULL)
        {
            SetArgs(0, 1, "면");
        }
    }
    dd.useindent = 1;
    defC++;

    dd.name = setString("여기까지");
    dd.argsCount = 0;
    dd.useindent = -1;
    defC++;

    dd.name = setString("아니면");
    dd.argsCount = 0;
    dd.useindent = 0;
    defC++;
}