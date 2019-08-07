#include <stdio.h>

int allowed(int n)
{
  int a = 1;
  while (n)
  {
    if ((n % 10) > 5) a = 0;
    n /= 10;
  }
  return(a);
}

int fix(int n)
{
  while (!allowed(n)) n += 5;
  return(n);
}

int retard(int n)
{
  int i = 0, k = 0; n --;
  while (n --)
  {
    i ++;
    if (!allowed(i))
    {
      i = fix(i);
      i --;
    }
  }
}

int pot(int x, int n)
{
  if (n == 0) return(1);
  int ret = pot(x, n / 2);
  if (n & 1) return(ret * ret * x);
  return(ret * ret);
}

int decTo6(int n, int depth)
{
  if (n == 0) return(0);
  return(pot(10, depth) * (n % 6) + decTo6(n / 6, depth + 1));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    printf("%d\n", decTo6(n - 1, 0));
  }
  return(0);
}
