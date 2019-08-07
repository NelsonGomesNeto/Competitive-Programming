#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
int n;

void read(int a[])
{
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
}

lli evaluate(int height[], int cost[], int h)
{
  lli c = 0;
  for (int j = 0; j < n; j ++)
    if (height[j] != h)
      c += cost[j] * abs(h - height[j]);
  return(c);
}

int chooseBest(int height[], int cost[], int lo, int hi)
{
  int best = lo, bV = evaluate(height, cost, lo);
  for (int i = lo + 1; i <= hi; i ++)
  {
    int nV = evaluate(height, cost, i);
    if (nV < bV)
    {
      bV = nV;
      best = i;
    }
  }
  return(best);
}

int ternarySearch(int height[], int cost[], int lo, int hi)
{
  if (lo >= hi - 2) return(chooseBest(height, cost, lo, hi));
  int mlo = (2*lo + hi) / 3, mhi = (lo + 2*hi) / 3 + 1;
  // printf("%d %d -- %d %d\n", lo, hi, mlo, mhi);
  lli elo = evaluate(height, cost, mlo), ehi = evaluate(height, cost, mhi);
  if (elo < ehi)
    return(ternarySearch(height, cost, lo, mhi - 1));
  else if (elo > ehi)
    return(ternarySearch(height, cost, mlo + 1, hi));
  else
    return(ternarySearch(height, cost, mlo, mhi));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    int height[n], cost[n];
    read(height); read(cost);

    int minHeight = 999999;
    for (int i = 0; i < n; i ++) minHeight = min(height[i], minHeight);
    int maxHeight = 0;
    for (int i = 0; i < n; i ++) maxHeight = max(height[i], maxHeight);

    DEBUG for (int i = minHeight; i <= maxHeight; i ++) printf("%d: %lld\n", i, evaluate(height, cost, i));
    DEBUG printf("\n");

    printf("%lld\n", evaluate(height, cost, ternarySearch(height, cost, minHeight, maxHeight)));
  }
  return(0);
}
