#include <stdio.h>
#include <string.h>

int countPairDigits(long long int num)
{
  if (num < 10)
    return(!(num % 10 & 1));
  return(!(num % 10 & 1) + countPairDigits(num / 10));
}

int main()
{
  long long int num; scanf("%Ld", &num);
  int digits = countPairDigits(num);
  printf("%d\n", digits);
  return(0);
}
