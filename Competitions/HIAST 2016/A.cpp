#include <bits/stdc++.h>
#define lli long long int

int odd(lli n)
{
  int divisions = 1;
  while (!(n & 1))
  {
    divisions = 1 - divisions;
    n >>= 1;
  }
  return(divisions);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli q; scanf("%lld", &q);
    if (q & 1 || odd(q)) printf("First Box\n");
    else printf("Second Box\n");
  }
  return(0);
}
