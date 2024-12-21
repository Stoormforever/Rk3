#include "array.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"

arr_t *create_array(void)
{
    arr_t *arr = malloc(sizeof(struct arr));

    arr->data = NULL;
    arr->len = 0;
    arr->allocated = 0;

    return arr;
}

static int add_array(arr_t *arr, char *name)
{
    if (!arr->data)
    {
        arr->data = malloc(sizeof(struct name));
        if (!arr->data)
            return ALLOCATION_ERROR;
        arr->allocated++;
    }
    else 
    {
        if (arr->len >= arr->allocated)
        {
            name_t *tmp = realloc(arr->data, arr->allocated * 2 * sizeof(struct name));
            if (!tmp)
                return ALLOCATION_ERROR;
            arr->data = tmp;
            arr->allocated *= 2;
        }
    }

    arr->data[arr->len].count = 1;
    arr->data[arr->len].name = name;
    arr->len++;

    return ERR_OK;
}

int read_names(arr_t *arr, FILE *f)
{
    int rc;
    char *name = NULL;
    size_t allocated = 0;
    ssize_t len;

    while ((len = getline(&name, &allocated, f)) != -1)
    {
        if (name[len - 1] == '\n')
            name[len - 1] = '\0';
        size_t i = 0;
        for (; i < arr->len && strcmp(name, arr->data[i].name); i++);
        
        if (i != arr->len)
        {
            arr->data[i].count++;
            free(name);
            name = NULL;
        }
        if (name)
            if ((rc = add_array(arr, name)))
                return rc;
        
        name = NULL;
    }

    if (!feof(f) || arr->len == 0)
        return READ_ERROR;

    return ERR_OK;
}

void free_array(arr_t *arr)
{
    if (arr->data)
        for (size_t i = 0; i < arr->len; i++)
            free(arr->data[i].name);

    free(arr->data);
    free(arr);
}

void print_array(arr_t *arr, FILE *f)
{
    for (size_t i = 0; i < arr->len; i++)
        fprintf(f, "%s: %d\n", arr->data[i].name, arr->data[i].count);
}
