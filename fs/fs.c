#include <string.h>
#include <stdlib.h>
#include "fs.h"

#define BUF_SIZE 1024

static void _delete(const char* p) {
    free((void*)p);
    p = NULL;
}

// read
static const char* _read_line(const char* file, unsigned int line) {
    if (line <= 0) {
        line = 1;
    }

    FILE* fp = fopen(file, "r");
    if (!fp) {
        return NULL;
    }

    char buf[BUF_SIZE] = { 0 };
    for (int i = 0; i < line; ++i) {
        fgets(buf, sizeof(buf), fp);
    }
    fclose(fp);
    return strdup(buf);
}

static int _read_line_by_line(const char* file, void (*callback)(const char* line, unsigned long ln)) {
    FILE* fp = fopen(file, "r");
    if (!fp) {
        return 0;
    }

    unsigned long rows = 0;
    char buf[BUF_SIZE] = { 0 };
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        rows++;
        callback(buf, rows);
    }
    fclose(fp);
    return 1;
}

static const char* _read_all(const char* file) {
    FILE* fp = fopen(file, "r");
    if (!fp) {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    char* buf = (char*)malloc(file_size);
    fread(buf, file_size, 1, fp);
    fclose(fp);
    return buf;
}

// write
static int _trunc(const char* file) {
    FILE* fp = fopen(file, "w");
    if (!fp) {
        return 0;
    }

    fclose(fp);
    return 1;
}

static int _write(const char* file, const char* data) {
    FILE* fp = fopen(file, "w");
    if (!fp) {
        return 0;
    }

    size_t data_size = strlen(data);
    size_t size = fwrite(data, data_size, 1, fp);
    fclose(fp);
    return size == data_size ? 1 : 0;
}

static int _append(const char* file, const char* data) {
    FILE* fp = fopen(file, "a");
    if (!fp) {
        return 0;
    }

    size_t data_size = strlen(data);
    size_t size = fwrite(data, data_size, 1, fp);
    fclose(fp);
    return size == data_size ? 1 : 0;
}

static int _copy(const char* file_src, const char* file_dest) {
    FILE* rfp = fopen(file_src, "r");
    FILE* wfp = fopen(file_dest, "w");
    int res = 0;
    if (!(rfp && wfp)) {
        goto end;
    }

    char buf[BUF_SIZE] = { 0 };
    while (fgets(buf, sizeof(buf), rfp) != NULL) {
        fwrite(buf, 1, strlen(buf), wfp);
    }

    res = 1;
end:
    fclose(rfp);
    fclose(wfp);
    return res;
}

// delete
static int _remove(const char* file) {
    return remove(file) == -1 ? 0 : 1;
}

Fs fs = {
        .delete = _delete,
        .read_line = _read_line,
        .read_line_by_line = _read_line_by_line,
        .read_all = _read_all,
        .trunc = _trunc,
        .remove = _remove,
        .write = _write,
        .append = _append,
        .copy = _copy,
};