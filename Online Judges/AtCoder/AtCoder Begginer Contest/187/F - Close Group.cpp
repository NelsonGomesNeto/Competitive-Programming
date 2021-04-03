#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 18; int n, m;
const int inf = maxN*maxN;
bool has[maxN][maxN];

int getMsb(int mask)
{
  int msb = 0;
  for (int i = 0; i < n; i++)
    if (mask & (1 << i))
      msb = i;
  return msb;
}

bool bitmasks[1 << maxN];
vector<int> validMasks[maxN];
int memo[1 << maxN];
int solve(int totalMask = 0)
{
  if (totalMask == ((1 << n) - 1)) return 0;
  int missing = ~totalMask & ((1 << n) - 1);
  if (bitmasks[missing]) return 1;
  int &ans = memo[totalMask];
  if (ans != -1) return ans;

  ans = inf;
  for (int mask: validMasks[getMsb(missing)])
    if (!(totalMask & mask))
      ans = min(ans, solve(totalMask | mask) + 1);
  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    memset(has, false, sizeof(has));
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      has[u][v] = has[v][u] = true;
    }

    for (int i = 0; i < n; i++) validMasks[i].clear();
    for (int bitmask = 0, end = 1 << n; bitmask < end; bitmask++)
    {
      bool valid = true;
      for (int u = 0; u < n; u++)
        if (bitmask & (1 << u))
          for (int v = u + 1; v < n; v++)
            if (bitmask & (1 << v))
              valid &= has[u][v];
      bitmasks[bitmask] = valid;
      if (valid)
        validMasks[getMsb(bitmask)].push_back(bitmask);
    }

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}