#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "operator.h"
#include "kinput.h"
#include "stack.h"

#include "usefunction.h"

int canInsert;
function* LastF;
int indent;

void anyFunction(char* line)
{
	def* defNow = searchDefine(line);
	if (defNow == NULL) return;
	switch (indent)
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
		int argDataLength;
		stack* argData = sliceFactorData(NewF->factors[i].startF, NewF->factors[i].endF, &argDataLength);
		NewF->factors[i].value = calcStackToVariable(argData, argDataLength);

		NewF->factors[i].value.isMatched = true;
	}
	indent += define->fun(NewF);
	if (indent == 0 || define->usecondit) freeFunction(NewF); // 함수 사용이 종료되면 삭제
	else LastF = NewF; // if문이라면.

	return 0;
}

void freeFunction(function* fun)
{
	if (fun->factors != NULL)
	{
		for (int i = 0; i < fun->define->argsCount; i++)
		{
			if (fun->factors[i].isMatched && fun->factors[i].value.type == sV)
			{
				free(fun->factors[i].value.sValue);
			}
		}
		free(fun->factors);
	}
	if (fun->options != NULL)
	{
		free(fun->options);
	}
	free(fun);
	fun = NULL;
}
int saveFunction(const char* line, int currentIndent, function* saveTo)
{
	saveTo->line[saveTo->linecount] = setString(line);
	saveTo->linecount++;
	indent += currentIndent;
	return 0;
}
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

extern int defC, defM;
extern def* defs;

void insertDefine()
{
	defC++;
	if (defC >= defM) {
		defM *= 2;
		void* dTemp = realloc(defs, defM * sizeof(def));
		if (dTemp != NULL) defs = (def*)dTemp;
	}
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
			int nameIndex = 0;
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