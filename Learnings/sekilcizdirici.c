#include <stdio.h>
int main (int argc, char **argv){
  printf("arg says %d\n", argc);
  for (int i = 0; i < argc; i++)
    printf ("%d. Arg=%s\n", i + 1, argv[i]);
    return 0;
}