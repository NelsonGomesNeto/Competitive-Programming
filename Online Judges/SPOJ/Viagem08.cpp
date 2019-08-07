#include <bits/stdc++.h>
int minInf = INT_MIN;
using namespace std;
int dp[501][501][501];

int knapsack(pair<int, int> place[], int before, int i, int places, int priceLimit, int end)
{
  i %= places;
  if (i == end)
  {
    if (priceLimit - abs(place[end].second - place[before].second) >= 0)
      return(0);
    return(-10000);
  }

  if (dp[before][i][priceLimit] == -1)
  {
    dp[before][i][priceLimit] = knapsack(place, before, i + 1, places, priceLimit, end);
    if (abs(place[i].second - place[before].second) <= priceLimit)
      dp[before][i][priceLimit] = max(dp[before][i][priceLimit], 1 + knapsack(place, i, i + 1, places, priceLimit - abs(place[i].second - place[before].second), end));
  }

  return(dp[before][i][priceLimit]);
}

int main()
{
  int places, priceLimit; scanf("%d %d", &places, &priceLimit);
  pair<int, int> aux[places], start; int i, j, f = 0;
  int lat, lon;
  memset(dp, -1, sizeof(dp));
  for (i = 0; i < places; i ++)
  {
    scanf("%d %d", &lat, &lon);
    if (!i) start = {lon, lat};
    //if (lon < 0) lon = 180 + (-lon);
    aux[i] = {lon, lat};
  }

  sort(aux, aux + places);

  pair<int, int> place[places + 1];
  int k;
  for (i = 0, k = 0; k < places; i ++)
  {
    i %= places;
    //printf("%d %d %d\n", j, aux[i].second, aux[i].first);
    if (aux[i].first == start.first && f == 0)
    {
      place[k ++] = aux[i];
      f = 1;
    }
    else if (f == 1)
      place[k ++] = aux[i];
    if (aux[i] == start)
      j = k - 1;
  }
  for (i = 0; i < places; i ++)
    printf("%d %d %d\n", i, place[i].second, place[i].first);
  printf("%d %d\n", j, j + 1);

  // pair<int, int> a = place[j];
  // place[j] = place[0];
  // place[0] = a;

  int answer = knapsack(place, j, j + 1, places, priceLimit, j);
  //answer = (answer + knapsack2(place, 0, 1, places, priceLimit)) / 2;

  printf("%d\n", answer);

  return(0);
}