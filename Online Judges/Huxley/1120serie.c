#include <stdio.h>
#include <math.h>

double fatorial(int n)
{
  if (n <= 1)
    return(1);
  return(n * fatorial(n - 1));
}

void serie(int i, int n, double sum)
{
  double now = fatorial(i)/sqrt(2*i + 1);
  sum += now;
  if (i == n)
  {
    printf("S: %.12Lf\n", sum);
    return;
  }
  serie(i + 1, n, sum);
  printf("%.12Lf\n", now);
}

int main()
{
  int n; scanf("%d", &n);
  serie(1, n, 0);
}