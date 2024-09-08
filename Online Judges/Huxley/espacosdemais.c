#include <stdio.h>
#include <string.h>

int main()
{
  char word[99]; scanf("%[^\n]", word);
  int ler, abre;
  for (ler = 0; ler < strlen(word); ler ++)
  {
    if (word[ler] != ' ')
    {
      printf("%c", word[ler]);
      abre = 0;
    }
    else if (abre == 0)
    {
      printf(" ");
      abre ++;
    }
  }
  printf("\n");
  return(0);
}
