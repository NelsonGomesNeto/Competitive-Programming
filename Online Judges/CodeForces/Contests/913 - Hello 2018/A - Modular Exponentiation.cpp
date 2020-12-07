#include <bits/stdc++.h>
#define lli long long int
#define DEBUG if(0)

int main()
{
  DEBUG for (int i = 1; i < 11; i ++) for (int j = 1; j < 11; j ++)
      printf("%d mod %lld = %lld\n", i, (lli) pow(2, j), i % (lli) pow(2, j));

  lli n, m; scanf("%lld\n%lld", &n, &m);

  if (log2(n) <= m)
    printf("%lld\n", m % (lli) pow(2, n));
  else
    printf("%lld\n", m);

  return(0);
}