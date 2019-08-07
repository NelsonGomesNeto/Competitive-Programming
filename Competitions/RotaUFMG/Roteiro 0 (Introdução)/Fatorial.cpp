#include <bits/stdc++.h>
#define lli long long int

lli fat(int n)
{
  if (n <= 1) return((lli) 1);
  return((lli) n * fat(n - 1));
}

int main()
{
  int n; scanf("%d", &n);

  printf("%lld\n", fat(n));

  return(0);
}