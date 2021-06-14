#pragma once
#include "operator.h"
void sayAtoB(char* A, char* B) //A 포인터부터 B 포인터까지 화면에 표시함.
{
    for (char* i = A; i < B; i++)
    {
        printf("%c", *i);
    }
    printf("\n");
}
int next_is_opperator(const char* po) //띄어쓰기만 무시하며 다음문자가 연산자인지 확인함.
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
char* setString(const char* item) //문자열을 새로 할당해 복사함.
{
    int strlen = stringLength(item, 0);
    char* str = malloc(strlen + 1);
    if (str == NULL) return NULL;
    for (int i = 0; i < strlen; i++)
        str[i] = item[i];
    str[strlen - 1] = '\0';
    return str;
}

int isFair(const char* word, factor it, int* ret) //factor의 인수 형식 중 맞는게 있으면 반환한다. ret에 글자의 길이를 넣는다.
{
    for (int i = 0; i < it.nameCount; i++)
    {
        if (isMatch(word, it.name[i]))
        {
            *ret = stringLength(word, ' ');
            return 1;
        }
    }
    return 0;
}
