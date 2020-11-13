#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e2; int n;
const int inf = 1e6;
char ss[maxN + 1];
string s;

int memo[maxN][maxN];
int solve(int i = 0, int end = s.size() - 1)
{
  if (i >= end) return i <= end;
  int &ans = memo[i][end];
  if (ans != -1) return ans;

  ans = solve(i + 1, end) + 1;
  for (int k = i + 1; k <= end; k++)
    if (s[i] == s[k])
      ans = min(ans, solve(i + 1, k - 1) + solve(k, end));
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", ss);
    s = string(ss);
    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}