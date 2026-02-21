#include "../../def.h"

#define ARENA_SIZE 1024

typedef struct arena {
  u8 mem[ARENA_SIZE];

  uptr offset;
} arena;

arena ARENA_Init();

void* ARENA_Alloc(arena* a, uptr size);

void ARENA_Free(arena* a, uptr offset);
void ARENA_Reset(arena* a);

string ARENA_strcpy(arena* a, string src);
