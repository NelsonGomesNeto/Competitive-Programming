#include <stdio.h>

int main()
{
  long long int i, tam; scanf("%Ld", &tam);
  printf("%Ld\n", tam);
  for (i = 1; i <= tam; i ++)
  {
    printf("%Ld %ld\n", i, 1000000000000);
  }
}
