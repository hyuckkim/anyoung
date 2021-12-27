#pragma once

typedef enum { sol, duo, tri, qua, funA, funB, LineBreak, BackSpace } textInfo;

void printMultibyteChar(textInfo thisInfo, char* utf8, char* nooNow);

int getitsbyte(unsigned char byte);

int getitsbyte(unsigned char byte);

int getSO(char* writeAt, const char* various);