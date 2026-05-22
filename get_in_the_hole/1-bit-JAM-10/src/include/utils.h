// utils.h
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// #######################################
// Logging
// #######################################

#ifdef LOGGING

#define ERROR_EXIT(fmt, ...) \
    do { \
        time_t now = time(NULL); \
        struct tm *tm_info = localtime(&now); \
        char time_buffer[20]; \
        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info); \
        fprintf(stderr, "ERROR: [%s] [%s:%d %s()] " fmt "\n", time_buffer, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        exit(EXIT_FAILURE); \
    } while(0)

#define ERROR_RETURN(fmt, ...) \
    do { \
        time_t now = time(NULL); \
        struct tm *tm_info = localtime(&now); \
        char time_buffer[20]; \
        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info); \
        fprintf(stderr, "ERROR: [%s] [%s:%d %s()] " fmt "\n", time_buffer, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        return false; \
    } while(0)

#define LOG_WARN(fmt, ...) \
    do { \
        time_t now = time(NULL); \
        struct tm *tm_info = localtime(&now); \
        char time_buffer[20]; \
        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info); \
        fprintf(stderr, "WARN: [%s] " fmt "\n", time_buffer, ##__VA_ARGS__); \
    } while(0)

#define LOG_INFO(fmt, ...) \
    do { \
        time_t now = time(NULL); \
        struct tm *tm_info = localtime(&now); \
        char time_buffer[20]; \
        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info); \
        printf("INFO: [%s] " fmt "\n", time_buffer, ##__VA_ARGS__); \
    } while(0)

#define LOG_DEBUG(fmt, ...) \
    do { \
        time_t now = time(NULL); \
        struct tm *tm_info = localtime(&now); \
        char time_buffer[20]; \
        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tm_info); \
        printf("DEBUG: [%s] " fmt "\n", time_buffer, ##__VA_ARGS__); \
    } while(0)

#else

#define ERROR_EXIT(fmt, ...) exit(EXIT_FAILURE)
#define ERROR_RETURN(fmt, ...) return false
#define LOG_WARN(fmt, ...)
#define LOG_INFO(fmt, ...)
#define LOG_DEBUG(fmt, ...)

#endif


// #######################################
// Dynamic Array
// #######################################

#define DA_APPEND(array, x) \
    do { \
        if (array.count >= array.capacity) \
        { \
            array.capacity++; \
            void* new_data = realloc(array.data, array.capacity * sizeof(*array.data)); \
            if (!new_data) \
                ERROR_RETURN("Memory Allocation Failure"); \
            array.data = new_data; \
        } \
        array.data[array.count++] = x; \
    } while(0)

#define DA_APPEND_DOUBLE(array, x) \
    do { \
        if (array.count >= array.capacity) \
        { \
            if (array.capacity == 0) \
                array.capacity = 1; \
            else \
                array.capacity *= 2; \
            void* new_data = realloc(array.data, array.capacity * sizeof(*array.data)); \
            if (!new_data) \
                ERROR_RETURN("Memory Allocation Failure"); \
            array.data = new_data; \
        } \
        array.data[array.count++] = x; \
    } while(0)

#define DA_APPEND_BY(array, x, increment) \
    do { \
        if (array.count >= array.capacity) \
        { \
            array.capacity += increment; \
            void* new_data = realloc(array.data, array.capacity * sizeof(*array.data)); \
            if (!new_data) \
                ERROR_RETURN("Memory Allocation Failure"); \
            array.data = new_data; \
        } \
        array.data[array.count++] = x; \
    } while(0)


// #######################################
// Misc
// #######################################

#define CAST(to, from) (*(to*)&(union{__typeof__(from) src; to dst;}){from}.dst)
