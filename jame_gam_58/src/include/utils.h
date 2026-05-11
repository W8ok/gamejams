#pragma once

#include <stdlib.h>

// Dont ask
#define CAST(to, from) (*(to*)&(union{__typeof__(from) src; to dst;}){from}.dst)

#define DA_APPEND(array, x) \
    do { \
        if ((array)->count >= (array)->capacity) \
        { \
            if ((array)->capacity == 0) \
                (array)->capacity = 1; \
            else \
                (array)->capacity *= 2; \
            void* new_data = realloc((array)->data, (array)->capacity * sizeof(*(array)->data)); \
            if (!new_data) \
                exit(EXIT_FAILURE); \
            (array)->data = new_data; \
        } \
        (array)->data[(array)->count++] = x; \
    } while(0)
