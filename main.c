#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
#include "decode.h"

static int read_int(const char *text, int *value)
{
    char *end;
    errno = 0;
    long number = strtol(text, &end, 10);
    if (end == text || *end != '\0' || errno == ERANGE ||
        number < INT_MIN || number > INT_MAX) {
        return 1;
    }
    *value = (int)number;
    return 0;
}

static int calculate_all(char *argv[], int count, long long *answers)
{
    for (int i = 0; i < count; i++) {
        int pos = 1 + 3 * i;
        int left, right;
        const char *sign = argv[pos + 1];

        if (read_int(argv[pos], &left) || read_int(argv[pos + 2], &right)) {
            fprintf(stderr, "Ошибка в выражении №%d: операнды должны быть целыми числами.\n", i + 1);
            return 1;
        }
        int status = 1;
        if (strlen(sign) == 1) {
            status = calc_primer(left, sign[0], right, &answers[i]);
        }
        if (status == 1) {
            fprintf(stderr, "Ошибка в выражении №%d: неизвестный оператор «%s».\n", i + 1, sign);
            return 1;
        }
        if (status == 2) {
            fprintf(stderr, "Ошибка в выражении №%d: остаток от деления на ноль.\n", i + 1);
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 6 || (argc - 3) % 3 != 0 || strcmp(argv[argc - 2], "-k") != 0) {
        fprintf(stderr, "Формат: cmdcalc A op B [A op B ...] -k ключ\n");
        return 1;
    }
    int key;
    if (read_int(argv[argc - 1], &key)) {
        fprintf(stderr, "Ошибка: после -k требуется целое число.\n");
        return 1;
    }

    int count = (argc - 3) / 3;
    long long *answers = calloc(count, sizeof(*answers));
    char *text = malloc(count + 1);
    int status = 1;

    if (answers == NULL || text == NULL) {
        fprintf(stderr, "Ошибка: недостаточно памяти.\n");
    } else if (calculate_all(argv, count, answers) == 0) {
        for (int i = 0; i < count; i++) {
            printf("Ответ №%d: %lld\n", i + 1, answers[i]);
        }
        int bad_answer = decode_answers(answers, count, key, text);
        if (bad_answer == 0) {
            print_text(text, count);
            status = 0;
        } else {
            fprintf(stderr, "Ошибка: код %lld для ответа №%d вне диапазона ASCII (0..127).\n",
                    answers[bad_answer - 1] - key, bad_answer);
        }
    }
    free(text);
    free(answers);
    return status;
}
