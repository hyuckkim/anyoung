/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>

void itisRValue(variable* v)
{
    if (v->isMatched && v->type == vV)
    {
        if (v->vValue->type == iV)
        {
            v->type = iV;
            v->iValue = v->vValue->iValue;
        }
        else if (v->vValue->type == sV)
        {
            v->type = sV;
            v->sValue = v->vValue->sValue;
        }
    }
}
void Function_Help()
{
    printf("\n흐름\n");
    printf("여기까지 \t\t\t흐름 함수를 어디까지 실행할지의 조건이 됩니다.\n\n");
    printf("[ㅁ 로/으로] ㅇ 번 되풀이 \t'여기까지' 까지의 함수를 ㅇ번 실행합니다. ㅁ에 동작 횟수를 0부터 기록합니다.\n");
    printf("ㅁ 면 조건\t\t\tㅁ가 숫자고 1이라면 '여기까지' 까지의 함수를 실행합니다.\n");
    printf("아니면\t\t\t\t조건과 여기까지 사이에 넣어 함수를 실행할지를 반전합니다.\n\n");
    printf("ㅁ 이라는/라는 동작\t\tㅁ 라는 문자열로 함수를 정의합니다.\n");
    printf("ㅁ 을/를 [ㅇ 로/으로] 인수\t함수의 인수를 설정합니다. 'ㅂ 와/나' 로 여러 조사를 받게 할 수 있습니다.\n");
    printf("\n데이터\n");
    printf("ㅁ 을/를 ㅇ으로/로 정하기\t변수 ㅁ의 값을 ㅇ로 지정합니다. ㅁ이 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 더하기\t\t변수 ㅁ의 값에 ㅇ를 더합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 빼기\t\t변수 ㅁ의 값에 ㅇ를 뺍니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 곱하기\t\t변수 ㅁ의 값에 ㅇ를 곱합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ 을/를 ㅇ 만큼 나누기\t\t변수 ㅁ의  값에 ㅇ를 나눕니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("\n화면 입출력\n");
    printf("ㅁ 에 듣기\t\t\t화면에서 입력을 받아 변수 ㅁ에 전달합니다.\n");
    printf("ㅁ 을/를 [조용히] 말하기 \tㅁ을 개행문자와 함께 출력합니다. '조용히' 와 사용되면 개행문자 없이 출력합니다.\n");
    printf("ㅁ 을/를 [ㅇ 번] 표시하기 \tㅁ을 ㅇ번 출력합니다. ㅇ는 숫자여야 합니다.\n");
    printf("도움\t\t\t\t함수에 대한 도움말을 봅니다.");
    printf("\n");
}
extern int anyFunction(char* line);
void Function_Loop(function* looping)
{
    looping->moon = malloc(sizeof(char* ) * moonLength);
    canInsert = 1;
}
void Function_If(function* looping)
{
    looping->moon = malloc(sizeof(char*) * moonLength);
    if (looping->factors[0].value.type == iV && looping->factors[0].value.iValue != 0) // 0이 아닌 int value : true.
        canInsert = 1;
    else
        canInsert = 0; //조건문 시작할 때 조건 비교해서 틀리면 아예 메모리에 저장 안함.
}
void Function_fun(function* looping)
{
    looping->moon = malloc(sizeof(char*) * moonLength);
    canInsert = 1;
}
void Function_Loop_end(function* fn)
{
    itisRValue(&fn->factors[1].value);
    funC++; //안에서 쓰이지 않아도 anyFunction에서 쓰므로 변경.
    if (fn->factors[0].value.isMatched)
    {
        variable* v = fn->factors[0].value.vValue;
        v->iValue = 0;
        ind = 0;
        for (int i = 0; i < fn->factors[1].value.iValue; i++) //v번
        {
            for (int j = 0; j < temp[funC - 1]; j++) //각 함수 실행
                anyFunction(fn->moon[j]);
            v->iValue++;
        }
    }
    else
    {
        for (int i = 0; i < fn->factors[1].value.iValue; i++) //v번
        {
            for (int j = 0; j < temp[funC - 1]; j++) //각 함수 실행
                anyFunction(fn->moon[j]);
        }
    }
    funC--;
    for (int i = 0; i < temp[funC]; i++)
        free(fn->moon[i]);
    free(fn);
    temp[funC] = 0;
}
void Function_If_end(function* fn)
{
    funC++;
    variable* v = &fn->factors[0].value;
    ind = 0;
    for (int j = 0; j < temp[funC - 1]; j++) //각 함수 실행
        anyFunction(fn->moon[j]);
    funC--;
    for (int i = 0; i < temp[funC]; i++)
        free(fn->moon[i]);
    free(fn);
    temp[funC] = 0;
}
void Function_fun_end(function* fn)
{
    funC++;
    defs[defC].name = fn->factors[0].value.sValue;
    defs[defC].args = malloc(sizeof(char**) * 8);
    defs[defC].argsName = malloc(sizeof(char*) * 8);
    defs[defC].argNameCount = malloc(sizeof(int*) * 8);
    defs[defC].options = malloc(sizeof(char*) * 8);
    defs[defC].line = malloc(sizeof(char*) * 80);
    defs[defC].useindent = false;
    defs[defC].argsCount = 0;
    defs[defC].optionsCount = 0;
    defs[defC].lineCount = 0;
    for (int i = 0; i < temp[funC - 1]; i++)
    {
        def defNow = getdefbyStr(fn->moon[i]);
        if (isMatch(defNow.name, "인수"))
        {
            functions[funC] = malloc(sizeof(function));
            if (functions[funC] == NULL) return;

            getfunbyDef(&defNow, fn->moon[i], functions[funC]);
            splitFactors(*functions[funC], fn->moon[i]);
            for (int i = 0; i < defNow.argsCount; i++)
            {
                if (!functions[funC]->factors[i].isMatched) continue; // 없는 인수는 그냥 넘어간다.
                //sayAtoB(funNow.factors[i].startF, funNow.factors[i].endF);
                getValueinFactor(&functions[funC]->factors[i]);
                functions[funC]->factors[i].value.isMatched = true;
            }
            if (!functions[funC]->factors[1].isMatched) // 조사가 없음 -> option으로 가야됨.
            {
                defs[defC].options[defs[defC].optionsCount] = setString(functions[funC]->factors[0].value.sValue);
            }
            else if (!functions[funC]->factors[2].isMatched) // 조사 하나
            {
                int c = defs[defC].argsCount;
                defs[defC].args[c] = malloc(sizeof(char**) * 1);
                defs[defC].argNameCount[c] = 1;
                defs[defC].argsName[c] = setString(functions[funC]->factors[0].value.sValue);
                defs[defC].args[c][0] = setString(functions[funC]->factors[1].value.sValue);
                defs[defC].argsCount++;
            }
            else if (!functions[funC]->factors[3].isMatched) // 조사 둘
            {
                int c = defs[defC].argsCount;
                defs[defC].args[c] = malloc(sizeof(char**) * 2);
                defs[defC].argNameCount[c] = 2;
                defs[defC].argsName[c] = setString(functions[funC]->factors[0].value.sValue);
                defs[defC].args[c][0] = setString(functions[funC]->factors[1].value.sValue);
                defs[defC].args[c][1] = setString(functions[funC]->factors[2].value.sValue);
                defs[defC].argsCount++;
            }
            else if (!functions[funC]->factors[4].isMatched) // 조사 셋
            {
                int c = defs[defC].argsCount;
                defs[defC].args[c] = malloc(sizeof(char**) * 3);
                defs[defC].argNameCount[c] = 3;
                defs[defC].argsName[c] = setString(functions[funC]->factors[0].value.sValue);
                defs[defC].args[c][0] = setString(functions[funC]->factors[1].value.sValue);
                defs[defC].args[c][1] = setString(functions[funC]->factors[2].value.sValue);
                defs[defC].args[c][2] = setString(functions[funC]->factors[3].value.sValue);
                defs[defC].argsCount++;
            }
            else // 조사 넷
            {
                int c = defs[defC].argsCount;
                defs[defC].args[c] = malloc(sizeof(char**) * 4);
                defs[defC].argNameCount[c] = 4;
                defs[defC].argsName[c] = setString(functions[funC]->factors[0].value.sValue);
                defs[defC].args[c][0] = setString(functions[funC]->factors[1].value.sValue);
                defs[defC].args[c][1] = setString(functions[funC]->factors[2].value.sValue);
                defs[defC].args[c][2] = setString(functions[funC]->factors[3].value.sValue);
                defs[defC].args[c][3] = setString(functions[funC]->factors[4].value.sValue);
                defs[defC].argsCount++;
            }
        }
        else
        {
            defs[defC].line[defs[defC].lineCount] = setString(fn->moon[i]);
            defs[defC].lineCount++;
        }
    }
    defC++;
}
void Function_User(function* fn)
{
    funLoopingNow = fn;
    funC++;
    for (int i = 0; i < fn->define->lineCount; i++)
    {
        anyFunction(fn->define->line[i]);
    }
    funC--;
    funLoopingNow = 0;
}
variable* GetArgument(char* name)
{

    //functions[funC]->factors[0].value.sValue
    for (int i = 0; i < funLoopingNow->define->argsCount; i++)
    {
        if (isMatch(funLoopingNow->define->argsName[i], name)) return &funLoopingNow->factors[i].value;
    }
    return NULL;
}
void Function_Set(variable value1, variable value2)
{
    itisRValue(&value2);
    if (value1.type != vV) return;
    switch (value2.type)
    {
    case iV:
        value1.vValue->type = iV;
        value1.vValue->iValue = value2.iValue;
        break;
    case sV:
        value1.vValue->type = sV;
        value1.vValue->sValue = setString(value2.sValue);
        break;
    }
}
void Function_Add(variable value1, variable value2)
{
    itisRValue(&value2);
    if (value1.type != vV) return;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue += value2.iValue;
    }
}
void Function_Minus(variable value1, variable value2)
{
    itisRValue(&value2);
    if (value1.type != vV) return;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue -= value2.iValue;
    }
}
void Function_Multi(variable value1, variable value2)
{
    itisRValue(&value2);
    if (value1.type != vV) return;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue *= value2.iValue;
    }
}
void Function_Devide(variable value1, variable value2)
{
    itisRValue(&value2);
    if (value1.type != vV) return;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue /= value2.iValue;
    }
}
void Function_Listen(variable value)
{
    if (value.type != vV) return;
        char* cc = malloc(lineLength);
        getSO(cc, "");
        value.vValue->sValue = setString(cc);
        value.vValue->type = sV;
        free(cc);
}
void Function_Say(variable value)
{
    itisRValue(&value);
    if (value.type == iV)
        printf("%d\n", value.iValue);
    else if (value.type == sV)
        printf("%s\n", value.sValue);
}
void Function_Say_Si(variable value)
{
    itisRValue(&value);
    if (value.type == iV)
        printf("%d", value.iValue);
    else if (value.type == sV)
        printf("%s", value.sValue);
}
void Function_Print(variable value1, variable value2)
{
    itisRValue(&value1);
    itisRValue(&value2);
    if (value2.isMatched)
    {
        for (int i = 0; i < value2.iValue; i++)
        {
            if (value1.type == iV)
                printf("%d", value1.iValue);
            else if (value1.type == sV)
                printf("%s", value1.sValue);
        }
    }
    else
    {
        if (value1.type == iV)
            printf("%d", value1.iValue);
        else if (value1.type == sV)
            printf("%s", value1.sValue);
    }
    printf("\n");
}