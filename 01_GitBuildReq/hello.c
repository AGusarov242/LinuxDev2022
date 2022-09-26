#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 32

void main() {
  char *str = malloc(sizeof(char) * BUFFSIZE);
  char c;
  unsigned cur_len = 0;
  unsigned increase = 2;
  while ((c = getchar()) != EOF && c != '\n')
  {
      str[cur_len] = c;
      cur_len++;
      if (cur_len > BUFFSIZE)
      {
          str  = realloc(str, sizeof(char) * increase*BUFFSIZE);
          increase *= 2;
      }
  }
  str[cur_len] = '\0';
  printf("Hello, %s\n", str);
  free(str);
}
