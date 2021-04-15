/// 2021년 3월 ~ 
/// 김광혁이 만듦.
/// 사용 운영체제 : Windows 10 64bit 20H2 19042.867
/// UTF-8 사용 beta 기능 사용시에만 사용 가능함
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdarg.h>
#include "types.h"
#include "kinput.h"
#include "annyCore.h"
#include "annyCore.c"

int main(int argc, char** argv)
{
    annyCore_init();
    char chars[lineLength] = "default";
    int indent = 1;
    if (argc == 1)
    {
        anyFunction("말하기 \"어순에 상관없는 한글 스크립트 언어 안녕\"을");
        anyFunction("말하기 \"v0.13 실행중\"을");
        anyFunction("말하기 \"'도움'으로 명령어 확인\"을");
        while (1)
        {
            if (indent == 1) getSO(chars, ">>> "); //todo : 운영체제별로 읽는 방법 다르게.
            else getSO(chars, "... ");
            if (chars[0] != 3) indent = anyFunction(chars) + 1;
            else return 0;
        }
    }
    else
    {
        FILE* stream;

        if (fopen_s(&stream, argv[1], "r") == 0 && stream != NULL)
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
}
