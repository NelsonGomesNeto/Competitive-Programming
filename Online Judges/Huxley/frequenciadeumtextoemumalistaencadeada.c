#include <stdio.h>
#include <string.h>

int main()
{
  char string[200]; int i, ler, conta;
  scanf("%[^\n]", string);
  for (i = 255; i >= 0; i --)
  {
    conta = 0;
    //printf("%d ~~~ %c\n", i, (char) i);
    for (ler = 0; ler < strlen(string); ler ++)
    {
      if (string[ler] == (char) i)
      {
        conta ++;
      }
    }
    if (conta > 0)
    {
      printf("%c %d\n", (char) i, conta);
    }
  }
  return(0);
}
