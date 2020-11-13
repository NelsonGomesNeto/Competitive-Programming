#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const int inf = 1e9;
int h[maxN];

int memo[maxN];
int solve(int i = 0)
{
  if (i >= n - 1) return i == n - 1 ? 0 : inf;
  int &ans = memo[i];
  if (ans != -1) return ans;

  return ans = min(solve(i + 1) + (i + 1 < n ? abs(h[i + 1] - h[i]) : 0),
                   solve(i + 2) + (i + 2 < n ? abs(h[i + 2] - h[i]) : 0));
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &h[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}