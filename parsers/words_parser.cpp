#include "words_parser.h"

bool auto_parse(Vector* tokens, Nodes* nodes, int max_level) {
    assert(tokens);
    assert(nodes);

    for (size_t i = 0; i < tokens->size - max_level; i++) {
        if (!auto_write_node(nodes, (char**)(tokens->arr) + i, 0, max_level))
            return false;
    }
    return true;
}

bool auto_write_node(Nodes* nodes, char** tokens_arr, const unsigned int level, const unsigned int max_level) {
    assert(nodes);
    assert(tokens_arr);

    nodes->all_cnt++;

    size_t i = 0;
    size_t token_len = strlen(tokens_arr[level]);

    for (i = 0; i < nodes->vec.size; i++) {
        size_t node_token_len = strlen(((Node*)vec_get(&nodes->vec, i))->token);

        if (node_token_len == token_len &&
            ((Node*)vec_get(&nodes->vec,i))->hash == MurmurHash2A(tokens_arr[level], (int)token_len) &&
            strncmp(((Node*)vec_get(&nodes->vec, i))->token, tokens_arr[level], node_token_len))
                break;
    }

    if (i == nodes->vec.size) {
        Node new_node = {};
        new_node.token = tokens_arr[level];
        new_node.hash = MurmurHash2A(new_node.token, (int)token_len);
        new_node.cnt = 1;
        if (!vec_ctor(&new_node.children.vec, sizeof(Node))) {
            printf("auto_write_node(): Memory alloc error\n");
            return false;
        }

        if(!vec_push(&nodes->vec, &new_node)) {
            printf("auto_write_node(): Memory alloc error\n");
            return false;
        }
    } else {
        ((Node*)vec_get(&nodes->vec, i))->cnt++;
    }

    if (level == max_level)
        return true;

    return auto_write_node(&((Node*)vec_get(&nodes->vec, i))->children, tokens_arr, level + 1, max_level);
}

void auto_generate_rand_node(Nodes* nodes, char** tokens_arr, const unsigned int level, const unsigned int max_level) {
    assert(nodes);
    assert(tokens_arr);

    long long r = rand_normal_generate_ll(0, (long long)nodes->all_cnt);

    for (size_t i = 0; i < nodes->vec.size; i++) {
        r -= ((Node*)vec_get(&nodes->vec, i))->cnt;
        if (r <= 0) {
            tokens_arr[level] = ((Node*)vec_get(&nodes->vec, i))->token;

            if (level < max_level)
                auto_generate_rand_node(&((Node*)vec_get(&nodes->vec, i))->children, tokens_arr, level + 1, max_level);
            return;
        }
    }
    assert(0 && "Rand node generate error");
}

bool auto_get_node(Nodes* nodes, char** tokens_arr, const unsigned int level, const unsigned int max_level, const unsigned int rand_max_level) {
    assert(nodes);
    assert(tokens_arr);

    if (level == max_level) {
        auto_generate_rand_node(nodes, tokens_arr, max_level, rand_max_level);
        return true;
    }

    size_t i = 0;
    char* token = tokens_arr[level];
    size_t token_len = strlen(token);

    for (i = 0; i < nodes->vec.size; i++) {
        size_t node_token_len = strlen(((Node*)vec_get(&nodes->vec, i))->token);

        if (node_token_len == token_len &&
            ((Node*)vec_get(&nodes->vec, i))->hash == MurmurHash2A(token, (int)token_len) &&
            strncmp(((Node*)vec_get(&nodes->vec, i))->token, token, node_token_len))
                break;
    }

    if (i == nodes->vec.size) {
        return false;
    }
    return auto_get_node(&((Node*)vec_get(&nodes->vec, i))->children, tokens_arr, level + 1, max_level, rand_max_level);
}

Status::Statuses auto_generate_text(Nodes* nodes, const int level, ssize_t cnt, const bool voice) {
    assert(nodes);

    char** prev_tokens = (char**)calloc((level + 1), sizeof(char*));
    if (prev_tokens == nullptr) {
        printf("Memory alloc error\n");
        return Status::MEMORY_EXCEED;
    }

    printf("---------- level %d ----------\n", level);

    auto_get_node(nodes, prev_tokens, 0, 0, level);

    int downgrade = 0;
    while (--cnt > 0) {
        for (ssize_t i = 0; i < level; i++)
            prev_tokens[i] = prev_tokens[i + 1];

        while (!auto_get_node(nodes, prev_tokens, 0, level, level) && --cnt > 0) {
            downgrade++;
            if (level < downgrade) downgrade = level;

            auto_get_node(nodes, prev_tokens, 0, level - downgrade, level);

            printf("%s ", prev_tokens[0]);
            if (voice)
                speak_add_token(prev_tokens[0]);

            for (ssize_t i = 0; i < level; i++)
                prev_tokens[i] = prev_tokens[i + 1];
        }
        printf("%s ", prev_tokens[0]);
        if (voice)
            speak_add_token(prev_tokens[0]);

        downgrade = 0;
    }
    speak_add_token("", true);
    printf("\n---------- stop ----------\n");

    free(prev_tokens);

    return Status::NORMAL_WORK;
}

void auto_detor(Nodes* nodes) {
    assert(nodes);

    for (size_t i = 0; i < nodes->vec.size; i++) {
        auto_detor(&((Node*)vec_get(&nodes->vec, i))->children);
    }
    vec_detor(&nodes->vec);
}

long long rand_normal_generate_ll(long long min, long long max) {
    static std::random_device rd;

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<long long> rand_normal {min, max};

    return rand_normal(gen);
}

