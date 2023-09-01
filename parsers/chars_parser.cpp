#include "chars_parser.h"

Status::Statuses auto_parse(const char* text, CharNodesVector* nodes, const int max_level) {
    assert(text);
    assert(nodes);

    char* bef = (char*)calloc((max_level + 1), sizeof(char));
    if (bef == nullptr) {
        printf("auto_parse(): Memory alloc error\n");
        return Status::MEMORY_EXCEED;
    }

    int ch = '\0';
    int begin = 0;
    while ((ch = *(text++)) != '\0') {

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

    return Status::NORMAL_WORK;
}

void auto_write_node(CharNodesVector* nodes, const char* str, const unsigned int level, const unsigned int max_level) {
    assert(nodes);
    assert(str);

    nodes->all_cnt++;

    size_t i = 0;
    for (i = 0; i < nodes->vec.size; i++) {
        if (((CharNode*)vec_get(&nodes->vec, i))->ch == str[level])
            break;
    }

    if (i == nodes->vec.size) {
        CharNode new_node = {};
        new_node.ch = str[level];
        new_node.cnt = 1;
        vec_ctor(&new_node.children.vec, sizeof(CharNode));

        if(!vec_push(&nodes->vec, &new_node)) {
            printf("auto_write_node(): Memory alloc error\n");
            return;
        }
    } else {
        ((CharNode*)vec_get(&nodes->vec, i))->cnt++;
    }

    if (level == max_level)
        return;

    auto_write_node(&((CharNode*)vec_get(&nodes->vec, i))->children, str, level + 1, max_level);
}

void auto_generate_rand_node(CharNodesVector* nodes, char* str, const unsigned int level, const unsigned int max_level) {
    assert(nodes);
    assert(str);

    long long r = rand_normal_generate_ll(0, (long long)nodes->all_cnt);

    for (size_t i = 0; i < nodes->vec.size; i++) {
        r -= ((CharNode*)vec_get(&nodes->vec, i))->cnt;
        if (r < 0) {
            str[level] = ((CharNode*)vec_get(&nodes->vec, i))->ch;

            if (level < max_level)
                auto_generate_rand_node(&((CharNode*)vec_get(&nodes->vec, i))->children, str, level + 1, max_level);
            break;
        }
    }
}

bool auto_get_node(CharNodesVector* nodes, char* str, const unsigned int level, const unsigned int max_level, const unsigned int rand_max_level) {
    assert(nodes);
    assert(str);

    if (level == max_level) {
        auto_generate_rand_node(nodes, str, max_level, rand_max_level);
        return true;
    }

    size_t i = 0;
    for (i = 0; i < nodes->vec.size; i++) {
        if (((CharNode*)vec_get(&nodes->vec, i))->ch == str[level])
            break;
    }

    if (i == nodes->vec.size) {
        return false;
    }
    return auto_get_node(&((CharNode*)vec_get(&nodes->vec, i))->children, str, level + 1, max_level, rand_max_level);
}

Status::Statuses auto_generate_text(CharNodesVector* nodes, const int level, ssize_t cnt, const bool voice) {
    assert(nodes);

    char* prev_chars = (char*)calloc(level + 2, sizeof(char));

    printf("---------- level %d ----------\n", level);

    auto_get_node(nodes, prev_chars, 0, 0, level);


    int downgrade = 0;
    while (--cnt > 0) {
        for (ssize_t i = 0; i < level; i++)
            prev_chars[i] = prev_chars[i + 1];

        while (!auto_get_node(nodes, prev_chars, 0, level, level) && --cnt > 0) {
            downgrade++;
            if (level < downgrade) downgrade = level;

            auto_get_node(nodes, prev_chars, 0, level - downgrade, level);

            printf("%c", prev_chars[0]);
            if (voice)
                speak_add_char(prev_chars[0]);

            for (ssize_t i = 0; i < level; i++)
                prev_chars[i] = prev_chars[i + 1];
        }
        printf("%c", prev_chars[0]);
        if (voice)
            speak_add_char(prev_chars[0]);

        downgrade = 0;
    }
    printf("\n---------- stop ----------\n");

    free(prev_chars);

    return Status::NORMAL_WORK;
}

void auto_detor(CharNodesVector* nodes) {
    assert(nodes);

    for (size_t i = 0; i < nodes->vec.size; i++) {
        auto_detor(&((CharNode*)vec_get(&nodes->vec, i))->children);
    }

    vec_detor(&nodes->vec);
}
