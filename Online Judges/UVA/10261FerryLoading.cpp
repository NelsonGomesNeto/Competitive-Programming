#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int length; vector<int> cars;
vector<int> dp[(int) 1e4 + 1], path[(int) 1e4 + 1];

int solve(int i, int port, int starboard)
{
  if (i == cars.size()) return(0);
  if (dp[port][i] == -1)
  {
    int p = 0, s = 0;
    if (port + cars[i] <= length) p = solve(i + 1, port + cars[i], starboard) + 1;
    if (starboard + cars[i] <= length) s = solve(i + 1, port, starboard + cars[i]) + 1;
    path[port][i] = p >= s;
    dp[port][i] = max(p, s);
  }
  return(dp[port][i]);
}

void printPath(int end)
{
  for (int i = 0, port = 0, starboard = 0; i < end; i ++)
  {
    printf("%s\n", path[port][i] ? "port" : "starboard");
    if (path[port][i]) port += cars[i];
    else starboard += cars[i];
  }
}

int main()
{
  int t, tt = 0; scanf("%d", &t);
  while (t --)
  {
    if (tt ++) printf("\n");
    scanf("%d", &length); length *= 100;
    cars.clear(); int size;
    while (scanf("%d", &size) && size) cars.push_back(size);
    for (int i = 0; i <= length; i ++)
    {
      dp[i].clear(); dp[i].resize(cars.size()); path[i].clear(); path[i].resize(cars.size());
      for (int j = 0; j < cars.size(); j ++) dp[i][j] = -1;
    }
    DEBUG for (int i = 0; i < cars.size(); i ++) printf("%d%c", cars[i], i < cars.size() - 1 ? ' ' : '\n');

    int ans = solve(0, 0, 0);
    printf("%d\n", ans);
    printPath(ans);
  }
  return(0);
}
