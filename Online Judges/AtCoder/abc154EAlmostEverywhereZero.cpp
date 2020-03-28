#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxS = 100 + 1; int k;
char nn[maxS];
string n;

lli memo[maxS][4][2];
lli solve(int i = 0, int kk = 0, bool onLimit = true)
{
  if (i == n.size()) return kk == k;
  if (kk > k) return 0;
  if (memo[i][kk][onLimit] != -1) return memo[i][kk][onLimit];

  lli ans = solve(i + 1, kk, onLimit && n[i] == '0');
  for (int d = 1; onLimit ? d <= n[i] - '0' : d <= 9; d ++)
    ans += solve(i + 1, kk + 1, onLimit && n[i] - '0' == d);

  return memo[i][kk][onLimit] = ans;
}

int main()
{
  while (scanf(" %s", nn) != EOF)
  {
    scanf("%d", &k);
    n = string(nn);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}