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

    while (chars[0] != '\n' && chars[0] != '\0')
    {
        printf(">>> ");
        getSO(chars); //TODO : 운영체제별로 입력 다르게 받기 (리눅스에선 그냥 gets 써도될듯)
        anyFunction(chars);
    }
}
