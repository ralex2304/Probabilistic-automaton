#include "cvector.h"

bool vec_ctor(Vector* vec, size_t elem_size) {
    assert(vec);

    vec->elem_size = elem_size;
    vec->arr = calloc(vec->capacity, vec->elem_size);
    if (vec->arr == nullptr)
        return false;
    return true;
}

void vec_detor(Vector* vec) {
    assert(vec);

    free(vec->arr);
    vec->arr = nullptr;
    vec->capacity = 0;
}

bool vec_realloc(Vector* vec, size_t new_size) {
    assert(vec);

    void* ptr = vec->arr;

    vec->arr = (void*)realloc(vec->arr, new_size * vec->elem_size);
    if (vec->arr == nullptr) {
        free(ptr);
        return false;
    }

    vec->capacity = new_size;
    return true;
}

bool vec_push(Vector* vec, void* elem) {
    assert(vec);
    assert(elem);

    if (vec->size >= vec->capacity &&
        !vec_realloc(vec, vec->capacity * 2)) {
        return false;
    }

    memcpy((char*)vec->arr + vec->size * vec->elem_size, elem, vec->elem_size);
    vec->size++;

    return true;
}

void* vec_get(Vector* vec, size_t i) {
    assert(vec);
    assert(i < vec->size);

    return (char*)vec->arr + i * vec->elem_size;
}
