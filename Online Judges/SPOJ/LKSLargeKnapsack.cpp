#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 500, maxK = 2e6 + 1; int s, n;
struct Item
{
  int size, value;
  void read() { scanf("%d %d", &value, &size); }
};
Item items[maxN];

int memo[maxK];
int solve()
{
  memset(memo, 0, sizeof(memo));
  for (int i = 0; i < n; i ++)
    for (int c = s; c >= items[i].size; c --)
      memo[c] = max(memo[c], items[i].value + memo[c - items[i].size]);
  return memo[s];
}

int main()
{
  scanf("%d %d", &s, &n);
  for (int i = 0; i < n; i ++)
    items[i].read();

  memset(memo, 0, sizeof(memo));
  int ans = solve();
  printf("%d\n", ans);
  return 0;
}