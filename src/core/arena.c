#include "include/arena.h"

arena ARENA_Init(){
  arena a;
  a.offset = 0;

  return a;
}

uptr ARENA_Allocate(arena* a, uptr size){
  if (a->offset + size > ARENA_SIZE) return NULL;
  
  uptr pointer = a->offset;
  a->offset += size;
  return pointer;  
}

void inline ARENA_Free(arena* a, uptr offset){a->offset = offset;}

void inline ARENA_Reset(arena* a){a->offset = 0;}

string ARENA_strcpy(arena* a, string src) {
  u8* mem = (u8*) ARENA_Alloc(a, src.size);
  memcpy(mem, src.str, src.size);
  return (string){mem, src.size};
}
