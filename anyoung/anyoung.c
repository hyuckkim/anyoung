/// 2021년 3월 ~ 
/// 김광혁이 만듦.
/// 사용 운영체제 : Windows 10 64bit 20H2 19042.867
/// UTF-8 사용 beta 기능 사용시에만 사용 가능함
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "types.h"
#include "kinput.h"
#include "annyCore.c"

#define SHUTDOWN 3

int useFunction(const char* line, def* define);
int saveFunction(const char* line, int indent, function* saveTo);
void anyFunction(char* line);
void freeFunction(function* funNow);
def* searchDefine(char* str);
extern function* initFunction(def* define, const char* str);
extern void splitFactors(function fun, const char* str);
extern int Anyoung_Init();

def* defs;
int defC = 0;
int defM = 1;
variable* vars;
char** varNames;
int varC;
int varM = 1;

function* LastF = NULL;
function* funLoopingNow = NULL;
int canInsert;
int ind = 0;


int main(int argc, char** argv)
{
	Anyoung_Init();
	char chars[lineLength] = "default";
	FILE* stream = NULL;

	int getBy, getIn;
	if (argc == 1)
	{
		anyFunction("말하기 \"어순에 상관없는 한글 스크립트 언어 안녕\"을");
		anyFunction("말하기 \"v0.22 실행중\"을");
		anyFunction("말하기 \"'도움'으로 명령어 확인\"을");
		getBy = 0;
	}
	else
	{
		if (fopen_s(&stream, argv[1], "r") != 0 || stream == NULL) 
		{
			printf("파일을 여는 데 실패하였습니다.");
			return 0;
		}
		getBy = 1;
	}

	while (1)
	{
		if (getBy == 0) 
		{
			if (ind == 0) getIn = getSO(chars, ">>> ");
			else getIn = getSO(chars, "... ");
			if (getIn != 0) break;
		}
		else 
		{
			getIn = (int)fgets(chars, lineLength, stream);
			if (getIn == 0) break;
		}
		ChangeLFtoNULL(chars);

		anyFunction(chars);
	}
	if (stream != NULL) fclose(stream);
	return 0;
}
//문자열을 판단해 함수를 실행할지 저장할지 결정한다.
void anyFunction(char* line)
{
	def* defNow = searchDefine(line);
	if (defNow == NULL) return;
	switch (ind)
	{
	case 0:
		useFunction(line, defNow);
		break;
	case 1:
		if (defNow->usecondit)
			useFunction(line, defNow);
		else
			if (canInsert)
				saveFunction(line, defNow->useindent, LastF);
		break;
	default:
		saveFunction(line, defNow->useindent, LastF);
		break;
	}
}
//함수를 실제로 실행한다.
int useFunction(const char* line, def* define)
{
	function* NewF = initFunction(define, line); //공간 할당
	if (NewF == NULL)
	{
		return -1;
	}

	NewF->returnTo = LastF; // 스택 구현
	splitFactors(*NewF, line);
	// 인수별로 문자열에서 다른 처리로 변경함.
	for (int i = 0; i < define->argsCount; i++)
	{
		if (!NewF->factors[i].isMatched) continue;
		NewF->factors[i].value = getValueinFactor(NewF->factors[i].startF, NewF->factors[i].endF);
		NewF->factors[i].value.isMatched = true;
	}
	ind += define->fun(NewF);
	if (ind == 0 || define->usecondit) freeFunction(NewF); // 함수 사용이 종료되면 삭제
	else LastF = NewF; // if문이라면.

	return 0;
}
//사용이 끝난 함수를 해제한다.
void freeFunction(function* funNow)
{
	if (funNow->factors != NULL)
	{
		for (int i = 0; i < funNow->define->argsCount; i++)
		{
			if (funNow->factors[i].isMatched && funNow->factors[i].value.type == sV)
			{
				free(funNow->factors[i].value.sValue);
			}
		}
		free(funNow->factors);
	}
	if (funNow->options != NULL)
	{

		free(funNow->options);
	}
	free(funNow);
	funNow = NULL;
}
//함수를 저장한다.
int saveFunction(const char* line, int indent, function* saveTo) 
{
	ind += indent;
	saveTo->moon[saveTo->temp] = setString(line);
	saveTo->temp++;
	return 0;
}
//name과 같은 이름의 변수가 있다면 반환한다.
variable* getVariable(char* name)
{
	for (int i = 0; i < varC; i++)
	{
		if (isMatch(varNames[i], name)) return &vars[i];
	}
	return NULL;
}
//변수 개수를 하나 추가하고 배열이 꽉 찼다면 배열 길이를 두배로 한다.
void VariableInserted()
{
	varC++;
	if (varC >= varM) 
	{
		varM *= 2;
		variable* vTemp = (variable*)realloc(vars, varM * sizeof(variable));
		if (vTemp != NULL) vars = vTemp;
		char** nTemp = (char**)realloc(varNames, varM * sizeof(char*));
		if (nTemp != NULL) varNames = nTemp;
	}
}
//문자열에서 새로운 변수를 만들어 반환한다.
variable* makeVariable(char* name)
{
	varNames[varC] = setString(name);
	vars[varC].type = iV;
	vars[varC].iValue = 0;
	VariableInserted();
	return &vars[varC - 1];
}
//현재 함수의 인수 중 이름이 맞는 것이 있다면 반환한다.
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
//해당 이름의 변수가 있다면 반환하고 없다면 새로 만든다.
variable* getVar(char* name)
{
	variable* v = getVariable(name);
	if (v != NULL) return v;
	if (funLoopingNow != 0) v = GetArgument(name);
	if (v != NULL) return v;
	return makeVariable(name);
}

//문장의 글자별로 함수가 있는지 찾아 반환한다.
def* searchDefine(char* str) 
{
	for (int i = 0; str[i] != 0; i += getitsbyte(str[i]))
	{ 
		if (str[i] == '"') i += stringLength(&str[i], '"');
		for (int j = 0; j < defC; j++)
		{ 
			if (isMatch(&str[i], defs[j].name)) return &defs[j];
		}
	}
	return NULL;
}
//function* 형식의 변수를 할당해 반환한다.
function* initFunction(def* define, const char* str)
{
	function* result = (function*)malloc(sizeof(function));
	if (result == NULL)
	{
		return NULL;
	}
	result->define = define;
	result->name = define->name;
	if (define->argsCount != 0)
	{
		result->factors = (factor*)malloc(sizeof(factor)
			* define->argsCount);
		if (result->factors == NULL)
		{
			free(result);
			return NULL;
		}
		for (int i = 0; i < define->argsCount; i++)
		{
			result->factors[i].name = define->args[i];
			result->factors[i].nameCount = define->argNameCount[i];
			result->factors[i].isMatched = false;
			result->factors[i].value.isMatched = false;
		}
	}
	else
	{
		result->factors = NULL;
	}
	if (define->optionsCount != 0)
	{
		result->options = (factor*)malloc(sizeof(factor)
			* define->optionsCount);
		if (result->options == NULL)
		{
			if (define->argsCount != 0)
			{
				free(result->factors);
			}
			free(result);
			return NULL;
		}
		for (int i = 0; i < define->optionsCount; i++)
		{
			result->options[i].name = define->options;
			result->options[i].nameCount = 1;
			result->options[i].isMatched = false;
			result->options[i].value.isMatched = false;
		}
	}
	else
	{
		result->options = NULL;
	}
	return result;
}
void splitFactors(function fun, const char* str) // 문장 factor별로 잘라주기
{
	int starti = 0;
	for (int i = 0; str[i] != 0; i++) {
		for (int j = 0; j < fun.define->argsCount; j++) {
			if (fun.factors[j].isMatched) continue;
			int nameIndex;
			if (isFair(&str[i], fun.factors[j], &nameIndex) && !next_is_opperator(&str[i]))
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
				starti = i + stringLength(fun.define->name, ' ');
			}
		}
		for (int j = 0; j < fun.define->optionsCount; j++) {
			if (fun.options[j].isMatched) continue;
			int nameIndex;
			if (isFair(&str[i], fun.options[j], &nameIndex) && !next_is_opperator(&str[i]))
			{
				fun.options[j].isMatched = true;
				fun.options[j].value.isMatched = true;
				starti = i + nameIndex; //첫 단어 잘리는 부분 + 조사 (stringLengthSpace로 잘라서 스페이스바는 알아서 걸러짐)
			}
		}
	}
	//if (ss < fun.define.argsCount) printf("오류 발생. 인수 개수와 형식이 맞지 않습니다.\n");
}