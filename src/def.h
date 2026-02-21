#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1280

#define STR(x) (string){.str=(u8*)x, .size=strlen(x)+1}
#define MAX(a, b) (a>b)?a:b
#define MIN(a, b) (a<b)?a:b

#define BIT_FLAG_CMP(a, b)    a & b
#define BIT_FLAG_ADD(a, b)    a = a | b
#define BIT_FLAG_DELETE(a, b) a = a & !b
#define BIT_FLAG_CLEAR(a)     a = 0

typedef uintptr_t uptr;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef struct {u8 x; u8 y;} vec2;

typedef struct {
  u8* str;
  u64 size;
} string;
