#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli n, m, k; scanf("%lld %lld %lld", &n, &m, &k);
  lli linesUp = ((k - n) / (m - 1));
  lli walked = ((k - n) % (m - 1));
  if (k < n) printf("%lld %lld\n", k + 1, (lli) 1);
  else printf("%lld %lld\n", n - linesUp, linesUp & 1 ? m - walked : 2 + walked);

  return(0);
}