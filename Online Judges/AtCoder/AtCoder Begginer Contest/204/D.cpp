#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxT = 1e3; int n;
int t[maxN];

int memo[maxN][maxN * maxT + 1];
int solve(int i = 0, int freeAt1 = 0, int freeAt2 = 0)
{
  if (i == n) return max(freeAt1, freeAt2);
  int &ans = memo[i][freeAt2];
  if (ans != -1) return ans;

  ans = min(
    solve(i + 1, freeAt1 + t[i], freeAt2),
    solve(i + 1, freeAt1, freeAt2 + t[i])
  );
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &t[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}