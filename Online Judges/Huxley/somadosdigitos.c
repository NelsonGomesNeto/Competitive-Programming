#include <stdio.h>
#include <string.h>

int main()
{
  char string[99]; int ler, soma = 0;
  scanf("%[^\n]", string);
  for (ler = 0; ler < strlen(string); ler ++)
  {
    soma += (int) string[ler] - 48;
  }
  printf("%d\n", soma);
}
