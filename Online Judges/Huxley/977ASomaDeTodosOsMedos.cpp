#include <bits/stdc++.h>
#define DEBUG if(1)
using namespace std;
// sadness, fear
int dp[2000][2001], events[2000][2], n;
int path[2000][2001], inf = 1<<20;

int solve(int i, int limit)
{
  if (i == n) return(0);

  if (dp[i][limit] == -1)
  {
    int ans = solve(i + 1, limit) + events[i][0], aux = inf;
    if (limit - events[i][1] >= 0) aux = solve(i + 1, limit - events[i][1]);
    path[i][limit] = aux > ans; // if <= I shouldn't choose
    dp[i][limit] = min(ans, aux);
  }

  return(dp[i][limit]);
}

void printArray(int a[], int size)
{
  for (int i = 0; i < size; i ++) printf("%d%c", a[i], i < size - 1 ? ' ' : '\n');
}

int chooseEvents(vector<int>& chosen, int limit)
{
  int fear = 0;
  for (int i = 0; i < n; i ++)
    if (path[i][limit - fear])
      chosen.push_back(n - i - 1);
    else
      fear += events[i][1];
  return(fear);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  memset(path, 0, sizeof(path));

  int limit; scanf("%d %d", &n, &limit);
  for (int i = n - 1; i >= 0; i --) scanf("%d %d", &events[i][0], &events[i][1]);

  int sadness = solve(0, limit);
  vector<int> chosenEvents;
  int fear = chooseEvents(chosenEvents, limit);
  printf("%d %d\n", sadness, fear);
  reverse(chosenEvents.begin(), chosenEvents.end());
  printArray(&chosenEvents[0], chosenEvents.size());

  return(0);
}