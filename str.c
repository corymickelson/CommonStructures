//
// Created by red on 6/7/17.
//

#include "str.h"

void inplace_reverse(char *str) {
    if (str) {
        char *end = str + strlen(str) - 1;

        // Thank you stackoverflow https://stackoverflow.com/questions/784417/reversing-a-string-in-c
#define XOR_SWAP(a, b) do\
        {\
            a^=b;\
            b^=a;\
            a^=b;\
        }while(0)

        while (str < end) {
            XOR_SWAP(*str, *end);
            str++;
            end--;
        }
#undef XOR_SWAP
    }
}

void tostring(int num, char *str, int base) {
    int i = 0;
    bool isNegative = false;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }
    while (num != 0) {
        int rem = num % base;
        str[i++] = (char) ((rem > 9) ? (rem - 10) + 'a' : rem + '0');
        num = num / base;
    }
    if (isNegative) str[i++] = '-';

    str[i] = '\0';
    inplace_reverse(str);
}

int int_char_length(int i) {
    if(i == 0) return 1;
    else return (int) floor(log10(abs(i))) + 1;
}
