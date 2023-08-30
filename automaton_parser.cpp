#include "automaton_parser.h"

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
    static std::random_device rd;

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<unsigned long long> rand_normal {0, nodes->all_cnt};

    long long r = (long long)rand_normal(gen);
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

void auto_detor(Nodes* nodes) {
    for (size_t i = 0; i < nodes->vec.size; i++) {
        auto_detor(&((Node*)vec_get(&nodes->vec, i))->children);
    }
    vec_detor(&nodes->vec);
}

Status::Statuses Status::raise(const Statuses status) {
    switch (status) {
        case NORMAL_WORK:
            assert(0 && "Status::raise(): NORMAL_WORK mustn't be raised");
            break;
        case ARGS_ERROR:
            printf("Exiting. Args error\n");
            break;
        case FILE_ERROR:
            printf("Exiting. File error\n");
            break;
        case MEMORY_EXCEED:
            printf("Exiting. Not enough memory\n");
        case OK_EXIT:
        case NO_ERR:
            break;
        default:
            assert(0 && "Error::raise(): wrong error");
            break;
    };
    return status;
}

/*void speak_add(Vector* buf, char* add_token) {
    buf->str[buf->size++] = ch;
    if (buf->size >= buf->capacity - 1 || buf->str[buf->size - 1] == '\n') {
        buf->str[buf->size] = '\0';
        //txSpeak("<speak version='1.0' xmlns='http://www.w3.org/2001/10/synthesis' xml:lang='EN'>%s</speak>", buf->str);
        buf->size = 0;
    }
}*/
