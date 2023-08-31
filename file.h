#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <assert.h>

#include "statuses.h"

Status::Statuses file_open_and_read(const char* filename, char** buf);

/**
 * @brief Opens file in reading mode
 *
 * @param file
 * @param filename
 * @return true success
 * @return false failure
 */
bool file_open_r(FILE** file, const char* filename);

/**
 * @brief Gets file len
 *
 * @param file
 * @return long -1 in case of error
 */
long file_get_len(FILE* file);

/**
 * @brief Reads data from char to buffer. Buffer must be big enough
 *
 * @param file
 * @param buf
 * @param file_len
 * @return true
 * @return false
 */
bool file_read(FILE* file, char* buf, long file_len);

/**
 * @brief Closes file
 *
 * @param file
 * @return true success
 * @return false failure
 */
bool file_close(FILE* file);

#endif // #ifndef FILE_H_
