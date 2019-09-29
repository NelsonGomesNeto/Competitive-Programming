#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    lli c, m, x; scanf("%lld %lld %lld", &c, &m, &x);
    printf("%lld\n", min((c + m + x) / 3, min(c, m)));
  }
  return(0);
}
