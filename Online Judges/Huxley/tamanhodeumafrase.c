#include <stdio.h>
#include <string.h>

int main()
{
  char string[500]; scanf("%[^\n]", string);
  printf("%d\n", (int) strlen(string));
  return(0);
}
