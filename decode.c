#include <stdio.h>
#include "decode.h"

int decode_answers(const long long *answers, int count, int key, char *text)
{
    for (int i = 0; i < count; i++) {
        long long code = answers[i] - key;
        if (code < 0 || code > 127) {
            return i + 1;
        }
        text[i] = (char)code;
    }
    text[count] = '\0';
    return 0;
}

void print_text(const char *text, int count)
{
    printf("Результирующая строка: ");
    for (int i = 0; i < count; i++) {
        putchar(text[i]);
    }
    putchar('\n');
}
