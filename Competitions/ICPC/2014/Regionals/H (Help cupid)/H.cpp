#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int n;
int t[maxN];

int memo[maxN][maxN];
int solve(int i = 0, int j = n - 1)
{
  if (i >= j) return(0);
  if (memo[i][j] == -1)
  {
    int nxt = min(abs(t[i] - t[i + 1]), 24 - abs(t[i] - t[i + 1]));
    int end = min(abs(t[j] - t[j - 1]), 24 - abs(t[j] - t[j - 1]));
    int over = min(abs(t[i] - t[j]), 24 - abs(t[i] - t[j]));
    int ans = min({solve(i + 2, j) + nxt, solve(i, j - 2) + end, solve(i + 1, j - 1) + over});
    memo[i][j] = ans;
  }
  return(memo[i][j]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &t[i]);
  sort(t, t+n);
  // for (int i = 0; i < n; i ++) printf("%3d%c", t[i], i < n - 1 ? ' ' : '\n');

  memset(memo, -1, sizeof(memo));
  int ans = solve();
  printf("%d\n", ans);

  return(0);
}