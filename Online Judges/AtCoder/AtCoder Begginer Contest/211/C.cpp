#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli mod = 1e9 + 7;
string target = "chokudai";
char s[maxN + 1];

lli memo[maxN][11];
lli solve(int i = 0, int j = 0)
{
  if (j == target.size()) return 1;
  if (i == n) return 0;
  lli &ans = memo[i][j];
  if (ans != -1) return ans;

  ans = solve(i + 1, j);
  if (s[i] == target[j]) ans = (ans + solve(i + 1, j + 1)) % mod;
  return ans;
}

int main()
{
  while (~scanf(" %s", s))
  {
    n = strlen(s);
    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}