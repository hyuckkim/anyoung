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
    char chars[80] = "default";
    int indent = 1;
    if (argc == 1)
    {
        anyFunction("말하기 \"어순에 상관없는 한글 스크립트 언어 안녕\"을");
        anyFunction("말하기 \"v0.1 실행중\"을");
        anyFunction("말하기 \"'도움'으로 명령어 확인\"을");
        while (1)
        {
            if (indent == 1) printf(">>> ");
            else printf("... ");
            getSO(chars); //TODO : 운영체제별로 입력 다르게 받기 (리눅스에선 그냥 gets 써도될듯)
            if (chars[0] == '\n' || chars[0] == '\0') indent--;
            else indent += anyFunction(chars);
            if (indent == 0) return 0;
        }
    }
    else
    {
        FILE* stream;
        
        if (fopen_s(&stream, argv[1], "r") == 0 && stream != NULL)
        {
            while (fgets(chars, 80, stream) != NULL)
            {
                changeSpacetoNull(chars);
                anyFunction(chars);
            }
            fclose(stream);
        }
        return 0;
    }
}
