/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>
void annyCore_init()
{
    defs[defC].name = setString("말하기");
    defs[defC].argsCount = 1;
    defs[defC].args = malloc(sizeof(char**) * 1);
    defs[defC].argNameCount = malloc(sizeof(int) * 1);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("을");
            defs[defC].args[0][1] = setString("를");
        }
    }
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("표시하기");
    defs[defC].argsCount = 2;
    defs[defC].args = malloc(sizeof(char**) * 2);
    defs[defC].argNameCount = malloc(sizeof(int) * 2);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("을");
            defs[defC].args[0][1] = setString("를");
        }
        defs[defC].argNameCount[1] = 1;
        defs[defC].args[1] = malloc(sizeof(char*) * 1);
        if (defs[defC].args[1] != NULL)
        {
            defs[defC].args[1][0] = setString("번");
        }
    }
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("도움");
    defs[defC].argsCount = 0;
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("정하기");
    defs[defC].argsCount = 2;
    defs[defC].args = malloc(sizeof(char**) * 2);
    defs[defC].argNameCount = malloc(sizeof(int) * 2);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("을");
            defs[defC].args[0][1] = setString("를");
        }
        defs[defC].argNameCount[1] = 2;
        defs[defC].args[1] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[1] != NULL)
        {
            defs[defC].args[1][0] = setString("로");
            defs[defC].args[1][1] = setString("으로");
        }
    }
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("더하기");
    defs[defC].argsCount = 2;
    defs[defC].args = malloc(sizeof(char**) * 2);
    defs[defC].argNameCount = malloc(sizeof(int) * 2);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("을");
            defs[defC].args[0][1] = setString("를");
        }
        defs[defC].argNameCount[1] = 1;
        defs[defC].args[1] = malloc(sizeof(char*) * 1);
        if (defs[defC].args[1] != NULL)
        {
            defs[defC].args[1][0] = setString("만큼");
        }
    }
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("빼기");
    defs[defC].argsCount = 2;
    defs[defC].args = malloc(sizeof(char**) * 2);
    defs[defC].argNameCount = malloc(sizeof(int) * 2);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("을");
            defs[defC].args[0][1] = setString("를");
        }
        defs[defC].argNameCount[1] = 1;
        defs[defC].args[1] = malloc(sizeof(char*) * 1);
        if (defs[defC].args[1] != NULL)
        {
            defs[defC].args[1][0] = setString("만큼");
        }
    }
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("곱하기");
    defs[defC].argsCount = 2;
    defs[defC].args = malloc(sizeof(char**) * 2);
    defs[defC].argNameCount = malloc(sizeof(int) * 2);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("을");
            defs[defC].args[0][1] = setString("를");
        }
        defs[defC].argNameCount[1] = 1;
        defs[defC].args[1] = malloc(sizeof(char*) * 1);
        if (defs[defC].args[1] != NULL)
        {
            defs[defC].args[1][0] = setString("만큼");
        }
    }
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("나누기");
    defs[defC].argsCount = 2;
    defs[defC].args = malloc(sizeof(char**) * 2);
    defs[defC].argNameCount = malloc(sizeof(int) * 2);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("을");
            defs[defC].args[0][1] = setString("를");
        }
        defs[defC].argNameCount[1] = 1;
        defs[defC].args[1] = malloc(sizeof(char*) * 1);
        if (defs[defC].args[1] != NULL)
        {
            defs[defC].args[1][0] = setString("만큼");
        }
    }
    defs[defC].useindent = 0;
    defC++;

    defs[defC].name = setString("되풀이");
    defs[defC].argsCount = 2;
    defs[defC].args = malloc(sizeof(char**) * 2);
    defs[defC].argNameCount = malloc(sizeof(int) * 2);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 2;
        defs[defC].args[0] = malloc(sizeof(char*) * 2);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("로");
            defs[defC].args[0][1] = setString("으로");
        }
        defs[defC].argNameCount[1] = 1;
        defs[defC].args[1] = malloc(sizeof(char*) * 1);
        if (defs[defC].args[1] != NULL)
        {
            defs[defC].args[1][0] = setString("번");
        }
    }
    defs[defC].useindent = 1;
    defC++;

    defs[defC].name = setString("조건");
    defs[defC].argsCount = 1;
    defs[defC].args = malloc(sizeof(char**) * 1);
    defs[defC].argNameCount = malloc(sizeof(int) * 1);
    if (defs[defC].args != NULL && defs[defC].argNameCount != NULL)
    {
        defs[defC].argNameCount[0] = 1;
        defs[defC].args[0] = malloc(sizeof(char*) * 1);
        if (defs[defC].args[0] != NULL)
        {
            defs[defC].args[0][0] = setString("면");
        }
    }
    defs[defC].useindent = 1;
    defC++;

    defs[defC].name = setString("여기까지");
    defs[defC].argsCount = 0;
    defs[defC].useindent = -1;
    defC++;

    defs[defC].name = setString("아니면");
    defs[defC].argsCount = 0;
    defs[defC].useindent = 0;
    defC++;
}