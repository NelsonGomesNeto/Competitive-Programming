#include <stdio.h>
#include <string.h>

int main()
{
  char string[210]; int count = 0, ler;
  scanf("%[^\n]", string);
  for (ler = 0; ler < strlen(string); ler ++)
  {
    if (string[ler] >= '0' && string[ler] <= '9')
    {
      count ++;
    }
  }
  printf("%d\n", count);
  return(0);
}
