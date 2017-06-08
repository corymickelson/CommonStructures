//
// Created by red on 6/7/17.
//

#ifndef STRUCTURES_STR_H
#define STRUCTURES_STR_H

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef char* str;

#define INT_CHAR_LENGTH(i) int_char_length(i)
//#define TO_STRING(i, buf) char[INT_CHAR_LENGTH(i)] buf; tostring(i, buf, 10)
#define TO_STRING(i, str) char str[INT_CHAR_LENGTH(i)]; {\
    int a = INT_CHAR_LENGTH(i);\
    tostring(i, str, 10);\
}

void tostring(int num, char *str, int base);

int int_char_length(int i);

#endif //STRUCTURES_STR_H