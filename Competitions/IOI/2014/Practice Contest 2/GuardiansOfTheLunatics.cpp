#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxL = 8e3 + 1, maxG = 800 + 1; int l, g;
const lli inf = 1e18;
lli c[maxL], sum[maxL + 1];

lli getCost(int i, int j)
{
  return (j - i + 1) * (sum[j + 1] - sum[i]);
}

lli memo[maxG][maxL];
void solve(int i, int lo = 1, int hi = l, int optlo = 1, int opthi = l)
{
  if (lo > hi) return;

  int mid = (lo + hi) >> 1, optj;
  memo[i][mid] = inf;
  // printf("%d %d %d %d - %lld\n", i, lo, hi, mid, memo[i][mid]);
  for (int j = optlo, end = min(opthi, mid); j <= end; j ++)
  {
    // printf("\t%d - %lld %lld - %lld\n", j, memo[i - 1][j], getCost(j + 1, mid), memo[i - 1][j] + getCost(j + 1, mid));
    if (memo[i - 1][j] + getCost(j + 1, mid) < memo[i][mid])
      memo[i][mid] = memo[i - 1][j] + getCost(j + 1, mid), optj = j;
  }

  solve(i, lo, mid - 1, optlo, optj);
  solve(i, mid + 1, hi, optj, opthi);
}

int main()
{
  scanf("%d %d", &l, &g);
  for (int i = 1; i <= l; i ++)
  {
    scanf("%lld", &c[i]);
    sum[i + 1] = sum[i] + c[i];
  }

  for (int i = 1; i <= l; i ++)
    memo[1][i] = getCost(1, i);
  for (int i = 2; i <= g; i ++)
    solve(i);

  printf("%lld\n", memo[g][l]);

  return(0);
}