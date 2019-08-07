#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100, maxBudget = 25001; int n, m, budget;
struct Toy
{
  int amusement, annoyance, cost;
};
Toy toys[maxN];

int memo[maxN][maxBudget];
int solve(int i = 0, int b = budget)
{
  if (i == n) return(0);
  if (memo[i][b] == -1)
  {
    int ans = solve(i + 1, b);
    for (int j = 1, jj = 0, amusement = 0; j*toys[i].cost <= b && toys[i].amusement > jj*jj*toys[i].annoyance; j ++, jj ++)
    {
      amusement += toys[i].amusement - jj*jj*toys[i].annoyance;
      ans = max(ans, amusement + solve(i + 1, b - j*toys[i].cost));
    }
    memo[i][b] = ans;
  }
  return(memo[i][b]);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i ++)
      scanf("%d %d %d", &toys[i].amusement, &toys[i].annoyance, &toys[i].cost);

    scanf("%d", &m);
    for (int t = 0; t < m; t ++)
    {
      scanf("%d", &budget);
      printf("%d: %d\n", t, solve());
    }
  }
  return(0);
}