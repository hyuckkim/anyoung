/// 2021년 3월 ~ 
/// 김광혁이 만듦.
/// 사용 운영체제 : Windows 10 64bit 20H2 19042.867
/// UTF-8 사용 beta 기능 사용시에만 사용 가능함
#include <stdio.h>
#include "kinput.h"
#include "annyCore.c"

int main(int argc, char** argv)
{
    annyCore_init();
    if (argc == 1)
    {
        char chars[80] = "default";
        anyFunction("말하기 \"어순에 상관없는 한글 프로그래밍 언어 안녕\"을");
        anyFunction("말하기 \"v0.1 실행중\"을");
        anyFunction("말하기 \"'도움'으로 명령어 확인(아직 안됨)\"을");
        while (1)
        {
            printf(">>> ");
            getSO(chars); //TODO : 운영체제별로 입력 다르게 받기 (리눅스에선 그냥 gets 써도될듯)
            if (chars[0] == '\n' || chars[0] == '\0') return 0;
            anyFunction(chars);
        }
    }
    else
    {
        printf("%s", argv[1]);
    }
}
