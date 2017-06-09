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

int int_char_length(int i);

#define TO_STRING(i, str) char str[int_char_length(i)]; {\
    int a = int_char_length(i);\
    tostring(i, str, 10);\
}

void tostring(int num, char *str, int base);


#endif //STRUCTURES_STR_H
