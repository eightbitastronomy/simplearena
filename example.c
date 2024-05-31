/*************************************************************************
 * author: Miguel Abele
 * License: none. 
 *          This source code may be used freely and without constraint.
 * Last updated: 31 may 2024
 *************************************************************************/




#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "simplearena.h"



int name(ArenaHolder ah, va_list vlist) {

  int i;
  char * name;
  int * age;
  char * name2;
  int * age2;

  name = (char *)astake(ah,sizeof(char)*8);
  age = (int *)astake(ah,sizeof(int));
  name[0]='G';
  name[1]='e';
  name[2]='o';
  name[3]='r';
  name[4]='g';
  name[5]='i';
  name[6]='a';
  name[7]='\0';
  *age = va_arg(vlist,int);

  printf("Name: %s, Age: %d\n", name, *age);
  printf("Staking some more...\n");
  
  name2 = (char *)astake(ah,sizeof(char)*5);
  name2[0] = 'L';
  name2[1] = 'y';
  name2[2] = 'r';
  name2[3] = 'a';
  name2[4] = '\0';
  age2 = (int *)astake(ah,sizeof(int));
  *age2 = va_arg(vlist,int);

  printf("Name: %s, Age: %d\n", name, *age);
  printf("Name2: %s, Age2: %d\n", name2, *age2);

  return 0;

}




int main() {

  printf("Running...\n");

  printf("Ret value: %d\n", wrapper_512(name, 29, 32));

  printf("Done.\n");
  
  return 0;

};
