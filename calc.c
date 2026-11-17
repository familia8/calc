#include "calc.h"

int calc_primer(int a, char znak, int b, long long *result)
{
    long long x = a;
    long long y = b;

    switch (znak) {
    case '+':
        *result = x + y;
        break;
    case '-':
        *result = x - y;
        break;
    case '*':
        *result = x * y;
        break;
    case '%':
        if (y == 0) {
            return 2;
        }
        *result = x % y;
        break;
    default:
        return 1;
    }
    return 0;
}
