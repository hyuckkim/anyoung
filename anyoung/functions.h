/// <summary>
/// 이게 어떻게 가능한지 궁금한 사람을 위해 : 이거 파일 맨 위에 있는거 아님. annyCore.c의 360번줄쯤에 있음.
/// </summary>

void Function_Help()
{
    printf("\n흐름\n");
    printf("여기까지 \t\t\t흐름 함수를 어디까지 실행할지의 조건이 됩니다.\n\n");
    printf("[ㅁ 로] ㅇ 번 되풀이 \t\t'여기까지' 까지의 함수를 ㅇ번 실행합니다. ㅁ에 동작 횟수를 0부터 기록합니다.\n");
    printf("ㅁ 면 조건\t\t\tㅁ가 숫자고 1이라면 '여기까지' 까지의 함수를 실행합니다.\n");
    printf("아니면\t\t\t\t조건과 여기까지 사이에 넣어 함수를 실행할지를 반전합니다.\n");
    printf("\n데이터\n");
    printf("ㅁ을/를 ㅇ으로/로 정하기\t변수 ㅁ의 값을 ㅇ로 지정합니다. ㅁ이 없다면 새로 만듭니다.\n");
    printf("ㅁ을/를 ㅇ만큼 더하기\t\t변수 ㅁ의 값에 ㅇ를 더합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ을/를 ㅇ만큼 빼기\t\t변수 ㅁ의 값에 ㅇ를 뺍니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ을/를 ㅇ만큼 곱하기\t\t변수 ㅁ의 값에 ㅇ를 곱합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("ㅁ을/를 ㅇ만큼 나누기\t\t변수 ㅁ의  값에 ㅇ를 나눕니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.\n");
    printf("\n화면 입출력\n");
    printf("ㅁ 을/를 말하기 \t\tㅁ을 개행문자와 함께 출력합니다.\n");
    printf("ㅁ 을/를 [ㅇ 번] 표시하기 \tㅁ을 ㅇ번 출력합니다. ㅇ는 숫자여야 합니다.\n");
    printf("도움\t\t\t\t함수에 대한 도움말을 봅니다.");
    printf("\n");
}
extern int anyFunction(char* line);
void Function_Loop(function* looping)
{
    looping->moon = malloc(sizeof(char* ) * 40);
    canInsert = 1;
}
void Function_If(function* looping)
{
    looping->moon = malloc(sizeof(char*) * 40);
    if (looping->factors[0].value.type == 0 && looping->factors[0].value.iValue != 0) // 0이 아닌 int value : true.
        canInsert = 1;
    else
        canInsert = 0; //조건문 시작할 때 조건 비교해서 틀리면 아예 메모리에 저장 안함.
}
void Function_Loop_end(function* fn)
{
    funC++; //안에서 쓰이지 않아도 anyFunction에서 쓰므로 변경.
    variable* v = fn->factors[0].value.vValue;
    v->iValue = 0;
    ind = 0;
    for (int i = 0; i < fn->factors[1].value.iValue; i++) //v번
    {
        for (int j = 0; j < temp[funC - 1]; j++) //각 함수 실행
            anyFunction(fn->moon[j]);
        v->iValue++;
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
void Function_Set(variable value1, variable value2)
{
    if (value1.type == 2)
    {
        switch (value2.type)
        {
        case 0:
            value1.vValue->type = 0;
            value1.vValue->iValue = value2.iValue;
            break;
        case 1:
            value1.vValue->type = 1;
            value1.vValue->sValue = setString(value2.sValue);
            break;
        case 2:
            if (value2.vValue->type == 0)
            {
                value1.vValue->type = 0;
                value1.vValue->iValue = value2.vValue->iValue;
            }
            else if (value2.vValue->type == 1)
            {
                value1.vValue->type = 1;
                value1.vValue->sValue = setString(value2.vValue->sValue);
            }
            break;
        }
    }
}
void Function_Add(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue += value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue += value2.vValue->iValue;
        }
    }
}
void Function_Minus(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue -= value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue -= value2.vValue->iValue;
        }
    }
}
void Function_Multi(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue *= value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue *= value2.vValue->iValue;
        }
    }
}
void Function_Devide(variable value1, variable value2)
{
    if (value1.type == 2 && value1.vValue->type == 0)
    {
        if (value2.type == 0)
        {
            value1.vValue->iValue /= value2.iValue;
        }
        else if (value2.type == 2)
        {
            value1.vValue->iValue /= value2.vValue->iValue;
        }
    }
}
void Function_Say(variable value)
{
    if (value.type == 0)
        printf("%d\n", value.iValue);
    else if (value.type == 1)
        printf("%s\n", value.sValue);
    else
    {
        if(value.vValue->type == 0)
            printf("%d\n", value.vValue->iValue);
        else if (value.vValue->type == 1)
            printf("%s\n", value.vValue->sValue);
    }
}
void Function_Print(variable value1, variable value2)
{
    if (value2.isMatched == 1)
    {
        for (int i = 0; i < value2.iValue; i++)
        {
            if (value1.type == 0)
                printf("%d", value1.iValue);
            else if (value1.type == 1)
                printf("%s", value1.sValue);
            else
            {
                if (value1.vValue->type == 0)
                    printf("%d", value1.vValue->iValue);
                else if (value1.vValue->type == 1)
                    printf("%s", value1.vValue->sValue);
            }
        }
    }
    else
    {
        if (value1.type == 0)
            printf("%d", value1.iValue);
        else if (value1.type == 1)
            printf("%s", value1.sValue);
        else
        {
            if (value1.vValue->type == 0)
                printf("%d", value1.vValue->iValue);
            else if (value1.vValue->type == 1)
                printf("%s", value1.vValue->sValue);
        }
    }
    printf("\n");
}