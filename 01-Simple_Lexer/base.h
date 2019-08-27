#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef unsigned long long      uint64;

/* 判断是否是字母 */
int isAlpha(char ch);
/* 判断是否是数字 */
int isDigit(char ch);
/* 判断是否是空白字符 */
int isBlank(char ch);


#endif
