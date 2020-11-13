#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2, maxK = 1e5; int n, k;
int a[maxN];

int memo[2][maxK + 1];
int solve(bool first = true, int stones = k)
{
  if (a[0] > stones) return first ? -1 : 1;
  int &ans = memo[first][stones];
  if (ans != 0) return ans;

  ans = first ? -1 : 1;
  for (int i = 0; i < n && a[i] <= stones; i++)
    if (first)
      ans = max(ans, solve(!first, stones - a[i]));
    else
      ans = min(ans, solve(!first, stones - a[i]));
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    memset(memo, 0, sizeof(memo));
    int ans = solve();
    printf("%s\n", ans == 1 ? "First" : "Second");
  }
  return 0;
}