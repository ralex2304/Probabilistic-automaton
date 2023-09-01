#ifndef CVECTOR_H_
#define CVECTOR_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Specifies vector
 */
struct Vector {
    size_t elem_size = 0; ///< one element size
    size_t capacity  = 2; ///< capacity of vector (used for memory allocation)
    size_t size      = 0; ///< actual number of elements in vector

    void* arr = nullptr;  ///< data array
};

/**
 * @brief Vector constructor
 *
 * @param vec
 * @param elem_size
 * @return true success
 * @return false failure
 */
bool vec_ctor(Vector* vec, size_t elem_size);

/**
 * @brief NodeVector destructor
 *
 * @param vec
 */
void vec_detor(Vector* vec);

/**
 * @brief NodeVector memory reallocation
 *
 * @param vec
 * @param new_size
 * @return true success
 * @return false failure
 */
bool vec_realloc(Vector* vec, size_t new_size);

/**
 * @brief Push to NodeVector
 *
 * @param vec
 * @param elem
 * @return true success
 * @return false failure
 */
bool vec_push(Vector* vec, void* elem);

/**
 * @brief Gets element from vector
 *
 * @param vec
 * @param i index
 * @return void*
 */
void* vec_get(Vector* vec, size_t i);

#endif // #ifndef NODEVECTOR_H_
