/// 2021년 3월 ~ 
/// 김광혁이 만듦.
/// 사용 운영체제 : Windows 10 64bit 20H2 19042.867
/// UTF-8 사용 beta 기능 사용시에만 사용 가능함
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "types.h"
#include "kinput.h"
#include "annyCore.h"
#include "usefunction.h"
#include "operator.h"

extern int Anyoung_Init();

extern int ind;

int main(int argc, char** argv)
{
	function* LastF = NULL;
	Anyoung_Init();
	char chars[lineLength] = "default";
	FILE* stream = NULL;

	int getBy;
	char* getIn;
	if (argc == 1)
	{
		anyFunction("말하기 \"어순에 상관없는 한글 스크립트 언어 안녕\"을");
		anyFunction("말하기 \"v0.3 실행중\"을");
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
			if (getIn == NULL) break;
		}
		else 
		{
			getIn = fgets(chars, lineLength, stream);
			if (getIn == NULL) break;
		}
		ChangeLFtoNULL(chars);

		anyFunction(chars);
	}
	if (stream != NULL) fclose(stream);
	return 0;
}