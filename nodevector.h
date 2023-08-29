#ifndef NODEVECTOR_H_
#define NODEVECTOR_H_

#include <stdlib.h>

struct Node; // forward declaration

/**
 * @brief Specifies vector
 */
struct NodeVector {
    size_t capacity = 2;    ///< capacity of vector (used for memory allocation)
    size_t size = 0;        ///< actual number of elements in vector

    Node* arr = nullptr;    ///< data array
};

/**
 * @brief Contains automaton level data
 */
struct Nodes {
    unsigned long long all_cnt = 0; ///< sum of symbols in vec
    NodeVector vec = {};            ///< vector
};

/**
 * @brief Contains char information + next level Node
 */
struct Node {
    char ch;                ///< char
    unsigned long long cnt; ///< char count

    Nodes children;         ///< next level Node
};

/**
 * @brief NodeVector constructor
 *
 * @param vec
 * @return true success
 * @return false failure
 */
bool vec_ctor(NodeVector* vec);

/**
 * @brief NodeVector destructor
 *
 * @param vec
 */
void vec_detor(NodeVector* vec);

/**
 * @brief NodeVector memory reallocation
 *
 * @param vec
 * @param new_size
 * @return true success
 * @return false failure
 */
bool vec_realloc(NodeVector* vec, size_t new_size);

/**
 * @brief Push to NodeVector
 *
 * @param vec
 * @param elem
 * @return true success
 * @return false failure
 */
bool vec_push(NodeVector* vec, Node elem);

#endif // #ifndef NODEVECTOR_H_
