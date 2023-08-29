#define  TX_USE_SPEAK
#include "TXLib.h"

#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "nodevector.h"
#include "automaton_parser.h"
#include "args_parser.h"

/**
 * @brief string buffer. Used for voiceover
 */
struct StrBuf {
    static const size_t capacity = 1024;

    char* str = nullptr;
    size_t size = 0;
};

/**
 * @brief Adds chars to buf. If char = \n or buf is full, calls txSpeak()
 *
 * @param buf
 * @param ch
 */
void speak_add(StrBuf* buf, char ch);

int main(int argc, char* argv[]) {

    txDisableAutoPause();

    int level = 8;
    ssize_t cnt = 1000;
    char* filename = nullptr;
    bool voice = false;

    Status::Statuses args_parse_res = args_parse(argc, argv, &level, &cnt, &filename, &voice);
    if (args_parse_res != Status::NORMAL_WORK)
        return Status::raise(args_parse_res);

    FILE* file = fopen(filename, "r");
    if (file == nullptr) {
        printf("Error opening text file\n");
        return Status::raise(Status::FILE_ERROR);
    }

    Nodes nodes = {};
    vec_ctor(&nodes.vec);

    auto_parse(file, &nodes, level);

    fclose(file);

    char* str = (char*)calloc(level + 2, sizeof(char));

    printf("---------- level %d ----------\n", level);

    auto_get_node(&nodes, str, 0, 0, level);

    StrBuf speak_buf = {};
    speak_buf.str = (char*)calloc(speak_buf.capacity, sizeof(char));

    int downgrade = 0;
    while (--cnt > 0) {
        for (ssize_t i = 0; i < level; i++)
            str[i] = str[i + 1];

        while (!auto_get_node(&nodes, str, 0, level, level) && --cnt > 0) {
            downgrade++;
            if (level < downgrade) downgrade = level;

            auto_get_node(&nodes, str, 0, level - downgrade, level);

            printf("%c", str[0]);
            if (voice)
                speak_add(&speak_buf, str[0]);

            for (ssize_t i = 0; i < level; i++)
                str[i] = str[i + 1];
        }
        printf("%c", str[0]);
        if (voice)
            speak_add(&speak_buf, str[0]);

        downgrade = 0;
    }
    printf("\n---------- stop ----------\n");

    free(str);
    auto_detor(&nodes);

    return Status::raise(Status::OK_EXIT);
}

void speak_add(StrBuf* buf, char ch) {
    buf->str[buf->size++] = ch;
    if (buf->size >= buf->capacity - 1 || buf->str[buf->size - 1] == '\n') {
        buf->str[buf->size] = '\0';
        txSpeak("<speak version='1.0' xmlns='http://www.w3.org/2001/10/synthesis' xml:lang='EN'>%s</speak>", buf->str);
        buf->size = 0;
    }
}
