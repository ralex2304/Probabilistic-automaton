#ifndef AUTOMATON_PARSER_H_
#define AUTOMATON_PARSER_H_

#include <stdio.h>
#include <assert.h>
#include <random>
#include <string.h>

#include "../statuses.h"
#include "../cvector.h"
#include "../hash.h"
#include "../my_string.h"
#include "../voiceover.h"

/**
 * @brief Contains automaton level data
 */
struct Nodes {
    unsigned long long all_cnt = 0; ///< sum of symbols in vec
    Vector vec = {};                ///< vector
};

/**
 * @brief Contains char information + next level Node
 */
struct Node {
    char* token;            ///< word
    unsigned int hash;      ///< word hash

    unsigned long long cnt; ///< word count

    Nodes children;         ///< next level Node
};

/**
 * @brief Adds chars to buf. If char = \n or buf is full, calls txSpeak()
 *
 * @param buf
 * @param ch
 */
//void speak_add(String* buf, char ch);

/**
 * @brief Parses tokens to nodes
 *
 * @param tokens
 * @param nodes zero level Nodes
 * @param max_level
 * @return true success
 * @return false error
 */
bool auto_parse(Vector* tokens, Nodes* nodes, int max_level);

/**
 * @brief Finds ch Node in Nodes vector and increments it's cnt.
 * Is called recursively for levels from level to max_level
 *
 * @param nodes current level Nodes
 * @param tokens_arr source
 * @param level current level
 * @param max_level
 * @return true success
 * @return false error
 */
bool auto_write_node(Nodes* nodes, char** tokens_arr, const unsigned int level, const unsigned int max_level);

/**
 * @brief Random generates symbol for levels from level to max_level. Writes to str.
 * Is called recursively
 *
 * @param nodes current level Nodes
 * @param tokens_arr destination
 * @param level current level
 * @param max_level
 */
void auto_generate_rand_node(Nodes* nodes, char** tokens_arr, const unsigned int level, const unsigned int max_level);

/**
 * @brief Finds Node with char from str for all levels from level to max_level. Is called recursively.
 * Then calles auto_generate_rand_node for levels from max_level to rand_max_level
 *
 * @param nodes current level Nodes
 * @param tokens_arr source
 * @param level current level
 * @param max_level max level and min level for auto_generate_rand_node()
 * @param rand_max_level max level for auto_generate_rand_node()
 * @return true success
 * @return false failure
 */
bool auto_get_node(Nodes* nodes, char** tokens_arr, const unsigned int level, const unsigned int max_level, const unsigned int rand_max_level);

/**
 * @brief Calls destructors for all vectors in nodes. Is called recursively
 *
 * @param nodes
 */
void auto_detor(Nodes* nodes);

/**
 * @brief Generates and prints text
 *
 * @param nodes zero level node
 * @param level max level
 * @param cnt word count
 * @param voice enables voiceover
 * @return Status::Statuses
 */
Status::Statuses auto_generate_text(Nodes* nodes, const int level, ssize_t cnt, const bool voice);

/**
 * @brief Generates random long long number from min to max
 *
 * @param min
 * @param max
 * @return long long
 */
long long rand_normal_generate_ll(long long min, long long max);

#endif // #ifndef AUTOMATON_PARSER_H_
