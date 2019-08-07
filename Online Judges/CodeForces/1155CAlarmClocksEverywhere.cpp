#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 3e5, maxM = 3e5; int n, m;
lli x[maxN], pp[maxM];
set<lli> p;
lli y, j, allGCD;

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &x[i]);
  }
  y = x[0];
  for (int i = 1; i < n; i ++)
  {
    if (i == 1) allGCD = x[i] - y;
    else allGCD = gcd(allGCD, x[i] - y);
  }
  for (int i = 0; i < m; i ++)
  {
    scanf("%lld", &pp[i]);
    p.insert(pp[i]);
  }

  bool can = false;
  for (int i = 0; i < m; i ++)
    if (allGCD % pp[i] == 0)
      j = i, can = true;
  if (!can)
    printf("NO\n");
  else
  {
    printf("YES\n");
    printf("%lld %lld\n", y, j + 1);
  }

  return(0);
}