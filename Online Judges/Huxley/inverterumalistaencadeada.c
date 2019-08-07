#include <stdio.h>

int main()
{
  int num[999], ler = 0;
  while (scanf("%d", &num[ler]) != EOF)
  {
    ler ++;
  }
  for (; ler > 0; ler --)
  {
    printf("%d ", num[ler]);
  }
  printf("%d\n", num[0]);
  return(0);
}
