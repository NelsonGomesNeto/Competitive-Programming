#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3 + 1; int s, n;
struct Item
{
  int size, value;
  void read() { scanf("%d %d", &size, &value); }
};
Item items[maxN];

int memo[maxN][maxN];
int solve(int i = 0, int c = s)
{
  if (i == n) return 0;
  if (memo[i][c] != -1) return memo[i][c];
  int ans = solve(i + 1, c);
  if (c - items[i].size >= 0)
    ans = max(ans, solve(i + 1, c - items[i].size) + items[i].value);
  return memo[i][c] = ans;
}

int main()
{
  scanf("%d %d", &s, &n);
  for (int i = 0; i < n; i ++)
    items[i].read();

  memset(memo, -1, sizeof(memo));
  int ans = solve();
  printf("%d\n", ans);
  return 0;
}