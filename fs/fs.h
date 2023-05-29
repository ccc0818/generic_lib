#pragma once

#include <stdio.h>

typedef struct {
    void (*delete)(const char* p);
    const char* (*read_line)(const char* path, unsigned int line);
    int (*read_line_by_line)(const char* path, void (*callback)(const char* line, unsigned long ln));
    const char* (*read_all)(const char* file);
    int (*trunc)(const char* file);
    int (*remove)(const char* file);
    int (*write)(const char* file, const char* data);
    int (*append)(const char* file, const char* data);
    int (*copy)(const char* file_src, const char* file_dest);
} Fs;

extern Fs fs;