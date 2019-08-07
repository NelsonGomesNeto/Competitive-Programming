#include <stdio.h>

int sumDigits(int num)
{
  int sum = 0;
  while (num > 0)
  {
    sum += num % 10;
    num /= 10;
  }
  return(sum);
}

int digitalRoot(int num)
{
  while (num > 9) num = sumDigits(num);
  return(num);
}

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    int k, x; scanf("%d %d", &k, &x);
    int i = 0, found = 0;
    while (found < k)
      if (digitalRoot(++ i) == x) found ++;
      
    printf("%d\n", i);
  }
  return(0);
}