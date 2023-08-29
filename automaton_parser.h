#ifndef AUTOMATON_PARSER_H_
#define AUTOMATON_PARSER_H_

#include <stdio.h>
#include <random>

#include "nodevector.h"

/**
 * @brief Parses text from file
 *
 * @param file
 * @param nodes zero level Nodes
 * @param max_level
 */
void auto_parse(FILE* file, Nodes* nodes, int max_level);

/**
 * @brief Finds ch Node in Nodes vector and increments it's cnt.
 * Is called recursively for levels from level to max_level
 *
 * @param nodes current level Nodes
 * @param ch char
 * @param level current level
 * @param max_level
 */
void auto_write_node(Nodes* nodes, const char* ch, const unsigned int level, const unsigned int max_level);

/**
 * @brief Random generates symbol for levels from level to max_level. Writes to str.
 * Is called recursively
 *
 * @param nodes current level Nodes
 * @param str destination
 * @param level current level
 * @param max_level
 */
void auto_generate_rand_node(Nodes* nodes, char* str, const unsigned int level, const unsigned int max_level);

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
bool auto_get_node(Nodes* nodes, char* str, const unsigned int level, const unsigned int max_level, const unsigned int rand_max_level);

/**
 * @brief Calls destructors for all vectors in nodes. Is called recursively
 *
 * @param nodes
 */
void auto_detor(Nodes* nodes);

#endif // #ifndef AUTOMATON_PARSER_H_
