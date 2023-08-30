#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <assert.h>

#include "automaton_parser.h"


Status::Statuses file_open_and_read(const char* filename, char** buf);

bool file_open_r(FILE** file, const char* filename);

long file_get_len(FILE* file);

bool file_read(FILE* file, char* buf, long file_len);

bool file_close(FILE* file);

#endif // #ifndef FILE_H_
