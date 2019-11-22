#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3001; int n, t;
struct Dish
{
  int a, b;
  void read() { scanf("%d %d", &a, &b); }
  bool operator<(const Dish &other) const { return a < other.a || (a == other.a && b > other.b); }
};
Dish dishes[maxN];

int memo[maxN][2*maxN];
int solve(int i = 0, int b = 0)
{
  if (i == n) return 0;
  if (memo[i][b] != -1) return memo[i][b];

  int ans = solve(i + 1, b);
  if (b < 2*t)
    ans = max(ans, solve(i + 1, min(2*t, b + 2*dishes[i].a)) + dishes[i].b);
  return memo[i][b] = ans;
}

int main()
{
  while (scanf("%d %d", &n, &t) != EOF)
  {
    for (int i = 0; i < n; i ++)
      dishes[i].read();
    sort(dishes, dishes+n);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}