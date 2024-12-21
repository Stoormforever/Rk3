#include "array.h"
#include "errors.h"
#include <string.h>
#include <stdlib.h>

int compare_struct(const void *struct1, const void *struct2)
{
    return strcmp(((name_t*)struct1)->name, ((name_t*)struct2)->name);
}

int main(void)
{
    int rc;

    arr_t *arr = create_array();
    if (!arr)
        return ALLOCATION_ERROR;

    FILE *f_in = fopen("in.txt", "r");
    if (!f_in)
    {
        free_array(arr);
        return FILE_ERROR;
    }

    if ((rc = read_names(arr, f_in)))
    {
        free_array(arr);
        return rc;
    }
    fclose(f_in);
    qsort(arr->data, arr->len, sizeof(struct name), compare_struct);

    FILE *f_out = fopen("out.txt", "w");
    if (!f_out)
    {
        free_array(arr);
        return FILE_ERROR;
    }
    print_array(arr, f_out);

    fclose(f_out);
    free_array(arr);

    return 0;
}
