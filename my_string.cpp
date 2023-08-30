#include "my_string.h"

char* my_strtok(char* input) {
    static char* str = nullptr;

    if (input != nullptr)
        str = input;

    if (str == nullptr)
        return nullptr;

    char* ret = str;

    while (!isspace(*str)) {
        str++;
    }

    while (isspace(*str) && *str) {
        *str = '\0';
        str++;
    }

    if (*str == '\0')
        str = nullptr;

    return ret;
}

