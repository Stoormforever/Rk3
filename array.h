#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

#define _GNU_SOURCE

typedef struct name name_t;

struct name
{
    char *name;
    int count;
};

typedef struct arr arr_t;

struct arr
{
    name_t *data;
    size_t allocated;
    size_t len;
};

arr_t *create_array(void);

int read_names(arr_t *arr, FILE *f);

void free_array(arr_t *arr);

void print_array(arr_t *arr, FILE *f);

#endif
