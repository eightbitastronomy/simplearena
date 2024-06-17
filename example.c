/*************************************************************************
 * author: Miguel Abele
 * License: none. 
 *          This source code may be used freely and without constraint.
 * Last updated: 17 june 2024
 *************************************************************************/




#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "simplearena.h"
#include <string.h>


static inline char convert(const int n) {
  switch(n) {
  case 0:
    return '0';
  case 1:
    return '1';
  case 2:
    return '2';
  case 3:
    return '3';
  case 4:
    return '4';
  case 5:
    return '5';
  case 6:
    return '6';
  case 7:
    return '7';
  case 8:
    return '8';
  case 9:
    return '9';
  }
}


char * in_it_to_win_it(ArenaHolder * memarea, const char * entryname, int id) {

  /* Note: For each stake call, two lines are given which produce equivalent
     results (this is because the ArenaHolder variable is passed by ref). A,
     dereference the pointer and call astake. B, don't dereference, and call
     astakep. */
  char * bufferstr = (char *)astakep(memarea, sizeof(char)*5);
  //char * bufferstr = (char *)astake(*memarea, sizeof(char)*5);
  char * spacer;
  char * formatted = (char *)astake(*memarea, sizeof(char)*32);
  //char * formatted = (char *)astakep(memarea, sizeof(char)*32);
  int len = strlen(entryname);
  if (entryname[len-1] == '\0')
    len--;
  int spacing = 29 - len - 1;
  int factor = 1000;
  int bufferint = id;
  int i = 0;
  while (factor > 0) {
    bufferstr[i] = convert(bufferint / factor);
    bufferint -= (bufferint / factor) * factor;
    factor /= 10;
    i++;
  }
  bufferstr[4] = '\0';
  spacer = (char *)astakep(memarea, sizeof(char)*spacing);
  //spacer = (char *)astake(*memarea, sizeof(char)*spacing);  
  for (i=0; i<spacing; i++) {
    spacer[i] = ' ';
  }
  for (i=0; i<len; i++) {
    formatted[i] = entryname[i];
  }
  for (i=len; i<len+spacing; i++) {
    formatted[i] = spacer[i-len];
  }
  for (i=len+spacing; i<33; i++) {
    formatted[i] = bufferstr[i-len-spacing];
  }
  return formatted;

}


int name(ArenaHolder ah, va_list vlist) {

  int i;
  char * name;
  int * age;
  char * name2;
  int * age2;

  name = (char *)astake(ah,sizeof(char)*8);
  age = (int *)astake(ah,sizeof(int));
  sprintf(name, "Georgia");
  *age = va_arg(vlist,int);

  printf("Name: %s, Age: %d\n", name, *age);
  printf("Staking some more...\n");
  
  name2 = (char *)astake(ah,sizeof(char)*5);
  sprintf(name, "Lyra");
  age2 = (int *)astake(ah,sizeof(int));
  *age2 = va_arg(vlist,int);

  printf("Name: %s, Age: %d\n", name, *age);
  printf("Name2: %s, Age2: %d\n", name2, *age2);

  return 0;

}




int main() {

  printf("Running...\n");

  /* Example, when an arena is needed solely for a to-be-called function,
     and none of its contents are needed at the current level.
     Hence, this is the wrapper_### use case. */
  printf("Ret value: %d\n", wrapper_512(name, 29, 32));

  /* Example, when an arena will be used for both the current level as
     well as functions to be called. Note, this scenario might necessi-
     ate freeing & tracking of freed slots in the arena, which this
     library deliberately doesn't provide. If that kind of functionality
     is required, it is the humble opinion of this author that heap usage
     would be tolerable.
     Here is a contrived use case: when you need to make an array, fill
     it, and move on. */
  Arena512 toplevelmem;
  ArenaHolder mylittlepieceofheaven = { (void *)&toplevelmem, stake_void, ASIZE512 };
  char * horse1, * horse2, * horse3;
  init(mylittlepieceofheaven.arena,ASIZE512);
  horse1 = in_it_to_win_it(&mylittlepieceofheaven, "SeaEnglishMuffin", 445);
  horse2 = in_it_to_win_it(&mylittlepieceofheaven, "RoundTheBends", 100);
  horse3 = in_it_to_win_it(&mylittlepieceofheaven, "Constitutional", 23);
  printf("--------------------------------\nCompetition Entries:\n--------------------------------\n");
  printf("%s\n", horse1);
  printf("%s\n", horse2);
  printf("%s\n", horse3);
  printf("--------------------------------\n");
  
  printf("Done. Never used malloc or free.\n");
  
  return 0;

};
