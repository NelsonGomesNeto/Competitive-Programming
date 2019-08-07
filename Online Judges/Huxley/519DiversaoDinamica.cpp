#include <bits/stdc++.h>
using namespace std;
//price, time
int n, k;
int toys[100][2], dp[100][100001], path[100][100001], inf = 1<<20;

int solve(int i, int k)
{
  if (i == -1) return(0);

  if (dp[i][k] == -1)
  {
    int ans = solve(i - 1, k), aux = -inf;
    if (k - toys[i][0] >= 0) aux = solve(i - 1, k - toys[i][0]) + toys[i][1];
    path[i][k] = aux >= ans;
    dp[i][k] = max(ans, aux);
  }

  return(dp[i][k]);
}

void printArray(int a[], int size)
{
  for (int i = 0; i < size; i ++) printf("%d%c", a[i], i < size - 1 ? ' ' : '\n');
}

int chooseToys(vector<int>& chosenToys)
{
  int cost = 0;
  for (int i = n - 1; i >= 0; i --)
    if (path[i][k - cost])
      chosenToys.push_back(i + 1), cost += toys[i][0];
  return(cost);
}

int main()
{
  int t, r = 1; scanf("%d", &t);
  while (r <= t)
  {
    scanf("%d %d", &n, &k); int can = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &toys[i][0]);
      if (toys[i][0] <= k) can = 1;
    }
    for (int i = 0; i < n; i ++) scanf("%d", &toys[i][1]);

    if (can)
    {
      for (int i = 0; i < n; i ++)
        memset(dp[i], -1, (k + 1) * sizeof(int)), memset(path[i], 0, (k + 1) * sizeof(int));
      int maxTime = solve(n - 1, k);
      vector<int> chosenToys;
      int cost = chooseToys(chosenToys);
      reverse(chosenToys.begin(), chosenToys.end());
      printf("brinquedos caso %d: ", r); printArray(&chosenToys[0], chosenToys.size());
      printf("custo total caso %d: %d\n", r, cost);
      printf("tempo total caso %d: %d\n", r, maxTime);
    }
    else printf("caso %d: saldo insuficiente\n", r);

    printf("\n"); r ++;
  }
  return(0);
}