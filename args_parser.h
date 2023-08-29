#ifndef ARGS_PARSER_H_
#define ARGS_PARSER_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "automaton_parser.h"

/**
 * @brief Specifies int main() returns
 */
enum class ArgsMode {
    ERR    = -1,    ///< Error
    EXIT     =  0,    ///< Continue reading args, but then normal exit
    CONTINUE =  1,    ///< Continue reading args
};

struct Argument; // forward declaration

typedef ArgsMode (*args_func)(const Argument args_dict[], const int args_dict_len,
         int* arg_i, const int argc, char* argv[],
         int* auto_level, ssize_t* output_cnt, char** filename, bool* voice);

/**
 * @brief Specifies console argument parametres: name, function and description
 */
struct Argument {
    const char* arg;           ///< Argument name
    args_func func;            ///< Function
    const char* description;   ///< Description
};


/**
 * @brief Parses console arguments
 *
 * @param argc
 * @param argv
 * @param auto_level
 * @param output_cnt
 * @param filename
 * @param voice
 * @return Status::Statuses
 */
Status::Statuses args_parse(int argc, char* argv[],
                            int* auto_level, ssize_t* output_cnt, char** filename, bool* voice);

/**
 * @brief Prints help
 *
 * @param args_dict
 * @param args_dict_len
 * @param arg_i
 * @param argc
 * @param argv
 * @param auto_level
 * @param output_cnt
 * @param filename
 * @param voice
 * @return ArgsMode
 */
ArgsMode print_help(const Argument args_dict[], const int args_dict_len,
                    int* arg_i, const int argc, char* argv[],
                    int* auto_level, ssize_t* output_cnt, char** filename, bool* voice);

/**
 * @brief Sets auto max level
 *
 * @param args_dict
 * @param args_dict_len
 * @param arg_i
 * @param argc
 * @param argv
 * @param auto_level
 * @param output_cnt
 * @param filename
 * @param voice
 * @return ArgsMode
 */
ArgsMode set_level(const Argument args_dict[], const int args_dict_len,
                   int* arg_i, const int argc, char* argv[],
                   int* auto_level, ssize_t* output_cnt, char** filename, bool* voice);

/**
 * @brief Sets output symb num
 *
 * @param args_dict
 * @param args_dict_len
 * @param arg_i
 * @param argc
 * @param argv
 * @param auto_level
 * @param output_cnt
 * @param filename
 * @param voice
 * @return ArgsMode
 */
ArgsMode set_symb_num(const Argument args_dict[], const int args_dict_len,
                      int* arg_i, const int argc, char* argv[],
                      int* auto_level, ssize_t* output_cnt, char** filename, bool* voice);

/**
 * @brief Sets filename
 *
 * @param args_dict
 * @param args_dict_len
 * @param arg_i
 * @param argc
 * @param argv
 * @param auto_level
 * @param output_cnt
 * @param filename
 * @param voice
 * @return ArgsMode
 */
ArgsMode set_filename(const Argument args_dict[], const int args_dict_len,
                      int* arg_i, const int argc, char* argv[],
                      int* auto_level, ssize_t* output_cnt, char** filename, bool* voice);

/**
 * @brief Enables voiceover
 *
 * @param args_dict
 * @param args_dict_len
 * @param arg_i
 * @param argc
 * @param argv
 * @param auto_level
 * @param output_cnt
 * @param filename
 * @param voice
 * @return ArgsMode
 */
ArgsMode enable_voice(const Argument args_dict[], const int args_dict_len,
                      int* arg_i, const int argc, char* argv[],
                      int* auto_level, ssize_t* output_cnt, char** filename, bool* voice);
#endif // #ifndef ARGS_PARSER_H_
