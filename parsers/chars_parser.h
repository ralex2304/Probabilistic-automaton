#ifndef CHARS_PARSER_H_
#define CHARS_PARSER_H_

#include <stdio.h>
#include <assert.h>

#include "../statuses.h"
#include "../cvector.h"
#include "../voiceover.h"
#include "../rand_wrapper.h"

/**
 * @brief Contains automaton level data
 */
struct CharNodesVector {
    unsigned long long all_cnt = 0; ///< sum of symbols in vec
    Vector vec = {};                ///< vector
};

/**
 * @brief Contains char information + next level CharNode
 */
struct CharNode {
    char ch;                ///< char
    unsigned long long cnt; ///< char count

    CharNodesVector children;         ///< next level CharNode
};

/**
 * @brief Parses text from file
 *
 * @param text
 * @param nodes zero level Nodes
 * @param Statuses
 */
Status::Statuses auto_parse(const char* text, CharNodesVector* nodes, const int max_level);

/**
 * @brief Finds ch Node in Nodes vector and increments it's cnt.
 * Is called recursively for levels from level to max_level
 *
 * @param nodes current level Nodes
 * @param ch char
 * @param level current level
 * @param max_level
 */
void auto_write_node(CharNodesVector* nodes, const char* ch, const unsigned int level, const unsigned int max_level);

/**
 * @brief Random generates symbol for levels from level to max_level. Writes to str.
 * Is called recursively
 *
 * @param nodes current level Nodes
 * @param str destination
 * @param level current level
 * @param max_level
 */
void auto_generate_rand_node(CharNodesVector* nodes, char* str, const unsigned int level, const unsigned int max_level);

/**
 * @brief Finds Node with char from str for all levels from level to max_level. Is called recursively.
 * Then calles auto_generate_rand_node for levels from max_level to rand_max_level
 *
 * @param nodes current level Nodes
 * @param str source
 * @param level current level
 * @param max_level max level and min level for auto_generate_rand_node()
 * @param rand_max_level max level for auto_generate_rand_node()
 * @return true success
 * @return false failure
 */
bool auto_get_node(CharNodesVector* nodes, char* str, const unsigned int level, const unsigned int max_level, const unsigned int rand_max_level);

/**
 * @brief Generates and prints text
 *
 * @param nodes zero level node
 * @param level max level
 * @param cnt word count
 * @param voice enables voiceover
 * @return Status::Statuses
 */
Status::Statuses auto_generate_text(CharNodesVector* nodes, const int level, ssize_t cnt, const bool voice);

/**
 * @brief Calls destructors for all vectors in nodes. Is called recursively
 *
 * @param nodes
 */
void auto_detor(CharNodesVector* nodes);

#endif // #ifndef CHARS_PARSER_H_
