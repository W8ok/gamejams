#pragma once

#include <stdint.h>

// Why yes i do enjoy overenginnering
// What about it?

// #######################################
// Generic types
// #######################################

// Unsigned integers
typedef uint8_t u8;
typedef union {
    struct { u8 a, b; };
    struct { u8 x, y; };
    struct { u8 width, height; };
} u8_2;

typedef union {
    struct { u8 a, b, c; };
    struct { u8 x, y, z; };
    struct { u8 width, height, depth; };
} u8_3;

typedef union {
    struct { u8 a, b, c, d; };
    struct { u8 x, y, z, w; };
    struct { u8 width, height, depth, time; };
} u8_4;

typedef uint16_t u16;
typedef union {
    struct { u16 a, b; };
    struct { u16 x, y; };
    struct { u16 width, height; };
} u16_2;

typedef union {
    struct { u16 a, b, c; };
    struct { u16 x, y, z; };
    struct { u16 width, height, depth; };
} u16_3;

typedef union {
    struct { u16 a, b, c, d; };
    struct { u16 x, y, z, w; };
    struct { u16 width, height, depth, time; };
} u16_4;

typedef uint32_t u32;
typedef union {
    struct { u32 a, b; };
    struct { u32 x, y; };
    struct { u32 width, height; };
} u32_2;

typedef union {
    struct { u32 a, b, c; };
    struct { u32 x, y, z; };
    struct { u32 width, height, depth; };
} u32_3;

typedef union {
    struct { u32 a, b, c, d; };
    struct { u32 x, y, z, w; };
    struct { u32 width, height, depth, time; };
} u32_4;

typedef uint64_t u64;
typedef union {
    struct { u64 a, b; };
    struct { u64 x, y; };
    struct { u64 width, height; };
} u64_2;

typedef union {
    struct { u64 a, b, c; };
    struct { u64 x, y, z; };
    struct { u64 width, height, depth; };
} u64_3;

typedef union {
    struct { u64 a, b, c, d; };
    struct { u64 x, y, z, w; };
    struct { u64 width, height, depth, time; };
} u64_4;

// Signed integers
typedef int8_t i8;
typedef union {
    struct { i8 a, b; };
    struct { i8 x, y; };
    struct { i8 width, height; };
} i8_2;

typedef union {
    struct { i8 a, b, c; };
    struct { i8 x, y, z; };
    struct { i8 width, height, depth; };
} i8_3;

typedef union {
    struct { i8 a, b, c, d; };
    struct { i8 x, y, z, w; };
    struct { i8 width, height, depth, time; };
} i8_4;

typedef int16_t i16;
typedef union {
    struct { i16 a, b; };
    struct { i16 x, y; };
    struct { i16 width, height; };
} i16_2;

typedef union {
    struct { i16 a, b, c; };
    struct { i16 x, y, z; };
} i16_3;

typedef union {
    struct { i16 a, b, c, d; };
    struct { i16 x, y, z, w; };
    struct { i16 width, height, depth, time; };
} i16_4;

typedef int32_t i32;
typedef union {
    struct { i32 a, b; };
    struct { i32 x, y; };
    struct { i32 width, height; };
} i32_2;

typedef union {
    struct { i32 a, b, c; };
    struct { i32 x, y, z; };
    struct { i32 width, height, depth; };
} i32_3;

typedef union {
    struct { i32 a, b, c, d; };
    struct { i32 x, y, z, w; };
    struct { i32 width, height, depth, time; };
} i32_4;

typedef int64_t i64;
typedef union {
    struct { i64 a, b; };
    struct { i64 x, y; };
    struct { i64 width, height; };
} i64_2;

typedef union {
    struct { i64 a, b, c; };
    struct { i64 x, y, z; };
    struct { i64 width, height, depth; };
} i64_3;

typedef union {
    struct { i64 a, b, c, d; };
    struct { i64 x, y, z, w; };
    struct { i64 width, height, depth, time; };
} i64_4;

// Floating point
typedef float f32;
typedef union {
    struct { f32 a, b; };
    struct { f32 x, y; };
    struct { f32 width, height; };
} f32_2;

typedef union {
    struct { f32 a, b, c; };
    struct { f32 x, y, z; };
    struct { f32 width, height, depth; };
} f32_3;

typedef union {
    struct { f32 a, b, c, d; };
    struct { f32 x, y, z, w; };
    struct { f32 width, height, depth, time; };
} f32_4;

typedef double f64;
typedef union {
    struct { f64 a, b; };
    struct { f64 x, y; };
    struct { f64 width, height; };
} f64_2;

typedef union {
    struct { f64 a, b, c; };
    struct { f64 x, y, z; };
    struct { f64 width, height, depth; };
} f64_3;

typedef union {
    struct { f64 a, b, c, d; };
    struct { f64 x, y, z, w; };
    struct { f64 width, height, depth, time; };
} f64_4;


// #######################################
// Geometry
// #######################################

// Rectangle
typedef struct { i32 x, y, width, height; } Rect_i32;
typedef struct { i64 x, y, width, height; } Rect_i64;
typedef struct { f32 x, y, width, height; } Rect_f32;
typedef struct { f64 x, y, width, height; } Rect_f64;

// Circle
typedef struct { i32 x, y, radius; } Circle_i32;
typedef struct { i64 x, y, radius; } Circle_i64;
typedef struct { f32 x, y, radius; } Circle_f32;
typedef struct { f64 x, y, radius; } Circle_f64;

// Point
typedef struct { i32 x, y; } Point_i32;
typedef struct { i64 x, y; } Point_i64;
typedef struct { f32 x, y; } Point_f32;
typedef struct { f64 x, y; } Point_f64;

// Line
typedef struct { Point_i32 origin; Point_i32 termination; } Line_i32;
typedef struct { Point_i64 origin; Point_i64 termination; } Line_i64;
typedef struct { Point_f32 origin; Point_f32 termination; } Line_f32;
typedef struct { Point_f64 origin; Point_f64 termination; } Line_f64;

// Size
typedef struct { i32 width, height; } Size_i32;
typedef struct { i64 width, height; } Size_i64;
typedef struct { f32 width, height; } Size_f32;
typedef struct { f64 width, height; } Size_f64;


// #######################################
// Color
// #######################################

// Color types
typedef struct { u8 r, g, b, a; } Color_u8;
typedef struct { f32 r, g, b, a; } Color_f32;

// Grayscale
#define COLOR_WHITE_U8      (Color_u8){255, 255, 255, 255}
#define COLOR_LIGHTGRAY_U8  (Color_u8){192, 192, 192, 255}
#define COLOR_GRAY_U8       (Color_u8){128, 128, 128, 255}
#define COLOR_DARKGRAY_U8   (Color_u8){64, 64, 64, 255}
#define COLOR_BLACK_U8      (Color_u8){0, 0, 0, 255}

#define COLOR_WHITE_F32     (Color_f32){1.0f, 1.0f, 1.0f, 1.0f}
#define COLOR_LIGHTGRAY_F32 (Color_f32){0.75f, 0.75f, 0.75f, 1.0f}
#define COLOR_GRAY_F32      (Color_f32){0.5f, 0.5f, 0.5f, 1.0f}
#define COLOR_DARKGRAY_F32  (Color_f32){0.25f, 0.25f, 0.25f, 1.0f}
#define COLOR_BLACK_F32     (Color_f32){0.0f, 0.0f, 0.0f, 1.0f}

// RGB primaries
#define COLOR_RED_U8        (Color_u8){255, 0, 0, 255}
#define COLOR_GREEN_U8      (Color_u8){0, 255, 0, 255}
#define COLOR_BLUE_U8       (Color_u8){0, 0, 255, 255}
#define COLOR_YELLOW_U8     (Color_u8){255, 255, 0, 255}
#define COLOR_CYAN_U8       (Color_u8){0, 255, 255, 255}
#define COLOR_MAGENTA_U8    (Color_u8){255, 0, 255, 255}

#define COLOR_RED_F32       (Color_f32){1.0f, 0.0f, 0.0f, 1.0f}
#define COLOR_GREEN_F32     (Color_f32){0.0f, 1.0f, 0.0f, 1.0f}
#define COLOR_BLUE_F32      (Color_f32){0.0f, 0.0f, 1.0f, 1.0f}
#define COLOR_YELLOW_F32    (Color_f32){1.0f, 1.0f, 0.0f, 1.0f}
#define COLOR_CYAN_F32      (Color_f32){0.0f, 1.0f, 1.0f, 1.0f}
#define COLOR_MAGENTA_F32   (Color_f32){1.0f, 0.0f, 1.0f, 1.0f}
