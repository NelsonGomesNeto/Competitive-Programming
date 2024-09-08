#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
const int maxN = 100;
char ss[maxN];
string s;
int n;

lli solve(int i, int j, int end)
{
  if (i == end)
    return 0;

  lli ans = solve(i + 1, j + 1, end);
  if (s[i] == s[j])
    ans = (1 + solve(i + 1, j + 1, end)) % mod;
  return ans;
}

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    n = s.size();

    lli ans = 0;
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
        ans = (ans + solve(i, j, j)) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}
