#include <stdio.h>

int main()
{
  char string[99];
  scanf("%[^\n]", string);
  printf("%s", string);
  return(0);
}
