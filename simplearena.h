/*************************************************************************
 * author: Miguel Abele
 * License: none. 
 *          This source code may be used freely and without constraint.
 * Last updated: 17 june 2024
 *************************************************************************/




#ifndef SIMPLE_ARENA_H
#define SIMPLE_ARENA_H

#include <stdarg.h>


/* predefined sizes, in bytes */
#define ASIZE512  512
#define ASIZE1K     1024
#define ASIZE2K     2048
#define ASIZE4K     4096
#define ASIZE8K     8192
#define ASIZE16K   16384
#define ASIZE32K   32768
#define ASIZE64K   65536
#define ASIZE128K 131072
#define ASIZE256K 262144
#define ASIZE512K 524288
#define ASIZE1M         1048576
#define ASIZE2M         2097152
#define ASIZE4M         4194304
#define ASIZE8M         8388608
#define ASIZE16M       16777216
#define ASIZE32M       33554432
#define ASIZE64M       67108864
#define ASIZE128M     134217728


/* making sizings a tad clearer */
typedef unsigned char Byte;
typedef unsigned int uint32;
typedef unsigned long uint64;


/* struct for passing arena to functions and for use with macros */
struct arena_holder {
  void * arena;
  //void (*init_arena)(); //not in use
  void * (*stake)();
  uint64 asize;
};
typedef struct arena_holder ArenaHolder;


/* initialize the arena, must be called on the arena itself, i.e., ArenaHolder's arena member */
void init(void * a, uint64 asize);

/* stake memory, for use with by-value variable [ArenaHolder] */
#define astake(holder,sz) (holder).stake((holder).arena,(holder).asize,sz);

/* stake memory, for use with by-ref variable [ArenaHolder *] */
#define astakep(holder,sz) holder->stake(((ArenaHolder *)holder)->arena,((ArenaHolder *)holder)->asize,sz);

/* the actual function that does the staking. Let astake/astakep call this. */
void * stake_void(void * sandbox, uint64 asize, uint64 isize);


/* wrapper functions to implement predefined arena sizes */
int wrapper_512(int (*func)(ArenaHolder,va_list), ...);
int wrapper_1K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_2K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_4K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_8K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_16K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_32K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_64K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_128K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_256K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_512K(int (*func)(ArenaHolder,va_list), ...);
int wrapper_1M(int (*func)(ArenaHolder,va_list), ...);
int wrapper_2M(int (*func)(ArenaHolder,va_list), ...);
int wrapper_4M(int (*func)(ArenaHolder,va_list), ...);
int wrapper_8M(int (*func)(ArenaHolder,va_list), ...);
int wrapper_16M(int (*func)(ArenaHolder,va_list), ...);
int wrapper_32M(int (*func)(ArenaHolder,va_list), ...);
int wrapper_64M(int (*func)(ArenaHolder,va_list), ...);
int wrapper_128M(int (*func)(ArenaHolder,va_list), ...);


/* all the structs for the wrapper functions that shouldn't be used directly.
   Let the macros and wrapper functions do the dirty work. */

struct arena512 {
  Byte region[ASIZE512];
  struct arena512 * ptr;
};
typedef struct arena512 Arena512;

struct arena1K {
  Byte region[ASIZE1K];
  struct arena1K * ptr;
};
typedef struct arena1K Arena1K;

struct arena2K {
  Byte region[ASIZE2K];
  struct arena2K * ptr;
};
typedef struct arena2K Arena2K;

struct arena4K {
  Byte region[ASIZE4K];
  struct arena4K * ptr;
};
typedef struct arena4K Arena4K;

struct arena8K {
  Byte region[ASIZE8K];
  struct arena8K * ptr;
};
typedef struct arena8K Arena8K;

struct arena16K {
  Byte region[ASIZE16K];
  struct arena16K * ptr;
};
typedef struct arena16K Arena16K;

struct arena32K {
  Byte region[ASIZE32K];
  struct arena32K * ptr;
};
typedef struct arena32K Arena32K;

struct arena64K {
  Byte region[ASIZE64K];
  struct arena64K * ptr;
};
typedef struct arena64K Arena64K;

struct arena128K {
  Byte region[ASIZE128K];
  struct arena128K * ptr;
};
typedef struct arena128K Arena128K;

struct arena256K {
  Byte region[ASIZE256K];
  struct arena256K * ptr;
};
typedef struct arena256K Arena256K;

struct arena512K {
  Byte region[ASIZE512K];
  struct arena512K * ptr;
};
typedef struct arena512K Arena512K;

struct arena1M {
  Byte region[ASIZE1M];
  struct arena1M * ptr;
};
typedef struct arena1M Arena1M;

struct arena2M {
  Byte region[ASIZE2M];
  struct arena2M * ptr;
};
typedef struct arena2M Arena2M;

struct arena4M {
  Byte region[ASIZE4M];
  struct arena4M * ptr;
};
typedef struct arena4M Arena4M;

struct arena8M {
  Byte region[ASIZE8M];
  struct arena8M * ptr;
};
typedef struct arena8M Arena8M;

struct arena16M {
  Byte region[ASIZE16M];
  struct arena16M * ptr;
};
typedef struct arena16M Arena16M;

struct arena32M {
  Byte region[ASIZE32M];
  struct arena32M * ptr;
};
typedef struct arena32M Arena32M;

struct arena64M {
  Byte region[ASIZE64M];
  struct arena64M * ptr;
};
typedef struct arena64M Arena64M;

struct arena128M {
  Byte region[ASIZE128M];
  struct arena128M * ptr;
};
typedef struct arena128M Arena128M;





/************************** not in use *************************
#define INITARENA(sb,sz) *(uint64 *)((sb)+sz) = (uint64)(sb)

void init512(Arena512 * a);
void * stake512(Arena512 * sandbox, uint64 size);
void * stake_w_sz(Arena * sandbox, uint64 size);
void * stake_no_sz(Arena * sandbox, uint64 size);
#define STAKE(sb,sz) ( ((void *)((sb)->ptr)) + (uint64)sz > (void *)(sb) + ASIZE ? NULL : ((sb)->lst = (sb)->ptr, \
											   (sb)->ptr = ((void *)((sb)->ptr)) + (uint64)sz, \
											   (sb)->lst ) )
****************************************************************/


#endif //SIMPLE_ARENA_H
