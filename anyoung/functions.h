/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>

extern int anyFunction(char* line);
variable itisRValue(variable* v)
{
    variable result;
    if (v->isMatched)
    {
        result.isMatched = true;
        if (v->type == vV)
        {
            if (v->vValue->type == iV)
            {
                result.type = iV;
                result.iValue = v->vValue->iValue;
            }
            else if (v->vValue->type == sV)
            {
                result.type = sV;
                result.sValue = v->vValue->sValue;
            }
        }
        else
        {
            if (v->type == iV)
            {
                result.type = iV;
                result.iValue = v->iValue;
            }
            else if (v->type == sV)
            {
                result.type = sV;
                result.sValue = v->sValue;
            }
        }
    }
    else
    {
        result.isMatched = false;
    }
    return result;
}
variable itisLValue(variable* v)
{
    variable result;
    if (v->isMatched)
    {
        result.isMatched = true;
        if (v->type == sV)
        {
            result.type = vV;
            result.vValue = getVar(v->sValue);
        }
        else if (v->type == vV)
        {
            result.type = vV;
            result.vValue = v->vValue;
        }
        return result;
    }
    else
    {
        result.isMatched = false;
    }
    return result;
}

int itCanInt(char* chars)
{
    for (int i = 0; chars[i] != 0; i++)
        if (chars[i] > '9' || chars[i] < '0') return 0;
    return 1;
}
int getIntinStr(char* chars)
{
    int result = 0;
    for (int i = 0; chars[i] != 0; i++)
    {
        result *= 10;
        result += chars[i] - '0';
    }
    return result;
}

int Function_User(function* fn)
{
    funLoopingNow = fn;
    for (int i = 0; i < fn->define->lineCount; i++)
    {
        anyFunction(fn->define->line[i]);
    }
    funLoopingNow = 0;
    return 0;
}
int Function_Help(function* fn)
{
    printf("\n흐름\n");
    printf("여기까지 \t\t\t흐름 함수를 어디까지 실행할지의 조건이 됩니다.\n\n");
    printf("[ㅁ 로/으로] ㅇ 번 되풀이 \t'여기까지' 까지의 함수를 ㅇ번 실행합니다. ㅁ에 동작 횟수를 0부터 기록합니다.\n");
    printf("ㅁ 면/이면 조건\t\t\tㅁ가 숫자고 1이라면 '여기까지' 까지의 함수를 실행합니다.\n");
    printf("아니면\t\t\t\t조건과 여기까지 사이에 넣어 함수를 실행할지를 반전합니다.\n\n");
    printf("ㅁ 이라는/라는 동작\t\tㅁ 라는 문자열로 함수를 정의합니다.\n");
    printf("ㅁ 을/를 [ㅇ 로/으로] 인수\t함수의 인수를 설정합니다. 'ㅂ 와/나' 로 여러 조사를 받게 할 수 있습니다.\n");
    printf("ㅁ 이 있는지\t\t\t인수로 ㅁ이 있으면 1, 없으면 0을 출력합니다.\n");
    printf("ㅁ 을/를 읽어오기 \t\t\tㅁ이라는 이름의 안녕 파일을 읽어 실행합니다.\n");
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
    return 0;
}
int Function_Loop(function* fn)
{
    fn->moon = malloc(sizeof(char* ) * moonLength);
    canInsert = 1;
    fn->temp = 0;
    return 1;
}
int Function_If(function* fn)
{
    fn->moon = malloc(sizeof(char*) * moonLength);
    itisRValue(&fn->factors[0].value);
    if (fn->factors[0].value.type == iV && fn->factors[0].value.iValue != 0) // 0이 아닌 int value : true.
        canInsert = 1;
    else
        canInsert = 0; //조건문 시작할 때 조건 비교해서 틀리면 아예 메모리에 저장 안함.
    fn->temp = 0;
    return 1;
}
int Function_fun(function* fn)
{
    fn->moon = malloc(sizeof(char*) * moonLength);
    canInsert = 1;
    fn->temp = 0;
    return 1;
}
int Function_Loop_end(function* fn)
{
    itisLValue(&fn->factors[0].value);
    itisRValue(&fn->factors[1].value);
    if (fn->factors[0].value.isMatched)
    {
        variable* v = fn->factors[0].value.vValue;
        v->iValue = 0;
        ind = 0;
        for (int i = 0; i < fn->factors[1].value.iValue; i++) //v번
        {
            for (int j = 0; j < fn->temp; j++) //각 함수 실행
                anyFunction(fn->moon[j]);
            v->iValue++;
        }
    }
    else
    {
        for (int i = 0; i < fn->factors[1].value.iValue; i++) //v번
        {
            for (int j = 0; j < fn->temp; j++) //각 함수 실행
                anyFunction(fn->moon[j]);
        }
    }
    for (int i = 0; i < fn->temp; i++)
        free(fn->moon[i]);
    return -1;
}
int Function_If_end(function* fn)
{
    variable* v = &fn->factors[0].value;
    ind = 0;
    for (int j = 0; j < fn->temp; j++) //각 함수 실행
        anyFunction(fn->moon[j]);
    for (int i = 0; i < fn->temp; i++)
        free(fn->moon[i]);
    return -1;
}
int Function_fun_end(function* fn)
{
    itisRValue(&fn->factors[0].value);
    
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
    defs[defC].fun = Function_User;
    for (int i = 0; i < fn->temp; i++)
    {
        def defNow = getdefbyStr(fn->moon[i]);
        if (isMatch(defNow.name, "인수"))
        {
            function* ll = LastF;
            LastF = malloc(sizeof(function));
            if (LastF == NULL)
            {
                LastF = ll;
                return 0;
            }
            LastF->returnTo = ll;

            getfunbyDef(&defNow, fn->moon[i], LastF);
            splitFactors(*LastF, fn->moon[i]);
            for (int i = 0; i < defNow.argsCount; i++)
            {
                if (!LastF->factors[i].isMatched) continue; // 없는 인수는 그냥 넘어간다.
                //sayAtoB(funNow.factors[i].startF, funNow.factors[i].endF);
                getValueinFactor(&LastF->factors[i]);
                LastF->factors[i].value.isMatched = true;
            }
            if (!LastF->factors[1].isMatched) // 조사가 없음 -> option으로 가야됨.
            {
                defs[defC].options[defs[defC].optionsCount] = setString(LastF->factors[0].value.sValue);
                defs[defC].optionsCount++;
            }
            else
            {
                int c = defs[defC].argsCount, argCount = 0;
                defs[defC].argsName[c] = setString(LastF->factors[0].value.sValue);
                for (int argCount = 0; LastF->factors[argCount + 1].isMatched; argCount++) { }
                defs[defC].args[c] = malloc(sizeof(char**) * argCount);
                defs[defC].argNameCount[c] = argCount;
                for (int i = 0; i < argCount; i++)
                    defs[defC].args[c][i] = setString(LastF->factors[i + 1].value.sValue);
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
    return -1;
}
int Function_include(function* fn)
{
    variable value = fn->factors[0].value;
    itisRValue(&value);
    if (value.type != sV) return 0;

    FILE* stream;
    char chars[lineLength];
    if (fopen_s(&stream, value.sValue, "r") == 0 && stream != NULL)
    {
        while (fgets(chars, lineLength, stream) != NULL)
        {
            changeSpacetoNull(chars);
            anyFunction(chars);
        }
        fclose(stream);
    }
    return 0;
}
int Function_valid(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    for (int i = 0; i < funLoopingNow->define->argsCount; i++)
    {
        if (isMatch(value2.sValue, funLoopingNow->define->argsName[i]))
        {
            value1.vValue->iValue = funLoopingNow->factors[i].isMatched;
            value1.vValue->type = iV;
            return 0;
        }
    }
    for (int i = 0; i < funLoopingNow->define->optionsCount; i++)
    {
        if (isMatch(value2.sValue, funLoopingNow->define->options[i]))
        {
            //printf("%d", funLoopingNow->options[i].isMatched);
            value1.vValue->iValue = funLoopingNow->options[i].isMatched;
            value1.vValue->type = iV;
            return 0;
        }
    }
    return 0;
}
int Function_Set(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
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
    return 0;
}
int Function_Add(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue += value2.iValue;
    }
    return 0;
}
int Function_Minus(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue -= value2.iValue;
    }
    return 0;
}
int Function_Multi(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue *= value2.iValue;
    }
    return 0;
}
int Function_Devide(function* fn)
{
    variable value1 = itisLValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
    if (value1.type != vV) return 0;
    if (value1.vValue->type == iV && value2.type == iV)
    {
        value1.vValue->iValue /= value2.iValue;
    }
    return 0;
}
int Function_Listen(function* fn)
{
    variable value = itisLValue(&fn->factors[0].value);
    char* cc = malloc(lineLength);
    getSO(cc, "");
    if (itCanInt(cc))
    {
        value.vValue->iValue = getIntinStr(cc);
        value.vValue->type = iV;
    }
    else
    {
        value.vValue->sValue = setString(cc);
        value.vValue->type = sV;
    }
    return 0;
}
int Function_Say(function* fn)
{
    variable value = itisRValue(&fn->factors[0].value);
    if (fn->options[0].isMatched)
    {
        if (value.type == iV)
            printf("%d", value.iValue);
        else if (value.type == sV)
            printf("%s", value.sValue);
    }
    else
    {
        if (value.type == iV)
            printf("%d\n", value.iValue);
        else if (value.type == sV)
            printf("%s\n", value.sValue);
    }
    return 0;
}
int Function_Print(function* fn)
{
    variable value1 = itisRValue(&fn->factors[0].value);
    variable value2 = itisRValue(&fn->factors[1].value);
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
    return 0;
}