#include <stdint.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1280

typedef uintptr_t uptr;

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef struct {u8 x; u8 y;} vec2;

typedef struct {
  char* str;
  int size;
} string;
