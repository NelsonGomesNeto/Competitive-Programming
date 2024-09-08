#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxX = 1e4; int n, x;
struct Jump
{
  int a, b;
  void read() { scanf("%d %d", &a, &b); }
};
Jump jumps[maxN];

int memo[maxN][maxX];
int solve(int i = 0, int p = 0)
{
  if (p > x) return false;
  if (i == n) return p == x;
  int &ans = memo[i][p];
  if (ans != -1) return ans;
  return ans = max(solve(i + 1, p + jumps[i].a), solve(i + 1, p + jumps[i].b));
}

int main()
{
  while (~scanf("%d %d", &n, &x))
  {
    for (int i = 0; i < n; i++) jumps[i].read();

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}