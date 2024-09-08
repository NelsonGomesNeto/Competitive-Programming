#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n;
const int maxTotal = 4*maxN + 1, mid = 2*maxN;
int a[maxN];

const int inf = 1e3;
int memo[maxTotal][maxN];
int solve(int total = 0, int i = 0)
{
  if (i == n) return total == 0;
  int &ans = memo[total + mid][i];
  if (ans != -1) return ans;

  ans = solve(total + a[i], i + 1);
  ans = max(ans, solve(total - a[i], i + 1));
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
  
    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}
