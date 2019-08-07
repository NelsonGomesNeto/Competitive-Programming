#include <bits/stdc++.h>
#define lli long long int

lli fat(lli n)
{
  if (n <= 1) return(1);
  return(n * fat(n - 1));
}

int main()
{
  lli m, n;
  while (scanf("%lld %lld", &m, &n) != EOF)
    printf("%lld\n", fat(m) + fat(n));
    
  return(0);
}