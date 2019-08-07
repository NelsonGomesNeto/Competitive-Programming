#include <stdio.h>

long long int mult(long long int x)
{
  long long int result = 1;
  while (x > 0)
  {
    result *= x % 10;
    x /= 10;
  }
  return(result);
}

int main()
{
  long long int N, Q = 0; scanf("%Ld", &N);
  while (mult(Q) != N && Q < 1000000)
  {
    Q ++;
  }
  if (Q != 1000000)
  {
    printf("%Ld\n", Q);
  }
  else
  {
    printf("-1\n");
  }
  return(0);
}
