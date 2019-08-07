#include <bits/stdc++.h>

double fact(double n)
{
  if (n < 2) return((double) 1);
  return(n * fact(n - 1));
}

int main()
{
  int n; scanf("%d", &n);

  int isPrime[100001]; for (int i = 0; i <= 100000; i ++) isPrime[i] = 1;
  isPrime[0] = isPrime[1] = 0;
  for (int i = 2; i <= 100000; i ++)
    if (isPrime[i])
      for (int j = 2; i*j <= 100000; j ++)
        isPrime[i*j] = 0;
  isPrime[1] = 1;

  double sum = 0;
  for (int i = 1, j = 1; i <= n; i ++)
  {
    printf("%s%d!/%d%c", i > 1 ? "+ " : "\0", i, j, i < n ? ' ' : '\n');
    sum += fact(i) / (double) j;
    if (i == j) { j ++; while (!isPrime[j]) j ++; }
  }
  printf("%.2lf\n", sum);

  return(0);
}