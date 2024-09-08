#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5;
int n;
struct Food
{
  int poison; lli tasty;
  void read() { scanf("%d %lld", &poison, &tasty); }
};
Food foods[maxN];

lli memo[maxN][2];
bool visited[maxN][2];
lli solve(int i = 0, bool healthy = true)
{
  if (i == n) return 0;
  lli& ans = memo[i][healthy];
  if (visited[i][healthy]) return ans;
  visited[i][healthy] = true;

  ans = solve(i + 1, healthy);
  if (!foods[i].poison || healthy)
    ans = max(ans, solve(i + 1, !foods[i].poison) + foods[i].tasty);
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      foods[i].read();

    memset(visited, false, sizeof(visited));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
