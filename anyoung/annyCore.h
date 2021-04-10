int isMatch(char* word1, char* word2) //포인터부터 시작해 '\0'이나 ' '까지 같은지 비교함.
{
    int i = 0;
    while (1)
    {
        if (word1[i] != word2[i]) return 0;
        i++;
        if (word1[i] == '\0' || word1[i] == ' ' || word1[i] == '\t') goto breakByFirst;
        if (word2[i] == '\0' || word2[i] == ' ' || word1[i] == '\t') goto breakBySecond;
    }
breakByFirst:
    if (word2[i] == '\0' || word2[i] == ' ' || word1[i] == '\t') return 1;
    else return 0;
breakBySecond:
    if (word1[i] == '\0' || word1[i] == ' ' || word1[i] == '\t') return 1;
    else return 0;
}
int getPriority(char op) //연산자 기호 하나를 주고 연산자의 우선순위를 반환함.
{
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    if (op == '=' || op == '<' || op == '>') return 0;
    return -1;
}
void sayAtoB(char* A, char* B) //A 포인터부터 B 포인터까지 화면에 표시함.
{
    for (char* i = A; i < B; i++)
    {
        printf("%c", *i);
    }
    printf("\n");
}
int next_is_opperator(char* po) //띄어쓰기만 무시하며 다음문자가 연산자인지 확인함.
{
    int i = 0;
    while (1)
    {
        i += 1;
        switch (po[i])
        {
        case ' ':
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case '<':
        case '>':
            return 1;
        case '\0':
            return 0;
        default:
            return 0;
        }
    }
}
void changeSpacetoNull(char* item) // 지정 포인터부터 시작해 앞에 있는 개행문자를 널문자로 변환.
{
    int i;
    for (i = 0; item[i] != '\n' && item[i] != '\0'; i++) { }
    item[i] = '\0';
}
int stringLength(char* item) //지정 포인터부터 시작해 null문자가 아닌 구간의 길이를 반환함.
{
    int i;
    for (i = 0; item[i] != 0; i++) {}
    return i + 1;
}
int stringLengthSpace(char* item) //위와 같지만 띄어쓰기에서도 자르고 반환함.
{
    int i;
    for (i = 0; item[i] != 0 && item[i] != ' '; i++) {}
    return i + 1;
}
int stringLengthQ(char* po) //대상 포인터부터 '"'가 얼마나 앞에 있는지를 반환함.
{
    for (int i = 1; po[i] != '\0'; i++)
    {
        if (po[i] == '"') return i;
    }
    return -1;
}
int logSize(int v)
{
    int res = 1;
    for(int i = v; i >= 10; i /= 10, res++) { }
    return res;
}
int logScale(int v, int is)
{
    int in = 1;
    for (int i = 0; i < is; i++) in *= 10;
    return (v / in) % 10; //is번 자리수를 가장 앞으로 당기고 1의 자리수만 반환.
}
char* setString(char* item) //문자열을 새로 할당해 복사함.
{
    int strlen = stringLength(item);
    char* str = malloc(strlen + 1);
    if (str == NULL) return NULL;
    for (int i = 0; i < strlen; i++)
    {
        str[i] = item[i];
    }
    str[strlen - 1] = '\0';
    return str;
}

int isFair(char* word, factor it, int* ret, int deb) //factor의 인수 형식 중 맞는게 있으면 반환한다. ret에 글자의 길이를 넣는다.
{
    if (deb == 1) printf("%d번 반복...", it.nameCount);
    for (int i = 0; i < it.nameCount; i++)
    {
        if (deb == 1) printf("%s / %s\n", word, it.name[i]); // For debug : 조건 순회하며 확인하기
        if (isMatch(word, it.name[i]))
        {
            *ret = stringLengthSpace(word);
            return 1;
        }
    }
    return 0;
}

def defs[80];
int defC = 0, defM = 10;
variable vars[80];
char* varNames[80];
int varC;
variable* getVariable(char* name)
{
    for (int i = 0; i < varC; i++)
    {
        if (isMatch(varNames[i], name)) return &vars[i];
    }
    return NULL;
}
variable* makeVariable(char* name)
{
    varNames[varC] = setString(name);
    vars[varC].type = iV;
    vars[varC].iValue = 0;
    varC++;
    return &vars[varC - 1];
}
variable* setVariable(variable* var)
{
    vars[varC] = *var;
    varC++;
    return &vars[varC - 1];
}
function* funLoopingNow = 0;
variable* GetArgument(char* name)
{
    //functions[funC]->factors[0].value.sValue
    for (int i = 0; i < funLoopingNow->define->argsCount; i++)
    {
        if (isMatch(funLoopingNow->define->argsName[i], name))
        {
            if (funLoopingNow->factors[i].value.type == vV)
                return funLoopingNow->factors[i].value.vValue;
            return &funLoopingNow->factors[i].value;
        }
    }
    return NULL;
}
variable* setVar(char* name)
{
    variable* v;
    v = getVariable(name);
    if (v == NULL && funLoopingNow != 0) v = GetArgument(name);
    if (v == NULL) v = makeVariable(name);
    return v;
}
variable* getVar(char* name)
{
    variable* v = getVariable(name);
    if (v != NULL) return v;
    if (funLoopingNow != 0) v = GetArgument(name);
    if (v != NULL) return v;
    return makeVariable(name);
}

int errorExcept = 0;
def getdefbyStr(char* str) // 문장에서 함수 이름을 찾아 반환함.
{
    errorExcept = 0;
    for (int i = 0; str[i] != 0; i++) { //문자열의 문자마다
        if (str[i] == '"') i += stringLengthQ(&str[i]); //따옴표 있으면 문자열 영역이니까 넘어감.
        for (int j = 0; j < defC; j++) { //함수들마다
           // printf("%s / %s\n", &str[i], defs[j].name);
            if (isMatch(&str[i], defs[j].name)) return defs[j]; //함수 이름이 맞으면 반환.
        }
    }
    errorExcept = 1;
    return defs[0];
}
void getfunbyDef(def* define, char* str, function* result) // 함수로 변수를 만들어 result 포인터를 바꾼다.
{
    result->define = define;
    result->name = define->name;
    result->factors = malloc(sizeof(factor)
        * define->argsCount); //sizeof(포인터)는 동적할당 관계없이 무조건 4라서 Count를 따로만듦
    result->options = malloc(sizeof(factor)
        * define->optionsCount);
    if (result->factors != NULL) for (int i = 0; i < define->argsCount; i++)
    {
        result->factors[i].name = define->args[i];
        result->factors[i].nameCount = define->argNameCount[i];
        result->factors[i].isMatched = false;
        result->factors[i].value.isMatched = false;
    }
    if (result->options != NULL) for (int i = 0; i < define->optionsCount; i++)
    {
        result->options[i].name = define->options;
        result->options[i].nameCount = 1;
        result->options[i].isMatched = false;
        result->options[i].value.isMatched = false;
    }
}
void splitFactors(function fun, char* str) // 문장 factor별로 잘라주기
{
    int starti = 0;
    for (int i = 0; str[i] != 0; i++) {
        for (int j = 0; j < fun.define->argsCount; j++) {
            if (fun.factors[j].isMatched) continue;
            int nameIndex;
            if (isFair(&str[i], fun.factors[j], &nameIndex, 0) && !next_is_opperator(&str[i]))
            {
                fun.factors[j].startF = str + starti;
                fun.factors[j].endF = str + i;
                fun.factors[j].isMatched = true;
                fun.factors[j].value.isMatched = true;
                starti = i + nameIndex; //첫 단어 잘리는 부분 + 조사 (stringLengthSpace로 잘라서 스페이스바는 알아서 걸러짐)
                break;
            }
            else if (isMatch(fun.define->name, &str[i]))
            {
                starti = i + stringLengthSpace(fun.define->name);
            }
        }
        for (int j = 0; j < fun.define->optionsCount; j++) {
            if (fun.options[j].isMatched) continue;
            int nameIndex;
            if (isFair(&str[i], fun.options[j], &nameIndex, 0) && !next_is_opperator(&str[i]))
            {
                fun.options[j].isMatched = true;
                fun.options[j].value.isMatched = true;
                starti = i + nameIndex; //첫 단어 잘리는 부분 + 조사 (stringLengthSpace로 잘라서 스페이스바는 알아서 걸러짐)
            }
        }
    }
    //if (ss < fun.define.argsCount) printf("오류 발생. 인수 개수와 형식이 맞지 않습니다.\n");
}