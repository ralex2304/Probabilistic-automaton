#define TX_COMPILED
#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "cvector.h"
#include "args_parser.h"
#include "file.h"

#include "parsers/words_parser.h"

int main(int argc, char* argv[]) {
    txSetLocale ();
    txDisableAutoPause();

    /// Console args parse
    int level = 4;
    ssize_t cnt = 1000;
    const char* filename = nullptr;
    bool voice = false;

    Status::Statuses args_parse_res = args_parse(argc, argv, &level, &cnt, &filename, &voice);
    if (args_parse_res != Status::NORMAL_WORK)
        return Status::raise(args_parse_res);

    if (filename == nullptr)
        filename = "texts/text.txt";
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
    while ((new_token = my_strtok(nullptr)) != nullptr)
        vec_push(&tokens, &new_token);

    if (!auto_parse(&tokens, &nodes, level))
        return Status::raise(Status::MEMORY_EXCEED);
    /// Text parsing end

    res = auto_generate_text(&nodes, level, cnt, voice);
    if (res != Status::NORMAL_WORK)
        return Status::raise(res);

    auto_detor(&nodes);
    free(text);

    return Status::raise(Status::OK_EXIT);
}
