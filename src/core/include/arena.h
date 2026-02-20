#include "../../def.h"

#define ARENA_SIZE 1024

typedef struct arena {
  u8 mem[ARENA_SIZE];

  uptr offset;
} arena;

arena ARENA_Init();

uptr ARENA_Alloc(arena* a, uptr size);

void inline ARENA_Free(arena* a, uptr offset);
void inline ARENA_Reset(arena* a);
