#include "my_string.h"

char* my_strtok(const char* input) {
    static char* str = nullptr;

    if (input != nullptr)
        str = const_cast<char*>(input);

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

