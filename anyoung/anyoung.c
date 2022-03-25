/// 2021년 3월 ~ 
/// 김광혁이 만듦.
/// 사용 운영체제 : Windows 10 64bit 20H2 19042.867
/// UTF-8 사용 beta 기능 사용시에만 사용 가능함
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include "types.h"
#include "kinput.h"
#include "usefunction.h"
#include "operator.h"

extern int Anyoung_Init();

extern int indent;

FILE* openSourceFile(int argc, char** argv) {
	FILE* stream = NULL;
	char argu[20] = ""; //디버깅 시 특정 소스 파일 입력
	if (argu[0] != '\0') {
		if (fopen_s(&stream, argu, "r") != 0 || stream == NULL) {
			printf("파일을 여는 데 실패하였습니다.");
			return NULL;
		}
		return stream;
	}
	else if (argc != 1) {
		if (fopen_s(&stream, argv[1], "r") != 0 || stream == NULL) {
			printf("파일을 여는 데 실패하였습니다.");
			return NULL;
		}
		else {
			return stream;
		}
	}
	else {
		return NULL;
	}
}
char* getLine(FILE* stream, char* buffer)
{
	if (stream == NULL)
	{
		if (indent == 0) return getSO(buffer, ">>> ");
		else return getSO(buffer, "... ");
	}
	else
	{
		return fgets(buffer, lineLength, stream);
	}
}
int main(int argc, char** argv)
{
	function* LastF = NULL;
	Anyoung_Init();
	
	SetConsoleOutputCP(CP_UTF8);
	char chars[lineLength] = "default";
	FILE* stream = openSourceFile(argc, argv);

	char* getIn;
	if (stream == NULL)
	{
		anyFunction("말하기 \"어순에 상관없는 한글 스크립트 언어 안녕\"을");
		anyFunction("말하기 \"v0.3\" + \" 실행중\"을");
		anyFunction("말하기 \"'도움'으로 명령어 확인\"을");
	}

	while (1)
	{
		getIn = getLine(stream, chars);
		if (getIn == NULL) 
			break;
		ChangeLFtoNULL(chars);

		anyFunction(chars);
	}
	if (stream != NULL) fclose(stream);
	return 0;
}