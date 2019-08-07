#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli s, g; scanf("%lld %lld", &s, &g);
  if (s <= g || (s - g) % g) printf("-1\n");
  else printf("%lld %lld\n", (s - g), g);
  return(0);
}