#include <stdio.h>

void contadif(long long int num, long long int *conta)
{
  if (num > 0)
  {
    contadif(num >> 1, &*conta);
    (*conta) += num & 1;
  }
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    long long int a, b, bin;
    scanf("%Ld %Ld\n", &a, &b);
    long long int dif = 0;
    a = a ^ b;
    contadif(a, &dif);
    printf("%Ld\n", dif);
    tests --;
  }
  return(0);
}
