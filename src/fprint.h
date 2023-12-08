#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#if defined(__linux__)
#include "../arch/linux.h"
#else
#error "Unknown arch"
#endif

#include "conversions.h"


#define TYPE_ID(var) _Generic((var), \
    int: "int", \
    unsigned int: "int", \
    long: "int", \
    unsigned long: "int", \
    long long: "int", \
    unsigned long long: "int", \
    float: "float", \
    double: "float", \
    long double: "float", \
    char: "char", \
    signed char: "char", \
    unsigned char: "char", \
    short: "int", \
    unsigned short: "int", \
    float _Complex: "_Complex", \
    double _Complex: "_Complex", \
    long double _Complex: "_Complex", \
    char*: "string", \
    default: "int" \
)

int type(void * val) {
    char * ident = TYPE_ID(val); 
    if (!strcmp("int", ident)) return 0; 
    if (!strcmp("float", ident)) return 1; 
    if (!strcmp("_Complex", ident)) return 2; 
    if (!strcmp("string", ident)) return 3; 
    if (!strcmp("char", ident)) return 4; 
}

void append(char ** dest, const char * src) {
    *dest = realloc(*dest, strlen(*dest) + strlen(src) + 1);
    strcat(*dest, src);
}


void popCharsNeg(char *str, int n) {
    int len = strlen(str);
    if (n >= 0 && n <= len) {
        str[len - n] = '\0';
    }
}

void appendChar(char * s, char c) {
    s = realloc(s, (strlen(s) * sizeof(char)) + 2);
    int len = strlen(s);
    strcpy(s, s);
    s[len] = c;
    s[len + 1] = 0;
}

char * fmt(char * format, ...) {
    va_list vals;
    va_start(vals, format);

    char * out = malloc(1);
    strcpy(out, "");

    const char exclam = '!';

    char * sep = malloc(511);
    strcpy(sep, "");

    while (*format) {
        if (*format=='$') {
            format++;
            switch (*format) {
                case 'f':
                    append(&out, f2s(va_arg(vals, double)));
                    break;
                case 'i':
                    append(&out, d2c(va_arg(vals, long long int)));
                    break;
                case 's':
                    append(&out, va_arg(vals, char *));
                    break;
                case 'c':
                    append(&out, c2c(va_arg(vals, int)));
                    /*
                    avoid this warning:
                        note: (so you should pass ‘int’ not ‘char’ to ‘va_arg’)
                        note: if this code is reached, the program will abort
                    */
                    break;
                default:
                    appendChar(out, *format);
            }
            append(&out, sep);
        } else if (*format=='!') {
            format++;
            switch (*format) {
                case '!':
                    append(&out, &exclam);
                    break;
                default:
                    {
                        while (*format != '!') {

                            sep[strlen(sep)]=*format;
                            sep[strlen(sep)]='\0';
                            
                            format++;
                        }
                    }
                    
            }
        } else {
            appendChar(out, *format);
        }
        format++;
    }
    
    popCharsNeg(out, strlen(sep)); // remove last splitter

    va_end(vals);

    return out;
}
