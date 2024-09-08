#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9 + 7;
const int maxN = 1e6; int n;
char s[maxN + 1];
char diff[256][256];

unordered_set<size_t> memo[maxN];
lli solve(int i = 0, char prv = 'A', string t = "", size_t h = 0)
{
  if (i >= n) return 1;
  if (memo[i].count(h))
    return 0;
  memo[i].insert(h);
  // lli &ans = memo[i][prv - 'A'];
  // if (ans != -1) return ans;

  size_t h2 = h + hash<char>()(s[i]);
  lli ans = solve(i + 1, s[i], s[i] + t, h2);
  if (i && diff[prv][s[i]])
  {
    t.back() = diff[prv][s[i]];
    h -= hash<char>()(prv);
    h += hash<char>()(t.back());
    ans = (ans + solve(i + 1, diff[prv][s[i]], t, h)) % mod;
  }
  return ans;
}

int main()
{
  memset(diff, 0, sizeof(diff));
  for (char i = 'A'; i <= 'C'; i++)
    for (char j = 'A'; j <= 'C'; j++)
      for (char k = 'A'; k <= 'C'; k++)
        if (k != i && k != j && i != j)
          diff[i][j] = k;

  while (~scanf("%d", &n))
  {
    scanf(" %s", s);

    for (int i = 0; i < n; i++)
      memo[i].clear();
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}