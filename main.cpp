//#define  TX_USE_SPEAK
#include <TXLib.h>

#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "cvector.h"
#include "automaton_parser.h"
#include "args_parser.h"
#include "file.h"

int main(int argc, char* argv[]) {
    txSetLocale ();
    //txDisableAutoPause();

    /// Console args parse
    int level = 4;
    ssize_t cnt = 1000;
    const char* filename = nullptr;
    bool voice = false;

    Status::Statuses args_parse_res = args_parse(argc, argv, &level, &cnt, &filename, &voice);
    if (args_parse_res != Status::NORMAL_WORK)
        return Status::raise(args_parse_res);

    if (filename == nullptr)
        filename = "text.txt";
    /// Console args parse end

    /// File reading
    char* text = nullptr;
    Status::Statuses res = file_open_and_read(filename, &text);
    if (res != Status::NORMAL_WORK)
        return Status::raise(res);

    assert(text);
    /// File reading end

    /// Text parsing
    Nodes nodes = {};
    vec_ctor(&nodes.vec, sizeof(Node));

    Vector tokens = {};
    vec_ctor(&tokens, sizeof(char*));

    char* new_token = my_strtok(text);
    while ((new_token = my_strtok(nullptr)) != nullptr) {
        vec_push(&tokens, &new_token);
        //printf("%s\n", *((char**)vec_get(&tokens, tokens.size - 1)));
    }

    if (!auto_parse(&tokens, &nodes, level))
        return Status::raise(Status::MEMORY_EXCEED);
    /// Text parsing end


    char** prev_tokens = (char**)calloc((level + 1), sizeof(char*));
    if (prev_tokens == nullptr) {
        printf("Memory alloc error\n");
        return Status::raise(Status::MEMORY_EXCEED);
    }

    printf("---------- level %d ----------\n", level);

    auto_get_node(&nodes, prev_tokens, 0, 0, level);

    /// StrBuf speak_buf = {};
    /// speak_buf.str = (char*)calloc(speak_buf.capacity, sizeof(char));

    int downgrade = 0;
    while (--cnt > 0) {
        for (ssize_t i = 0; i < level; i++)
            prev_tokens[i] = prev_tokens[i + 1];

        while (!auto_get_node(&nodes, prev_tokens, 0, level, level) && --cnt > 0) {
            downgrade++;
            /// printf("\n-------\n");
            if (level < downgrade) downgrade = level;

            auto_get_node(&nodes, prev_tokens, 0, level - downgrade, level);

            printf("%s ", prev_tokens[0]);
            /*if (voice)
                speak_add(&speak_buf, str[0]);*/

            for (ssize_t i = 0; i < level; i++)
                prev_tokens[i] = prev_tokens[i + 1];
        }
        printf("%s ", prev_tokens[0]);
        /*if (voice)
            speak_add(&speak_buf, str[0]);*/

        downgrade = 0;
    }
    printf("\n---------- stop ----------\n");


    free(prev_tokens);
    //free(speak_buf.str);
    auto_detor(&nodes);
    free(text);

    return Status::raise(Status::OK_EXIT);
}

