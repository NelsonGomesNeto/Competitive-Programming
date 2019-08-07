#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli now = 1, ans[1000001];
  for (int i = 0; i <= 1000000; i ++)
  {
    ans[i] = now % 10;
    now *= i + 1;
    while (now % 10 == 0) now /= 10;
    if (now > 1000000) now %= 1000000;
  }

  int n, t = 1;
  while (scanf("%d", &n) != EOF)
    printf("Instancia %d\n%lld\n\n", t ++, ans[n]);
  return(0);
}