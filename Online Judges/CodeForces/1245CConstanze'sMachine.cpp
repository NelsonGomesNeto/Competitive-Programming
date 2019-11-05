#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli mod = 1e9 + 7;
char s[maxN];

lli memo[maxN + 1];
lli solve(int i)
{
  if (i == 0) return 1;
  if (memo[i] == -1)
  {
    lli ans = solve(i - 1);
    if (i >= 2) ans = (ans + solve(i - 2)) % mod;
    memo[i] = ans;
  }
  return memo[i];
}

int main()
{
  memset(memo, -1, sizeof(memo));
  for (int i = 2; i <= maxN; i ++)
    memo[i] = solve(i);

  while (scanf("%s", s) != EOF)
  {
    getchar();
    n = strlen(s);
    vector<int> groups;
    for (int i = 0; i < n; i ++)
    {
      if (s[i] == 'u')
      {
        int j = i;
        while (j + 1 < n && s[j + 1] == 'u') j ++;
        if (i != j) groups.push_back(j - i + 1);
        i = j;
      }
      if (s[i] == 'n')
      {
        int j = i;
        while (j + 1 < n && s[j + 1] == 'n') j ++;
        if (i != j) groups.push_back(j - i + 1);
        i = j;
      }
    }
    lli ans = 1;
    for (int i: groups)
      ans = (ans * memo[i]) % mod;
    for (int i = 0; i < n; i ++)
      if (s[i] == 'm' || s[i] == 'w')
        ans = 0;
    printf("%lld\n", ans);
  }
  return 0;
}
