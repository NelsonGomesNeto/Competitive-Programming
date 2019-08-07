#include <stdio.h>

int main()
{
  int testes, pop; scanf("%d", &testes);
  while (testes > 0)
  {
    long long int result = 1;
    scanf("%d", &pop);
    while (pop > 3)
    {
      pop --;
      result = (pop * (result % 1000000007)) % 1000000007;
    }
    testes --;
    printf("%Ld\n", result);
  }
  return(0);
}
