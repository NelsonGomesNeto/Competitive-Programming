#include <bits/stdc++.h>
int minInf = INT_MIN;
using namespace std;
int dp2[501][501][501];
map<vector<int>, int> dp;

int knapsack(pair<int, int> place[], int now, int i, int places, vector<int> visited, int priceLimit, int lol)
{
  //printf("%lu\n", dp.count(visited));

  if (i == places)
  {
    if (priceLimit - abs(place[0].second - place[now].second) >= 0)
    {
      //printf("%d\n", lol);
      return(0);
    }
    return(-10000);
  }

  if (dp.count(visited) == 0 || dp2[i][priceLimit][priceLimit] == -1)
  {
    //visited[now] = 1;
    //visited[now] = 1;
    int k, best = knapsack(place, now, i + 1, places, visited, priceLimit, lol);
    for (k = 1; k < places; k ++)
    {
      if (!visited[k])
      {
        int newPrice = priceLimit - abs(place[k].second - place[now].second);
        if (newPrice >= 0 && place[k].first >= place[now].first)
        {
          visited[k] = 1;
          best = max(best, 1 + knapsack(place, k, i + 1, places, visited, newPrice, lol + 1));
          visited[k] = 0;
        }
      }
    }
    //best = max(best, knapsack(place, now, i + 1, places, visited, priceLimit, lol));
    dp[visited] = best;
    dp2[i][priceLimit][priceLimit] = best;
    //visited[now] = 0;
  }

  return(max(dp2[i][priceLimit][priceLimit], dp[visited]));
}

int main()
{
  int places, priceLimit; scanf("%d %d", &places, &priceLimit);
  pair<int, int> aux[places], start; int i, j, f = 0;
  pair<int, int> place[places];
  int lat, lon;
  for (i = 0; i < places; i ++)
  {
    scanf("%d %d", &lat, &lon);
    if (!i) start = {lon, lat};
    if (lon < 0) lon += 360;
    //if (lon < 0) lon = 180 + (-lon);
    place[i] = {lon, lat};
  }

  //sort(place, place + places);

  for (i = 0; i < places; i ++)
    printf("%d %d %d\n", i, place[i].second, place[i].first);

  vector<int> visited;
  for (i = 0; i <= places; i ++) visited.push_back(0);
  visited[0] = 1;

  memset(dp2, -1, sizeof(dp2));
  int answer = knapsack(place, 0, 0, places, visited, priceLimit, 0);
  //answer = (answer + knapsack2(place, 0, 1, places, priceLimit)) / 2;

  printf("%d\n", answer);

  for (auto m : dp)
  {
    printf("%d ", m.second);
  } printf("\n");

  return(0);
}