/*************************************************************************
 * author: Miguel Abele
 * License: none. 
 *          This source code may be used freely and without constraint.
 * Last updated: 31 may 2024
 *************************************************************************/




#include <stdlib.h>
#include "simplearena.h"



void init(void * a, uint64 asize) {
  *(uint64 *)(a+asize) = (uint64)a;
}


void * stake_void(void * sandbox, uint64 asize, uint64 isize) {

  void * primaryptr = (void *)(*(uint64 *)(sandbox+asize));
  if ( (primaryptr + isize) > (sandbox + asize) )
    return NULL;
  void * secondaryptr = primaryptr;
  primaryptr += isize;
  *(uint64 *)(sandbox+asize) = (uint64)primaryptr;
  return secondaryptr;

}


#define WRAPPERBODY(sz)  { va_list ptr;		\
			   int ret; \
			   ArenaHolder holder; \
			   holder.arena = (void *)&ar; \
			   init(&ar,sz); \
			   holder.stake = stake_void; \
			   holder.asize = sz; \
			   va_start(ptr,func); \
			   ret = func(holder,ptr); \
			   va_end(ptr); \
			   return ret; }


int wrapper_512(int (*func)(ArenaHolder,va_list), ...) {
  Arena512 ar;
  WRAPPERBODY(ASIZE512);
}


int wrapper_1K(int (*func)(ArenaHolder,va_list), ...) {
  Arena1K ar;
  WRAPPERBODY(ASIZE1K);
}


int wrapper_2K(int (*func)(ArenaHolder,va_list), ...) {
  Arena2K ar;
  WRAPPERBODY(ASIZE2K);
}


int wrapper_4K(int (*func)(ArenaHolder,va_list), ...) {
  Arena4K ar;
  WRAPPERBODY(ASIZE4K);
}


int wrapper_8K(int (*func)(ArenaHolder,va_list), ...) {
  Arena8K ar;
  WRAPPERBODY(ASIZE8K);
}


int wrapper_16K(int (*func)(ArenaHolder,va_list), ...) {
  Arena16K ar;
  WRAPPERBODY(ASIZE16K);
}


int wrapper_32K(int (*func)(ArenaHolder,va_list), ...) {
  Arena32K ar;
  WRAPPERBODY(ASIZE32K);
}


int wrapper_64K(int (*func)(ArenaHolder,va_list), ...) {
  Arena64K ar;
  WRAPPERBODY(ASIZE64K);
}


int wrapper_128K(int (*func)(ArenaHolder,va_list), ...) {
  Arena128K ar;
  WRAPPERBODY(ASIZE128K);
}


int wrapper_256K(int (*func)(ArenaHolder,va_list), ...) {
  Arena256K ar;
  WRAPPERBODY(ASIZE256K);
}


int wrapper_512K(int (*func)(ArenaHolder,va_list), ...) {
  Arena512K ar;
  WRAPPERBODY(ASIZE512K);
}


int wrapper_1M(int (*func)(ArenaHolder,va_list), ...) {
  Arena1M ar;
  WRAPPERBODY(ASIZE1M);
}


int wrapper_2M(int (*func)(ArenaHolder,va_list), ...) {
  Arena2M ar;
  WRAPPERBODY(ASIZE2M);
}


int wrapper_4M(int (*func)(ArenaHolder,va_list), ...) {
  Arena4M ar;
  WRAPPERBODY(ASIZE4M);
}


int wrapper_8M(int (*func)(ArenaHolder,va_list), ...) {
  Arena8M ar;
  WRAPPERBODY(ASIZE8M);
}


int wrapper_16M(int (*func)(ArenaHolder,va_list), ...) {
  Arena16M ar;
  WRAPPERBODY(ASIZE16M);
}


int wrapper_32M(int (*func)(ArenaHolder,va_list), ...) {
  Arena32M ar;
  WRAPPERBODY(ASIZE32M);
}


int wrapper_64M(int (*func)(ArenaHolder,va_list), ...) {
  Arena64M ar;
  WRAPPERBODY(ASIZE64M);
}


int wrapper_128M(int (*func)(ArenaHolder,va_list), ...) {
  Arena128M ar;
  WRAPPERBODY(ASIZE128M);
}




/**************************** not in use **********************************

void * stake0512(Arena0512 * sandbox, uint64 size) {

  void * primaryptr = (void *)(sandbox->ptr);
  if ( (primaryptr + size) > ((void *)sandbox + ASIZE) )
    return NULL;
  sandbox->lst = sandbox->ptr;
  primaryptr += size;
  sandbox->ptr = (Arena0512 *)primaryptr;
  return (void *)sandbox->lst;

}


void * stake_w_sz(Arena * sandbox, uint64 size) {

  void * primaryptr = sandbox->ptr;
  memcpy(primaryptr,&size,sizeof(uint64));
  primaryptr += sizeof(uint64);
  sandbox->lst = (Arena *)primaryptr;
  primaryptr += size;
  sandbox->ptr = (Arena *)primaryptr;
  return (void *)sandbox->lst;

}


void * stake_no_sz(Arena * sandbox, uint64 size) {

  void * primaryptr = (void *)(sandbox->ptr);
  if ( (primaryptr + size) > ((void *)sandbox + ASIZE) )
    return NULL;
  sandbox->lst = sandbox->ptr;
  primaryptr += size;
  sandbox->ptr = (Arena *)primaryptr;
  return (void *)sandbox->lst;

}


************************************************************/
