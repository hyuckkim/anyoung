#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "operator.h"

variable* vars;
char** varNames;
int varC;
int varM = 1;
extern function* funLoopingNow;

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
	if (funLoopingNow != NULL) v = GetArgument(name);
	if (v != NULL) return v;
	return makeVariable(name);
}

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