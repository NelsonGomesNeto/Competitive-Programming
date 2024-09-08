#include <stdio.h>
#include <string.h>

int check(char p[], int i, int tam)
{
  if (i == tam / 2)
  {
    return(1);
  }
  if (p[i] != p[tam - 1 - i])
  {
    return(0);
  }
  check(p, i + 1, tam);
}

int main()
{
  char palindromo[999];
  scanf("%s", palindromo);
  if (check(palindromo, 0, strlen(palindromo)) == 1)
  {
    printf("SIM\n");
  }
  else
  {
    printf("NAO\n");
  }
  return(0);
}
