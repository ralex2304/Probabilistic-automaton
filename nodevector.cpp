#include "nodevector.h"

bool vec_ctor(NodeVector* vec) {
    vec->arr = (Node*)calloc(vec->capacity, sizeof(Node));
    if (vec->arr == nullptr)
        return false;
    return true;
}

void vec_detor(NodeVector* vec) {
    free(vec->arr);
    vec->arr = nullptr;
    vec->capacity = 0;
}

bool vec_realloc(NodeVector* vec, size_t new_size) {
    Node* ptr = vec->arr;

    vec->arr = (Node*)realloc(vec->arr, new_size * sizeof(Node));
    if (vec->arr == nullptr) {
        free(ptr);
        return false;
    }

    vec->capacity = new_size;
    return true;
}

bool vec_push(NodeVector* vec, Node elem) {
    if (vec->size >= vec->capacity &&
        !vec_realloc(vec, vec->capacity * 2)) {
        return false;
    }

    vec->arr[vec->size++] = elem;

    return true;
}
