#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const string req = "MEX";
const int maxN = 2e5;
int n;
int a[maxN];
char s[maxN + 1];

int mexTable[1 << 3];
int mex(int mask)
{
  int hehe = ~mask;
  int ans = 0;
  while (hehe)
  {
    if (hehe & 1) return ans;
    hehe >>= 1, ++ans;
  }
  assert(false);
}

lli memo[maxN][1 << 3][3];
lli solve(int i = 0, int mask = 0, int j = 0)
{
  DEBUG printf("\t\t%d %d %d\n", i, mask, j);
  if (j == 3) return mexTable[mask];
  if (i == n) return 0;
  lli& ans = memo[i][mask][j];
  if (ans != -1) return ans;

  ans = solve(i + 1, mask, j);
  if (s[i] == req[j])
    ans += solve(i + 1, mask | (1 << a[i]), j + 1);

  return ans;
}

int main()
{
  for (int i = 0; i < (1 << 3); ++i)
  {
    mexTable[i] = mex(i);
    DEBUG printf("\t%d %d\n", i, mexTable[i]);
  }

  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    scanf(" %s", s);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
