#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10, maxM = 1e3, maxMask = 1<<9; int n, m, k;
const int inf = maxN * maxM;
char bar[maxN][maxM + 1];
int acc[maxN + 1][maxM + 1];

int getSum(int loi, int hii, int loj, int hij)
{
  loi++, hii++, loj++, hij++;
  return acc[hii][hij] - acc[hii][loj - 1] - acc[loi - 1][hij] + acc[loi - 1][loj - 1];
}

int ones(int num)
{
  int o = 0;
  while (num)
  {
    o += num & 1;
    num >>= 1;
  }
  return o;
}

int bitmask;
bool valid(int loj, int hij)
{
  int mk = 0;
  int loi = 0;
  for (int i = 0; i < n - 1; i++)
    if (bitmask & (1 << i))
    {
      mk = max(mk, getSum(loi, i, loj, hij));
      loi = i + 1;
    }
  mk = max(mk, getSum(loi, n - 1, loj, hij));
  return mk <= k;
}
int solve()
{
  int verticalCuts = -1, lo = 0;
  for (int j = 0; j < m; j++)
  {
    while (j + 1 < m && valid(lo, j + 1)) j++;
    if (j == lo && !valid(lo, j))
      return inf;
    lo = j + 1, verticalCuts++;
  }
  return ones(bitmask) + verticalCuts;
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", bar[i]);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        acc[i + 1][j + 1] = (bar[i][j] == '1') + acc[i][j + 1] + acc[i + 1][j] - acc[i][j];

    int ans = inf;
    for (bitmask = 0; bitmask < maxMask; bitmask++)
      ans = min(ans, solve());
    printf("%d\n", ans);
  }
  return 0;
}