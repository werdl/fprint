#ifndef _STDINT_H
#include <stdint.h>
#endif

char * d2c(int val){
    int base=10;
    static char buf[65] = {0}; // static for memory boost
    int i = 30;
    for(; val && i; --i, val /= base)
        buf[i] = "0123456789"[val % base];
    return &buf[i+1];
}

char * f2s(double f) {
    char *str = malloc(100 * sizeof(char));

    char pos;
    char len;
    char *curr;
    int value;

    int size = 50;

    pos = 0;

    value = (int)f; // truncate the floating point number
    char *intPart = d2c(value); // this is kinda dangerous depending on the length of str
    strcpy(str, intPart); // copy integer part to str

    if (f < 0) // handle negative numbers
    {
        f *= -1;
        value *= -1;
    }

    len = strlen(str); // find out how big the integer part was
    pos = len;          // position the pointer to the end of the integer part
    str[pos++] = '.';   // add decimal point to string

    while (pos < (size + len + 1)) // process remaining digits
    {
        f = f - (double)value; // hack off the whole part of the number
        f *= 10;               // move next digit over
        value = (int)f;         // get next digit
        curr = d2c(value);      // convert digit to string
        str[pos++] = *curr;     // add digit to result string and increment pointer
    }
    return str;
}

char * c2c(char c) {
    size_t size = (unsigned int)(c * 10);
    char * buf = malloc(size);
    *buf=c;
    return (buf);
}