#pragma once

/// <summary>
/// Find how much this text has byte in utf-8.
/// </summary>
/// <param name="byte">First byte of utf-8 one letter.</param>
/// <returns>utf-8 bytes. 1, 2, 3, 4 https://en.wikipedia.org/wiki/UTF-8#Encoding</returns>
int getitsbyte(unsigned char byte);

/// <summary>
/// Get line text input in utf-8 windows by _getch() in coino.h
/// </summary>
/// <param name="writeAt">pointer to get text</param>
/// <param name="various">line-left-text. console arrow.</param>
/// <returns>if successed, writeAtas it is. if that get error: null.</returns>
char* getSO(char* writeAt, const char* various);
