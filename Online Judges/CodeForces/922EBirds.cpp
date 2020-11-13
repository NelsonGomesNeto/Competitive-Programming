#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxC = 1e4; int n; lli w, b, x;
const int maxAns = maxC;
int c[maxN];
lli costs[maxN];

lli getCapacity(int imps)
{
  return w + imps * b;
}
lli memo[maxAns + 1];
lli aux[maxAns + 1];
// memo[i] = the maximum amount of mana if 'i' birds were summoned
int solve()
{
  memset(memo, -1, sizeof(memo));

  for (int i = 0; i <= c[0]; i++)
    if (w - i * costs[0] >= 0)
      memo[i] = min(w - i * costs[0] + x, getCapacity(i));

  for (int j = 1; j < n; j++)
  {
    memcpy(aux, memo, sizeof(memo));
    for (int i = 0; i <= c[j]; i++)
      for (int k = maxAns; k >= 0; k--)
        if (aux[k] - i * costs[j] >= 0)
          memo[i + k] = max(memo[i + k], min(aux[k] - i * costs[j] + x, getCapacity(i + k)));
  }

  for (int i = maxAns; i >= 0; i--)
    if (memo[i] > -1)
      return i;
  return 0;
}

int main()
{
  while (scanf("%d %lld %lld %lld", &n, &w, &b, &x) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &c[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &costs[i]);

    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}