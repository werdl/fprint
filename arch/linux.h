#ifndef _STDIO_H
#include <stdio.h>
#endif

int local_putchar(char c) {
    putchar(c);
}

char * trim_zeroes(char * str) {
    int len = strlen(str); 
    for (int i = 0; i < len - 1; ++i) { 
        if (str[i] == '0' && str[i + 1] == '0') { 
            memmove(&str[i], &str[i + 1], len - i); 
            --len; 
            --i; 
        } 
    } 
}

// char * f2c(float f) {
//     size_t size = (unsigned int)(f * 10);
//     char * buf = malloc(size);
//     snprintf(buf, size, "%f", f);
//     return (buf);
// }

// char * d2c(int d) {
//     size_t size = (unsigned int)(d * 10);
//     char * buf = malloc(size);
//     snprintf(buf, size, "%d", d);

//     return (buf);
// }

