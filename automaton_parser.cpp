#include "automaton_parser.h"


void auto_parse(FILE* file, Nodes* nodes, const int max_level) {
    char* bef = (char*)calloc((max_level + 2), sizeof(char));
    if (bef == nullptr) {
        printf("auto_parse(): Memory alloc error\n");
        return;
    }

    int ch = '\0';
    int begin = 0;
    while ((ch = getc(file)) != EOF) {
        //if (!isalpha(ch) && !isdigit(ch) && !isspace(ch)) continue;

        for (ssize_t i = 0; i < max_level; i++)
            bef[i] = bef[i + 1];

        bef[max_level] = (char)ch;

        if (begin < max_level) {
            begin++;
            continue;
        }

        auto_write_node(nodes, bef, 0, max_level);

    }
    free(bef);
}

void auto_write_node(Nodes* nodes, const char* str, const unsigned int level, const unsigned int max_level) {
    nodes->all_cnt++;

    size_t i = 0;
    for (i = 0; i < nodes->vec.size; i++) {
        if (nodes->vec.arr[i].ch == str[level])
            break;
    }

    if (i == nodes->vec.size) {
        Node new_node = {};
        new_node.ch = str[level];
        new_node.cnt = 1;
        vec_ctor(&new_node.children.vec);

        if(!vec_push(&nodes->vec, new_node)) {
            printf("auto_write_node(): Memory alloc error\n");
            return;
        }
    } else {
        nodes->vec.arr[i].cnt++;
    }

    if (level == max_level)
        return;

    auto_write_node(&nodes->vec.arr[i].children, str, level + 1, max_level);
}

void auto_generate_rand_node(Nodes* nodes, char* str, const unsigned int level, const unsigned int max_level) {
    static std::random_device rd;

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<unsigned long long> rand_normal {0, nodes->all_cnt};

    long long r = (long long)rand_normal(gen);
    for (size_t i = 0; i < nodes->vec.size; i++) {
        r -= nodes->vec.arr[i].cnt;
        if (r < 0) {
            str[level] = nodes->vec.arr[i].ch;

            if (level < max_level)
                auto_generate_rand_node(&nodes->vec.arr[i].children, str, level + 1, max_level);
            break;
        }
    }
}

bool auto_get_node(Nodes* nodes, char* str, const unsigned int level, const unsigned int max_level, const unsigned int rand_max_level) {

    if (level == max_level) {
        auto_generate_rand_node(nodes, str, max_level, rand_max_level);
        return true;
    }

    size_t i = 0;
    for (i = 0; i < nodes->vec.size; i++) {
        if (nodes->vec.arr[i].ch == str[level])
            break;
    }

    if (i == nodes->vec.size) {
        return false;
    }
    return auto_get_node(&nodes->vec.arr[i].children, str, level + 1, max_level, rand_max_level);
}

void auto_detor(Nodes* nodes) {
    for (size_t i = 0; i < nodes->vec.size; i++) {
        auto_detor(&nodes->vec.arr[i].children);
    }
    vec_detor(&nodes->vec);
}
